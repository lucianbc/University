/* ---------------------------------------------------------
% Apel
------------------------------------------------------------*/
pb :-
	tell('/home/lucian/Documents/University/AI/Code/Lab9/output.txt'),
	initial(Poz),
	bestfirst(Poz,Sol),
	arata_solutie(Sol),
	told.


/* ---------------------------------------------------------
% Procedurile (predicatele) specifice problemei eight-puzzle
------------------------------------------------------------*/
% Definim relatia de succesiune; consideram ca toate arcele au costul 1.

ss([Gol|Placute],[Gol1|Placute1],1):-
	member(E, Placute),
	dM(E, Gol, DM),
	DM = 1,
	Gol1 = E,
	inlocuieste(E, Gol, Placute, Placute1).

dM(E, Gol, DM) :-
	E = /(X1, Y1),
	Gol = /(X2, Y2),
	XX is abs((X2 - X1)),
	YY is abs((Y2 - Y1)),
	DM is XX + YY.

inlocuieste(E, Gol, [E | Placute], [Gol | Placute]) :- !.
inlocuieste(E, Gol, [X | Placute], [X | Placute1]) :-
	inlocuieste(E, Gol, Placute, Placute1).

h([Gol|L], H) :-
	scop([Gol1| L1]),
	h2([Gol | L], [Gol1 | L1], H2),
	secv(Gol1, L, L1, SECV),
	H is H2 + 3 * S.


h2([], [], 0) :- !.
h2([E1 | L1], [E2 | L2], S) :-
	h2(L1, L2, S1),
	dM(E1, E2, D),
	S is S + D.

secv(Gol, L1, L2, Secv) :-
	inversiuni(L1, L2, I),
	(
		member(Gol, L1), S is I * 2 - 1; S is I * 2
	).

inversiuni([], [], 0 ) :- !.
inversiuni([H | T], [H | T1], I) :-
	inversiuni(T, T1, I).
inversiuni([H1 | T1], [H2 | T2], I) :-
	inversiuni(T1, T2, I2),
	I is I2 + 1.

arata_solutie([]).
arata_solutie([Nod|Drum]):-
	arata_nod(Nod),
	arata_solutie(Drum).


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

/* ---------------------------------------------------------
% Configuratia initiala si cea finala (scop)
------------------------------------------------------------*/
scop([2/2, 	1/3,	2/3,	3/3,	3/2,	3/1,	2/1,	1/1,	1/2]).

initial([2/2,	1/3,	3/2,	2/3,	3/3,	3/1,	2/1,	1/1,	1/2]).

/* ---------------------------------------------------------
% predicatele specifice best-first
------------------------------------------------------------*/

% Predicatul bestfirst(Nod_initial,Solutie) este adevarat daca Solutie este un drum (obtinut folosind strategia best-first) de la nodul Nod_initial la o stare-scop.

bestfirst(Nod_initial,Solutie):- expandeaza([],l(Nod_initial,0/0),9999999,_, da,Solutie).

expandeaza(Drum,l(N,_),_,_, da,[N|Drum]):-scop(N).
% Caz 1: daca N este nod-scop, atunci construim o cale-solutie.

expandeaza(Drum,l(N,F/G),Limita,Arb1,Rez,Sol):- F=<Limita,
												(bagof(M/C,(ss(N,M,C), \+ (membru(M,Drum))),Succ),!,
												listasucc(G,Succ,As),
												cea_mai_buna_f(As,F1),
												expandeaza(Drum,t(N,F1/G,As),Limita,Arb1, Rez,Sol);
												Rez=imposibil
												).
% Caz 2: Daca N este nod-frunza a carui fˆ -valoare
% este mai mica decat Limita,atunci ii generez
% succesorii si ii expandez in limita Limita.

expandeaza(Drum,t(N,F/G,[A|As]),Limita,Arb1,Rez,Sol):-F=<Limita,
													cea_mai_buna_f(As,BF),
													min(Limita,BF,Limita1),
													expandeaza([N|Drum],A,Limita1,A1,Rez1,Sol),
													continua(Drum,t(N,F/G,[A1|As]),Limita,Arb1,
													Rez1,Rez,Sol).
% Caz 3: Daca arborele de radacina N are subarbori
% nevizi si fˆ -valoarea este mai mica decat Limita,
% atunci expandam cel mai "promitator" subarbore al
% sau; in functie de rezultatul obtinut, Rez, vom
% decide cum anume vom continua cautarea prin
% intermediul procedurii (predicatului) continua.

expandeaza(_,t(_,_,[]),_,_,imposibil,_):-!.
% Caz 4: pe aceasta varianta nu o sa obtinem niciodata
% o solutie.

expandeaza(_,Arb,Limita,Arb,nu,_):- f(Arb,F),F>Limita.
% Caz 5: In cazul unor fˆ -valori mai mari decat Bound, arborele nu mai poate fi extins.

continua(_,_,_,_,da,da,Sol).

continua(P,t(N,F/G,[A1|As]),Limita,Arb1,nu,Rez,Sol):- insereaza(A1,As,NAs),
													cea_mai_buna_f(NAs,F1),
													expandeaza(P,t(N,F1/G,NAs),Limita,Arb1,Rez,Sol).

continua(P,t(N,F/G,[_|As]),Limita,Arb1,imposibil,Rez, Sol):- cea_mai_buna_f(As,F1),
															 expandeaza(P,t(N,F1/G,As),Limita,Arb1,Rez,Sol).

listasucc(_,[],[]).
listasucc(G0,[N/C|NCs],Ts):- G is G0+C,
							h(N,H),
							F is G+H,
							listasucc(G0,NCs,Ts1),
							insereaza(l(N,F/G),Ts1,Ts).

%Predicatul insereaza(A,As,As1) este utilizat pentru
%inserarea unui arbore A intr-o lista de arbori As,
%mentinand ordinea impusa de fˆ -valorile lor.
insereaza(A,As,[A|As]):-f(A,F), cea_mai_buna_f(As,F1), F=<F1,!.
insereaza(A,[A1|As],[A1|As1]):-insereaza(A,As,As1).

min(X,Y,X):-X=<Y,!.
min(_,Y,Y).

f(l(_,F/_),F). % f-val unei frunze
f(t(_,F/_,_),F). % f-val unui arbore

%Predicatul cea_mai_buna_f(As,F) este utilizat pentru
%a determina cea mai buna fˆ -valoare a unui arbore din
%lista de arbori As, daca aceasta lista este nevida;
%lista As este ordonata dupa fˆ -valorile subarborilor
%constituenti.
cea_mai_buna_f([A|_],F):-f(A,F).
cea_mai_buna_f([],999999).
%In cazul unei liste de arbori vide, fˆ -valoarea
%determinata este foarte mare.
