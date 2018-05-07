problem(0,P):-
		P=[ [7,2,5,9,6,1,4,8,3],
				[3,6,9,4,2,8,1,7,5],
				[4,8,1,3,7,5,9,2,6],
				[9,1,6,2,8,4,5,3,7],
				[5,7,3,6,1,9,2,4,8],
				[2,4,1,7,5,3,6,9,1],
				[1,9,4,2,3,6,7,5,2],
				[6,3,7,5,4,2,3,1,9],
				[8,5,2,1,9,7,3,6,4]].

toateCifre([]).
toateCifre([Linie | Matrice]) :-
	\+member(n, Linie),
	toateCifre(Matrice).

membruGol(Linie, [Linie | _], C, C, J) :-
	member(n, Linie),
	cauta(Linie, n, J).

membruGol(Linie, [H | T], C, I, J) :-
	\+member(n, H),
	C1 is C + 1,
	membruGol(Linie, T, C1, I, J).

% cauta(L, E, Contor)
cauta([H | _], H, 1) :- !.
cauta([_ | T], E, C) :-
	cauta(T, E, C1),
	C is C1 + 1.
