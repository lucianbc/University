% ex1
all_a([a]) :- !.
all_a([H | T]) :-
  H = a,
  all_a(T).

trans_a_b([], []).
trans_a_b([a | Ta], [b | Tb]) :-
  trans_a_b(Ta, Tb).

% ex2
scalarMult(_, [], []) :- !.
scalarMult(A, [H | V], Result) :-
  scalarMult(A, V, T),
  NA is A * H,
  Result = [NA | T].

dot([], [], 0) :- !.
dot([H1 | L1], [H2 | L2], Result) :-
  dot(L1, L2, Res),
  HH is H1 * H2,
  Result is HH + Res.

max([A], A) :- !.
max([H | T], Max) :-
  max(T, M1),
  (
    H > M1, Max = H, !;
    Max = M1
  ).

% ex3
rev([], Z, Z).
rev([H | T], Z, Cont) :- rev(T, Z, [H | Cont]).

palindrome(X) :- rev(X, X, []).

% ex 4
remove_duplicates([], []) :- !.
remove_duplicates([H | T], Res) :-
  remove_duplicates(T, NDRes),
  (
    member(H, NDRes), Res = NDRes, !;
    Res = [H | NDRes]
  ).
