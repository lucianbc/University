/* ----------------------------------------------------------
JOCUL X SI 0
-------------------------------------------------------------*/
%  APELURI:
x0M:- x_si_o_minimax.
x0AB:- x_si_o_alpha_beta.

/* -----------------------------------------------------------
 PREDICATE SPECIFICE PENTRU JOCUL X SI 0
-------------------------------------------------------------*/
x_si_o_minimax:-
					statistics(walltime, [Start,_]),
						initializari(MAX,N),
						tablou_initial(Tablou),
						afis_tablou(Tablou),
						joc_minimax(st(x,Tablou,N,MAX)),
					statistics(walltime, [End,_]),
					Time is End - Start,
					format('~3d seconds.~n', [Time]).


x_si_o_alpha_beta:-
					statistics(walltime, [Start,_]),
						initializari(MAX,N),
						tablou_initial(Tablou),
						afis_tablou(Tablou),
						joc_alpha_beta(st(x,Tablou,N,MAX)),
					statistics(walltime, [End,_]),
					Time is End - Start,
					format('~3d seconds.~n', [Time]).

/* ---------------------------------------------------------
JUCATORUL CARE MARCHEAZA CU X INCEPE JOCUL.

PREDICATUL JUCATOR_MAX(M) ESTE FOLOSIT PENTRU DETERMINAREA JUCATORULUI CARE VA FACE PRIMA MUTARE;
EL ESTE, DE ASEMENEA, UTILIZAT PENTRU A DETERMINA CU CE JOACA MAX.
--------------------------------------------------------------*/
jucator_Max(M):-write('Incepe jocul ... '),nl,
				repeat,
				write('Vrei sa fii cu X ? (da/nu)'),nl,
				read(T),
				(T=da,M=0 ;T=nu, M=x;T=d,M=0;T=n,M=x),!.
initializari(M,N):-jucator_Max(M),
				nl,repeat,
				write('Adancimea: '),
				read(N),integer(N),!,nl.

%%%%%%%%
% DE IMPLEMENTAT!
%%%%%%%%

joc_minimax(st(_,Tablou,_,MAX)):-tablou_final(Tablou,J),!,anunt_castigator(J,MAX).
%% % Muta omul...
joc_minimax(st(J,Tablou,N,MAX)):- MAX\==J,!, mutare_MIN(Tablou, Turm, J), juc_opus(J, Jo), afis_tablou(Turm), joc_minimax(st(Jo, Turm, N, MAX)).

%% % Muta calculatorul...
joc_minimax(st(J,Tablou,N,MAX)):- MAX==J, minimax(st(J, Tablou, N, MAX), st(_, TablUrm, _, _), _), juc_opus(J, Jo), afis_tablou(TablUrm), joc_minimax(st(Jo, TablUrm, N, MAX)).


joc_alpha_beta(st(_,Tablou,_,MAX)):-tablou_final(Tablou,J),!,
									anunt_castigator(J,MAX).

%% % Muta omul...
joc_alpha_beta(st(J,Tablou,N,MAX)):- MAX\==J,!, mutare_MIN(Tablou, Turm, J), juc_opus(J, Jo), afis_tablou(Turm), joc_alpha_beta(st(Jo, Turm, N, MAX)).

%% % Muta calculatorul...
joc_alpha_beta(st(J,Tablou,N,MAX)):- MAX==J, alphabeta(st(J, Tablou, N, MAX), -100, 100, st(_, TablUrm, _, _), _), juc_opus(J, Jo), afis_tablou(TablUrm), joc_alpha_beta(st(Jo, TablUrm, N, MAX)).

%%%%%%%%
% *********************
%%%%%%%%

anunt_castigator(J,MAX):- J==MAX,write('Ai pierdut!'),nl;
						  juc_opus(J,J_O),J_O==MAX,
						  write('Ai castigat!'),nl,
						  write('Bravo !!');
						  J==gol,
						  write('Jocul s-a incheiat cu remiza '),nl.
mutare_MIN(Tablou,Tablou_urm,J):- nl,write('Trebuie sa marchezi. '),nl,
									write('Specifica campul pe care il vei marca.'),
									nl,repeat,det_coord_1(L),
									det_coord_2(C),
									N is L*3+C,
									liber_marcheaza(N,Tablou,Tablou_urm,J),!.

det_coord_1(L):- repeat,write('Linia: '),
				read(L1),integer(L1),!,
				L is L1-1.
det_coord_2(C):- repeat,write('Coloana: '),
				read(C1),integer(C1),!,
				C is C1-1.
liber_marcheaza(0,[gol|R],[J|R],J):-!.
liber_marcheaza(N,[H|T],[H|T1],J):- N1 is N-1,liber_marcheaza(N1,T,T1,J).

afis_tablou([C1,C2,C3,C4,C5,C6,C7,C8,C9]):- write(' 1 2 3 '),nl,nl,
											write('1 '),scrie_elem(C1),
											write('   '),scrie_elem(C2),
											write('   '),scrie_elem(C3),nl,
											write('2 '),scrie_elem(C4),
											write('   '),scrie_elem(C5),
											write('   '),scrie_elem(C6),nl,
											write('3 '),scrie_elem(C7),
											write('   '),scrie_elem(C8),
											write('   '),scrie_elem(C9),nl.
											scrie_elem(X):-X==gol,!,write('.');
											X==x,!,write('X');
											write('0').

