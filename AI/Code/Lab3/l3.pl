% lists
afis([]).
afis([H | T]) :- write(H), nl, afis(T).

% adaugare

add([], X, [X]).
add(L, X, [L|X]).

add2([], E, [E]).
add2([H | T], E, [H | T1]) :-
  add2(T, E, T1).

% ex 1
membru(X, [H | T]) :- X = H; membru(X, T).

% ex 2
gaseste(0, [X | T], X).
gaseste(N, [_ | T], X) :- N1 is N - 1, gaseste(N1, T, X).

% ex 3
sterge(0, [H | T], T).
sterge(N, [H | T], [H | T1]) :- N1 is N - 1, sterge(N1, T, T1).

% ex 4
sterge-el(E, [E | T], T).
sterge-el(E, [H | T], [H | T1]) :- sterge-el(E, T, T1).

% not working
stergeVal([], _, []).
stergeVal([E | T], E, T1) :- stergeVal(T, E, T1).
stergeVal([H | T], E, [H, T1]) :- stergeVal(T, E, T1).

% ex 5
len(0, []).
len(K, [H | T]) :- len(K1, T), K is K1 + 1.

% ex 6
conc([], L, L).
conc([X | L1], L2, [X | L3]) :- conc(L1, L2, L3).

% ex 7
% not working
are_dup([]) :- fail.
are_dup([_]) :- fail.
are_dup([H | T]) :- membru(H, T); are_dup(T).

% ex 9
sumLess5([], 0).
sumLess5([X], X).
sumLess5([H | T], S) :- H < 5, sumLess5(T, S1), S is S1 + H.
