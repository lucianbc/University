% roman to arab number converter
symbol('I', 1).
symbol('V', 5).
symbol('X', 10).
symbol('L', 50).
symbol('C', 100).
symbol('D', 500).
symbol('M', 1000).

symbols2numbers([], []).
symbols2numbers([S | Symbols], [N | Numbers]) :-
  symbol(S, N),
  symbols2numbers(Symbols, Numbers).

sum([], 0).
sum([H | L], S) :-
  sum(L, S1),
  S is S1 + H.

signify(First, Second, First) :- First >= Second, !.
signify(First, _, X) :- X is -First.

signify([], []) :- !.
signify([X], [X]) :- !.
signify([H1, H2 | Rest], Signified) :-
  signify([H2 | Rest], SmSignified),
  signify(H1, H2, Ret),
  Signified = [Ret | SmSignified].

roman2arabic(Roman, Arabic) :-
  atom_chars(Roman, RomanSymbols),
  symbols2numbers(RomanSymbols, Numbers),
  signify(Numbers, SignedNumbers),
  sum(SignedNumbers, Arabic).
