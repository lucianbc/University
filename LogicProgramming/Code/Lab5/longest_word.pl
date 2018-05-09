% Ex 2: cel mai lung cuvant
:- include('words.pl').

word_letters(Word, X) :-
  atom_chars(Word, X).

cover(L1, L2) :-
  msort(L1, L11),
  msort(L2, L22),
  cover2(L11, L22).

cover2([], []) :- !.
cover2([], [_ | _]) :- !.
cover2([H | L11], [H | L22]) :-
  cover2(L11, L22), !.
cover2([H1 | L11], [_ | L22]) :-
  cover2([H1 | L11], L22).

solution(List, Word, Score) :-
  word(Word),
  word_letters(Word, WordL),
  length(WordL, Score),
  cover(WordL, List).

sol_optima(Lista, Cuvant, Lg, Sc) :-
  solution(Lista, Cuvant, Lg),
  Sc = Lg, !.
sol_optima(L, W, Lg, Sc) :-
  Lg1 is Lg - 1,
  sol_optima(L, W, Lg1, Sc).

topsolution(List, Word, Score) :-
  length(List, L),
  sol_optima(List, Word, L, Score).
