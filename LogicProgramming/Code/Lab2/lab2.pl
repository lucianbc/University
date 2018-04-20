% ex1
% distanta
distance(P1, P2, D) :-
  P1 = (X1, Y1),
  P2 = (X2, Y2),
  X22 is (X2 - X1) ** 2,
  Y22 is (Y2 - Y1) ** 2,
  D22 is X22 + Y22,
  P22 is 1 / 2,
  D is D22 ** P22.

% ex2
% afisare patrat n x n
line(0, _) :- write('\n'), !.
line(N, P) :-
  write(P),
  N1 is N - 1,
  line(N1, P).
rect(_, 0, _) :- !.
rect(L, H, P) :-
  line(L, P),
  H1 is H - 1,
  rect(L, H1, P).
square(N, P) :-
  rect(N, N, P).

% ex3
% fibonacci
fib_(0, 1, 0) :- !.
fib_(N, F1, F2) :-
  N1 is N - 1,
  fib_(N1, F2, F3),
  F1 is F2 + F3.
fib(N, R) :-
  fib_(N, R, _).