juc_opus(x,0).
juc_opus(0,x).

mutare_max(st(MAX,_,_,MAX)).
mutare_min(st(MIN,_,_,MAX)):-juc_opus(MAX,MIN).

% INITIAL, TABLOUL ESTE COMPLET NEMARCAT

tablou_initial([gol,gol,gol,gol,gol,gol,gol,gol,gol]).

/* ---------------------------------------------------------
 PREDICATUL TABLOU_FINAL(T) ESTE ADEVARAT FIE DACA T ARE O LINIE ORIZONTALA, O COLOANA SAU O DIAGONALA
 MARCATA IN INTREGIME DE CATRE UNUL DIN JUCATORI, FIE DACA T ESTE COMPLET MARCAT, DAR NICI UNUL DINTRE
 JUCATORI NU ESTE CASTIGATOR (CAZ CARE CORESPUNDE UNEI SITUATII DE REMIZA).
 ---------------------------------------------------------*/
%%%%%%%%
% DE IMPLEMENTAT!
%%%%%%%%
tablou_final([C,C,C|_],C):-C\==gol,!.
tablou_final([_, _, _, C, C, C, | _], C) :- C \== gol, !.
tablou_final([_, _, _, _, _, _, C, C, C], C) :- C \== gol, !.
tablou_final([C, _, _, C, _, _, C, _, _], C) :- C \== gol, !.
tablou_final([_, C, _, _, C, _, _, C, _], C) :- C \== gol, !.
tablou_final([_, _, C, _, _, C, _, _, C], C) :- C \== gol, !.
tablou_final([C, _, _, _, C, _, _, _, C], C) :- C \== gol, !.
tablou_final([_, _, C, _, C, _, C, _, _], C) :- C \== gol, !.
tablou_final(L, gol) :- \+member(gol, L).


mutari(Poz,ListaPoz):- bagof(Poz1,mutare(Poz,Poz1),ListaPoz).


mutare(st(Jucator,T,N,M),st(Jucator_opus,Tablou1,N1,M)):-
	juc_opus(Jucator, Jucator_opus),
	N1 is N - 1,
	marcheaza(T, Jucator, Tablou1).

marcheaza([gol | Rest], Marcaj, [Marcaj | Rest]).
marcheaza([P | Rest], Marcaj, [P | UrmRest]) :-
	marcheaza(Rest, Marcaj, UrmRest).


%%%%%%%%
% *********************
%%%%%%%%

% DEFINIM FUNCTIA DE EVALUARE STATICA

staticval(st(_,Tablou,_,MAX),Val):- tablou_final(Tablou,T),!,juc_opus(MAX,MIN),
									(T==MIN, Val = -99;
									T==MAX, Val is 99;
									T==gol,Val is 0).
staticval(st(_,Tablou,_,MAX),Val):- juc_opus(MAX,MIN),
									nr_lin_deschise(MAX,L_D_2,Tablou),

									%DETERMINAM NUMARUL DE LINII DESCHISE PENTRU MAX

									nr_lin_deschise(MIN,L_D_1,Tablou),

									%DETERMINAM NUMARUL DE LINII DESCHISE PENTRU MIN

									Val is L_D_2-L_D_1.
/* ---------------------------------------------------------
 PREDICATUL NR_LIN_DESCHISE(XO,L_D,TABLOU) ESTE UTILIZAT PENTRU DETERMINAREA NUMARULUI DE LINII
 DESCHISE (L_D) PENTRU JUCATORUL XO, IN CAZUL CONFIGURATIEI (TABLOULUI) TABLOU.
 --------------------------------------------------------- */

nr_lin_deschise(XO,L_D,Tablou):- linia1(Tablou,L1,XO),
								linia2(Tablou,L2,XO),
								linia3(Tablou,L3,XO),
								coloana1(Tablou,C1,XO),
								coloana2(Tablou,C2,XO),
								coloana3(Tablou,C3,XO),
								diagonala1(Tablou,D1,XO),
								diagonala2(Tablou,D2,XO),
								L_D is L1+L2+L3+C1+C2+C3+D1+D2.
/* ---------------------------------------------------------
 PREDICATUL LINIA1(T,R,XO) ESTE FOLOSIT PENTRU A DETERMINA DACA PRIMA LINIE ORIZONTALA A TABLOULUI T
 ESTE LINIE DESCHISA PENTRU JUCATORUL XO; DACA DA, ATUNCI R=1, ALTFEL R=0.
 --------------------------------------------------------- */
%%%%%%%%
% DE IMPLEMENTAT!
%%%%%%%%
linia1([A, B, C | _], 1, XO) :-juc_opus(XO, Jo), \+member(Jo, [A, B, C]), !.
linia1([_, _, _ | _], 0, _).

linia2([_, _, _, A, B, C | _], 1, XO) :-juc_opus(XO, Jo), \+member(Jo, [A, B, C]), !.
linia2([_, _, _, _, _, _ | _], 0, _).

