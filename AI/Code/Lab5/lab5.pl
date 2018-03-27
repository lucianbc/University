matrice([[1, 2, 3], [4, 5, 6], [7, 8, 9]]).
matrice2([[1, 2, 3, 7, 9], [4, 5, 6, 8, 7], [7, 8, 9, 6, 4]]).
diag([[1, 0, 1], [0, 1, 0], [1, 0, 1]]).
categorii([mar/fruct, portocala/fruct, caine/animal, cal/animal, narcisa/floare]).

% ex1
afis([H | _], 1) :-
  afisare(H).

afis([_ | T], C) :-
  C1 is C - 1,
  afis(T, C1).

afisareLinie(I) :-
  matrice(M),
  afis(M, I).

afisare(L) :-
  write(L),
  write('\n').

% ex 2
get_el([H | _], 1, H) :- !.
get_el([_ | T], P, E) :-
  P1 is P - 1,
  get_el(T, P1, E).

itereaza([H | _], H).
itereaza([_ | T], X) :- itereaza(T, X).

afisC(M, NCol, X) :-
  itereaza(M, R),
  get_el(R, NCol, X).

getCol(M, NCol, Col) :-
  bagof(X, afisC(M, NCol, X), Col).

afisareColoana(C) :-
  matrice(M),
  getCol(M, C, Coloana),
  afisare(Coloana).

% ex3
% get_first_n(L, N, X)
get_first_n(_, 0, _) :- !, fail.
get_first_n([H | _], _, H).
get_first_n([_ | T], N, X) :-
  N1 is N - 1,
  get_first_n(T, N1, X).

collect_first_n(L, N, C) :-
  findall(X, get_first_n(L, N, X), C).

itereaza([H | _], Crt, H, Crt).
itereaza([_ | T], Crt, X, I) :-
  C1 is Crt + 1,
  itereaza(T, C1, X, I).
itereaza(L, E, I) :- itereaza(L, 0, E, I).

e_sub_diag(M, T) :-
  itereaza(M, L, I),
  collect_first_n(L, I, T).

sub_diag(M, T) :-
  findall(X, e_sub_diag(M, X), T).

% ex4
% valideaza_lista(L, Start, Pozitii)
valideaza_lista([], _, _) :- !.
valideaza_lista([1 | T], Iterator, [Iterator | Poz]) :-
  It1 is Iterator + 1,
  valideaza_lista(T, It1, Poz), !.
valideaza_lista([0 | T], Iterator, []) :-
  It1 is Iterator + 1,
  valideaza_lista(T, It1, []), !.
valideaza_lista([0 | T], Iterator, [H | Poz]) :-
  H =\= Iterator,
  It1 is Iterator + 1,
  valideaza_lista(T, It1, [H | Poz]).

to_set(L, S) :-
  setof(X, itereaza(L, X), S).

valideaza_matrice([], _, _) :- !.

valideaza_matrice([H | Mat], L, R) :-
  to_set([L, R], S),
  valideaza_lista(H, 1, S),
  L1 is L + 1,
  R1 is R - 1,
  valideaza_matrice(Mat, L1, R1).

diagonala(M) :-
  length(M, L),
  valideaza_matrice(M, 1, L).

% ex 5
clase(L, Cl) :-
  setof(C, E^X^(
    itereaza(L, X),
    X = /(E, C)
  ), Cl).


elemente([], _, []).
elemente([/(E, Cl) | T], Cl, [E | El])
  :- elemente(T, Cl, El), !.
elemente([_ | T], Cl, El) :-
  elemente(T, Cl, El).

union(L, X) :-
  setof(Z, C ^ Cl ^(
    clase(L, C),
    itereaza(C, Cl),
    elemente(L, Cl, Z)
  ), X).

% ex 6
int_iterate(1, 1) :- !.
int_iterate(X, X).
int_iterate(K, X) :-
  K1 is K - 1,
  int_iterate(K1, X).

get_cols(M, C) :-
  length(M, L),
  setof(Crt, int_iterate(L, Crt), Sorted),
  itereaza(Sorted, Cr),
  getCol(M, Cr, C).

transpusa(M, T) :-
  bagof(C, get_cols(M, C), T).

% ex 7
% sublist(List, L, R, SubList)
sublist_it([H | _], 0, R, H) :- R >= 0.
sublist_it([_ | T], 0, R, X) :-
  R >= 0,
  R1 is R - 1,
  sublist_it(T, 0, R1, X).
sublist_it([_ | T], L, R, X) :-
  L >= 0,
  R >= 0,
  L1 is L - 1,
  R1 is R - 1,
  sublist_it(T, L1, R1, X).

sublist(List, L, R, SubList) :-
  findall(X, sublist_it(List, L, R, X), SubList).

interval(L, R, X) :- L =< X, X =< R.

% invocare:
% matrice2(M), submatrice(M, 1, 2, 2, 3, S).
submatrice(M, L1, C1, L2, C2, SM) :-
  findall(S, (
    itereaza(M, Linie, Indice),
    interval(L1, L2, Indice),
    sublist(Linie, C1, C2, S)
    ), SM
  ).
