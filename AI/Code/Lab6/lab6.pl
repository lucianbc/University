% Arbore: t(R, S, D)
% Frunza: t(R, n, n)
arb1(
  t(20,
    t(15,
      n,
      t(17, n, n)
    ),
    t(40,
      t(35, n, n),
      t(42, n, n)
    )
  )
).

% ex1
afisPre :- arb1(T), afisPre(T).
afisPre(t(R, n, n)) :-
  write(R), write(' ').
afisPre(n).
afisPre(t(R, S, D)) :-
  write(R), write(' '),
  afisPre(S),
  afisPre(D).

afisPost :- arb1(T), afisPost(T).
afisPost(t(R, n, n)) :-
  write(R), write(' ').
afisPost(n).
afisPost(t(R, S, D)) :-
  afisPost(S),
  afisPost(D),
  write(R), write(' ').

afisIn :- arb1(T), afisIn(T).
afisIn(t(R, n, n)) :-
  write(R), write(' ').
afisIn(n).
afisIn(t(R, S, D)) :-
  afisIn(S),
  write(R), write(' '),
  afisIn(D).

% ex2
nrFrunze(n, 0) :- !.
nrFrunze(t(_, n, n), 1) :- !.
nrFrunze(t(_, S, D), N) :-
  nrFrunze(S, N1),
  nrFrunze(D, N2),
  N is N1 + N2.

nrNoduri(n, 0) :- !.
nrNoduri(t(_, n, n), 0) :- !.
nrNoduri(t(_, S, D), N) :-
  nrNoduri(S, N1),
  nrNoduri(D, N2),
  N is N1 + N2 + 1.

% ex3
increment_gt(Crt, X, Prag, S) :-
  X > Prag, S is Crt + 1, !.
increment_gt(Crt, _, _, Crt).

biggerThan(n, _, 0).
biggerThan(t(R, n, n), P, N) :-
  increment_gt(0, R, P, N), !.
biggerThan(t(R, S, D), P, N) :-
  biggerThan(S, P, N1),
  biggerThan(D, P, N2),
  Ni is N1 + N2,
  increment_gt(Ni, R, P, N).

% ex4
min(A, B, A) :- A < B, !.
min(_, B, B).

max(A, B, A) :- A > B, !.
max(_, B, B).

min_max(t(R, n, n), R, R) :- !.
min_max(t(R, S, n), Min, Max) :-
  min_max(S, Min1, Max1),
  Min is min(Min1, R),
  Max is max(Max1, R),
  !.
min_max(t(R, n, D), Min, Max) :-
  min_max(D, Min1, Max1),
  Min is min(Min1, R),
  Max is max(Max1, R),
  !.
min_max(t(R, S, D), Min, Max) :-
  min_max(S, Min1, Max1),
  min_max(D, Min2, Max2),
  MinT is min(Min1, Min2), Min is min(MinT, R),
  MaxT is max(Max1, Max2), Max is max(MaxT, R).


% ex5
% avg(T, A)
sum_count(n, 0, 0) :- !.
sum_count(t(R, n, n), R, 1) :- !.
sum_count(t(R, S, D), Sum, Count) :-
  sum_count(S, S1, C1),
  sum_count(D, S2, C2),
  Sum is S1 + S2 + R,
  Count is C1 + C2 + 1.

avg(T, A) :-
  sum_count(T, S, C),
  A is S / C.

% ex6
sum_level(n, _, 0) :- !.
sum_level(t(R, _, _), 1, R) :- !.
sum_level(t(_, S, D), L, Sum) :-
  L > 1,
  L1 is L - 1,
  sum_level(S, L1, Sum1),
  sum_level(D, L1, Sum2),
  Sum is Sum1 + Sum2.

% ex7
split(List, Left, Middle, Right) :-
  length(List, TotLen),
  HalfLen is TotLen div 2,
  conc(Left, [Middle | Right], List),
  length(Left, HalfLen).

buildTree([], n) :- !.
buildTree(List, Tree) :-
  split(List, Left, Mid, Right),
  buildTree(Left, LeftTree),
  buildTree(Right, RightTree),
  Tree = t(Mid, LeftTree, RightTree).

% ex8
conc([], L2, L2).
conc([H | L1], L2, [H | L3]) :-
  conc(L1, L2, L3).

pair(_, n, []).
pair(H, t(Hh, _, _), [(H, Hh)]).

muchii(n, []) :- !.
muchii(t(_, n, n), []) :- !.
muchii(t(R, S, D), Muchii) :-
  muchii(S, M1),
  muchii(D, M2),
  pair(R, S, P1),
  pair(R, D, P2),
  conc(P1, M1, Mt1),
  conc(P2, M2, Mt2),
  conc(Mt1, Mt2, Muchii).