linia3([_, _, _, _, _, _, A, B, C], 1, XO) :-juc_opus(XO, Jo), \+member(Jo, [A, B, C]), !.
linia3([_, _, _, _, _, _, _, _, _], 0, _).


/* ---------------------------------------------------------
% PREDICATUL COLOANA1(T,R,XO) ESTE FOLOSIT PENTRU A DETERMINA DACA PRIMA COLOANA A TABLOULUI T ESTE
% LINIE DESCHISA PENTRU JUCATORUL XO; DACA DA, ATUNCI R=1, ALTFEL R=0.
 --------------------------------------------------------- */
coloana1([A, _, _, B, _, _, C, _, _], 1, XO) :-juc_opus(XO, Jo), \+member(Jo, [A, B, C]), !.
coloana1([_, _, _, _, _, _, _, _, _], 0, _).

coloana2([_, A, _, _, B, _, _, C, _], 1, XO) :-juc_opus(XO, Jo), \+member(Jo, [A, B, C]), !.
coloana2([_, _, _, _, _, _, _, _, _], 0, _).

coloana3([_, _, A, _, _, B, _, _, C], 1, XO) :-juc_opus(XO, Jo), \+member(Jo, [A, B, C]), !.
coloana3([_, _, _, _, _, _, _, _, _], 0, _).


/* ---------------------------------------------------------
% PREDICATUL DIAGONALA1(T,R,XO) ESTE FOLOSIT PENTRU A DETERMINA DACA PRIMA DIAGONALA A TABLOULUI T ESTE
% LINIE DESCHISA PENTRU JUCATORUL XO; DACA DA, ATUNCI R=1, ALTFEL R=0
 --------------------------------------------------------- */
diagonala1([A, _, _, _, B, _, _, _, C], 1, XO) :-juc_opus(XO, Jo), \+member(Jo, [A, B, C]), !.
diagonala1([_, _, _, _, _, _, _, _, _], 0, _).

diagonala2([_, _, A, _, B, _, C, _, _], 1, XO) :-juc_opus(XO, Jo), \+member(Jo, [A, B, C]), !.
diagonala2([_, _, _, _, _, _, _, _, _], 0, _).


%%%%%%%%
% *********************
%%%%%%%%

/* -----------------------------------------------------------
					ALGORITMUL MINIMAX
-------------------------------------------------------------*/

minimax(Poz,SuccBun,Val):- mutari(Poz,ListaPoz),!,
						celmaibun(ListaPoz,SuccBun,Val);
						staticval(Poz,Val).
celmaibun([Poz],Poz,Val):-minimax(Poz,_,Val).
celmaibun([Poz1|ListaPoz],PozBun,ValBuna):- minimax(Poz1,_,Val1),
											celmaibun(ListaPoz,Poz2,Val2),
											maibine(Poz1,Val1,Poz2,Val2,PozBun,ValBuna).


maibine(Poz0,Val0,Poz1,Val1,Poz0,Val0):- mutare_min(Poz0),Val0>Val1,!;
										 mutare_max(Poz0),Val0<Val1,!.
maibine(Poz0,Val0,Poz1,Val1,Poz1,Val1).





/* -----------------------------------------------------------
					ALGORITMUL ALPHA-BETA
-------------------------------------------------------------*/

alphabeta(Poz,Alpha,Beta,PozBuna,Val):-
					mutari(Poz,ListaPoz),!,
					limitarebuna(ListaPoz,Alpha,Beta,PozBuna,Val);
					staticval(Poz,Val).

limitarebuna([Poz|ListaPoz],Alpha,Beta,PozBuna,ValBuna):-
					alphabeta(Poz,Alpha,Beta,_,Val),
					destuldebun(ListaPoz,Alpha,Beta,Poz,Val,PozBuna,ValBuna).

					destuldebun([],_,_,Poz,Val,Poz,Val):-!.
destuldebun(_,Alpha,Beta,Poz,Val,Poz,Val):-
					mutare_min(Poz),Val>Beta,!;
					mutare_max(Poz),Val<Alpha,!.
destuldebun(ListaPoz,Alpha,Beta,Poz,Val,PozBuna,ValBuna):-
					limitenoi(Alpha,Beta,Poz,Val,AlphaNou,BetaNou),
					limitarebuna(ListaPoz,AlphaNou,BetaNou,Poz1,Val1),
					maibine(Poz,Val,Poz1,Val1,PozBuna,ValBuna).

limitenoi(Alpha,Beta,Poz,Val,Val,Beta):-  mutare_min(Poz),Val>Alpha,!.
limitenoi(Alpha,Beta,Poz,Val,Alpha,Val):- mutare_max(Poz),Val<Beta,!.
limitenoi(Alpha,Beta,_,_,Alpha,Beta).

maibine(Poz0,Val0,Poz1,Val1,Poz0,Val0):- mutare_min(Poz0),Val0>Val1,!;
										 mutare_max(Poz0),Val0<Val1,!.
maibine(Poz0,Val0,Poz1,Val1,Poz1,Val1).
