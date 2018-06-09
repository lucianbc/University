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
membru(X, [H | T]) :-
   X = H;
   membru(X, T).

% ex 2
gaseste(0, [X | _], X).
gaseste(N, [_ | T], X) :-
  N1 is N - 1,
  gaseste(N1, T, X).

% ex 3
sterge(0, [_ | T], T).
sterge(N, [H | T], [H | T1]) :- N1 is N - 1, sterge(N1, T, T1).

% ex 4
stergeVal(_, [], []).
stergeVal(V, [V | T], L) :-
  stergeVal(V, T, L), !.
stergeVal(V, [H | T], [H | L]) :-
  stergeVal(V, T, L).

% ex 5
len(0, []).
len(K, [_ | T]) :- len(K1, T), K is K1 + 1.

% ex 6
conc([], L, L).
conc([X | L1], L2, [X | L3]) :-
  conc(L1, L2, L3).

% ex 7
are_dup([]) :- fail.
are_dup([_]) :- fail.
are_dup([H | T]) :- membru(H, T), !; are_dup(T).

% ex8
stergeDup([], []).
stergeDup([H | In], [H | Out]) :-
  stergeVal(H, In, FaraH),
  stergeDup(FaraH, Out).

% ex 9
sumLess5([], 0).
sumLess5([H | T], S) :-
  H < 5,
  sumLess5(T, S1),
  S is S1 + H.

% ex10
mereSiPortocale([], 0, 0).
mereSiPortocale([H | T], Mere, Portocale) :-
  mereSiPortocale(T, M1, P1),
  (
    H = mar, Mere is M1 + 1, Portocale = P1, !;
    H = portocala, Mere = M1, Portocale is P1 + 1
  ).
