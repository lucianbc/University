inlocuieste(E, Gol, [E | Placute], [Gol | Placute]) :- !.
inlocuieste(E, Gol, [X | Placute], [X | Placute1]) :-
	inlocuieste(E, Gol, Placute, Placute1).

dM(E, Gol, DM) :-
	E = /(X1, Y1),
	Gol = /(X2, Y2),
	XX is abs((X2 - X1)),
	YY is abs((Y2 - Y1)),
  DM is XX + YY.

  indice([E | _], E, 0) :- !.
  indice([_ | L], X, I) :-
  	indice(L, X, I1),
  	I is I1 + 1.

  arata_nod(Nod) :-
    indice(Nod, 1/3, I1),
  	indice(Nod, 2/3, I2),
  	indice(Nod, 3/3, I3),
  	indice(Nod, 1/2, I4),
  	indice(Nod, 2/2, I5),
  	indice(Nod, 3/2, I6),
  	indice(Nod, 1/1, I7),
  	indice(Nod, 2/1, I8),
  	indice(Nod, 3/1, I9),
  	write('-----'), nl,
    write(I1), write(' '), write(I2), write(' '), write(I3), nl,
    write(I4), write(' '), write(I5), write(' '), write(I6), nl,
    write(I7), write(' '), write(I8), write(' '), write(I9), nl,
    write('-----'), nl.
