score(josef,masopust,[eu(1960,1),wc(1962,1)]).
score(wayne,rooney,[eu(2004,2),eu(2012,1),wc(2014,1),eu(2016,1)]).
score(martin,peters,[wc(1966,1),wc(1970,1)]).
score(franz,beckenbauer,[wc(1966,4),wc(1970,1)]).
score(pak,seungzin,[wc(1966,2)]).
score(uwe,seeler,[wc(1958,2),wc(1962,2),wc(1966,2),wc(1970,3)]).
score(just,fontaine,[wc(1958,13)]).

mystery(wc(N)) :- score(X,Y,XS), member(wc(N,M),XS), M>3.

mmystery(Q) :-
  Q =.. [Func, Arg],
  QQ =.. [Func, Arg, M],
  score(X, Y, XS),
  member(QQ, XS),
  M > 3.

tournament_score(S) :-
  (S = wc(M, N), !; S = eu(M, N)),
  integer(M),
  integer(N),
  M > 0,
  N > 0.

tournament_scores([]).
tournament_scores([H | T]) :-
  tournament_score(H),
  tournament_scores(T).

sum_score(Name, Surname, S) :-
  score(Name, Surname, G),
  sum(G, S).

sum([], 0).
sum([H | T], S) :-
  sum(T, SS),
  H =.. [_, _, Goals],
  S is SS + Goals.
