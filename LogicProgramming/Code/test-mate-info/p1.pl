% merge/3: true if the first two lists are sorted and the third one is the frst
% two, merged and sorted
merge([], L, L).
merge(L, [], L).

merge([H1 | L1], [H2 | L2], [H1 | Merged]) :-
  H1 < H2,
  merge(L1, [H2 | L2], Merged).

merge([H1 | L1], [H2 | L2], [H2 | Merged]) :-
  H1 >= H2,
  merge([H1 | L1], L2, Merged).

% list2set/2: true it the first is a list and the second list contains all
% distinct elements of the first one
list2set([], []).
list2set([H | T], Set) :-
  list2set(T, Set),
  member(H, Set), !.
list2set([H | T], [H | Set]) :-
  list2set(T, Set).

% intesect/3: true if the first two arguments are lists and the third is the
% intersection of the first two
intersect(_, [], []).
intersect([], _, []).
intersect([H | T], L, [H | I]) :-
  remove(H, L, R1), !,
  intersect(T, R1, I).
intersect([_ | T], L, I) :-
  intersect(T, L, I).

remove(X, [X | T], T).
remove(X, [Y | T], [Y | R]) :-
  X \= Y,
  remove(X, T, R).
