% ex 1
% drum in  tre puncte conectate
connected(1,2).
connected(3,4).
connected(5,6).
connected(7,8).
connected(9,10).
connected(12,13).
connected(13,14).
connected(15,16).
connected(17,18).
connected(19,20).
connected(4,1).
connected(6,3).
connected(4,7).
connected(6,11).
connected(14,9).
connected(11,15).
connected(16,12).
connected(14,17).
connected(16,19).

path(P1, P2) :-
  connected(P1, P2).
path(P1, P2) :-
  connected(P1, X),
  path(X, P2).

% ex 2
% operatii aritmetice
succesor(N, [x | N]).

predecessor([x], []).
predecessor(N, Result) :-
  N = [_ | Result].

plus([], N2, N2).
plus([H | N1], N2, [H | Result]) :-
  plus(N1, N2, Result).

times([], _, []) :- !.
times([x], N2, N2) :- !.
times(N1, N2, Result) :-
  predecessor(N1, N11),
  times(N11, N2, Temp),
  plus(N2, Temp, Result).

% ex3
% element at
element_at([H | _], 1, H) :- !.
element_at([_ | T], P, R) :-
  P1 is P - 1,
  element_at(T, P1, R).

% ex4
% cuvinte incrucisate
word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(enhance,e,n,h,a,n,c,e).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).

crossword(V1, V2, V3, H1, H2, H3) :-
  word(V1, _, H1V1, _, H2V1, _, H3V1, _),
  word(V2, _, H1V2, _, H2V2, _, H3V2, _),
  word(V3, _, H1V3, _, H2V3, _, H3V3, _),
  word(H1, _, H1V1, _, H1V2, _, H1V3, _),
  word(H2, _, H2V1, _, H2V2, _, H2V3, _),
  word(H3, _, H3V1, _, H3V2, _, H3V3, _).

% ex5
% baza de date
born(jan, date(20,3,1977)).
born(jeroen, date(2,2,1992)).
born(joris, date(17,3,1995)).
born(jelle, date(1,1,2004)).
born(joan, date(24,12,0)).
born(joop, date(30,4,1989)).
born(jannecke, date(17,3,1993)).
born(jaap, date(16,11,1995)).

year(Year, Person) :-
  born(Person, date(_, _, Year)).

before(Date1, Date2) :-
  Date1 = date(Day1, Month1, Year1),
  Date2 = date(Day2, Month2, Year2),
  compare(Day1, Month1, Year1, Day2, Month2, Year2).

% true if date1 < date2
compare(_, _, Year1, _, _, Year2) :-
  Year1 < Year2, !.
compare(_, _, Year1, _, _, Year2) :-
  Year1 > Year2, !, fail.
compare(_, Month1, _, _, Month2, _) :-
  Month1 < Month2, !.
compare(_, Month1, _, _, Month2, _) :-
  Month1 > Month2, !, fail.
compare(Day1, _, _, Day2, _, _) :-
  Day1 < Day2, !.
compare(_, _, _, _, _, _) :-
  !, fail.

older(P1, P2) :-
  born(P1, Birth1),
  born(P2, Birth2),
  before(Birth1, Birth2).
