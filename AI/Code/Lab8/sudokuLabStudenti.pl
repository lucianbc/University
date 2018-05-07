?- use_module(library(lists)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% START SUDOKU %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   Sudoku template
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
problem(0,P):-
		P=[ [7,2,5,9,6,1,4,8,3],
			[3,6,9,4,2,8,1,7,5],
			[4,8,1,3,7,5,9,2,6],
			[9,1,6,2,8,4,5,3,7],
			[5,7,3,6,1,9,2,4,8],
			[2,4,n,7,5,3,6,9,1],
			[1,9,4,n,3,6,7,5,2],
			[6,3,7,5,4,2,n,1,9],
			[8,5,2,1,n,7,3,6,4]].


problem(1,P):-
		P=[ [7,n,5,n,6,1,4,n,3],
			[3,6,9,n,2,8,1,7,5],
			[4,8,1,3,7,5,9,2,6],
			[9,1,6,n,8,4,5,n,7],
			[5,7,3,6,1,9,2,4,8],
			[2,4,n,7,5,3,6,n,1],
			[1,9,4,n,3,6,7,5,2],
			[6,3,7,5,4,2,n,1,9],
			[8,5,2,1,n,7,3,6,4]].

problem(2, P) :-
        P=[ [7,n,5,n,6,1,4,n,3],
			[3,6,9,n,2,8,n,7,5],
			[n,8,1,3,7,n,9,2,6],
			[9,1,6,n,8,4,5,n,7],
			[n,7,3,6,1,9,2,4,n],
			[2,4,n,7,5,n,6,n,1],
			[1,9,4,n,3,6,7,5,2],
			[n,3,7,5,4,2,n,1,9],
			[8,5,2,1,n,7,3,6,4]].

problem(3, P) :-
        P=[ [7,n,5,n,6,1,4,n,3],
			[3,6,9,n,2,8,n,7,5],
			[n,8,n,3,7,n,9,2,6],
			[9,1,6,n,8,4,5,n,7],
			[n,7,3,n,1,9,n,4,n],
			[2,4,n,7,5,n,6,n,1],
			[1,n,4,n,3,6,7,5,2],
			[n,3,7,n,4,2,n,1,9],
			[n,5,2,1,n,7,3,6,4]].


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 Apel:
	Optiune poate fi 0, 1, 2, sau 3 (Vezi deasupra predicatul problem).
	Exemplu Apel: sudokuDF(0).
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

sudokuBF(Optiune):-
	problem(Optiune, Rows),
	rezolva_bf(Rows,Solutie),
	afis(Solutie).

sudokuDF(Optiune):-
	problem(Optiune, Rows),
	rezolva_df(Rows,Solutie),
	afis(Solutie).

sudokuDFID(Optiune):-
	problem(Optiune, Rows),
	rezolva_dfid(Rows,Solutie),
	afis(Solutie).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	BF & DF & DFID
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
rezolva_df(NodInitial,Solutie):-depthfirst([],NodInitial,Solutie).

rezolva_bf(NodInitial,Solutie):-
	breadthfirst([[NodInitial]],Solutie).

rezolva_dfid(NodInitial,Solutie):-
	depth_first_iterative_deepening(NodInitial,Solutie).

breadthfirst([[Nod|Drum]|_],[Nod|Drum]):-scop(Nod).

breadthfirst([Drum|Drumuri],Solutie):-
	extinde(Drum,DrumNoi),
	append(Drumuri,DrumNoi,Drumuri1),
	breadthfirst(Drumuri1,Solutie).

extinde([Nod|Drum],DrumNoi):-
	bagof([NodNou,Nod|Drum], (ss(Nod,NodNou),\+(member(NodNou,[Nod|Drum]))),DrumNoi),!.

extinde(_,[]).
%%%%%%%%%%%%%%%%%%%%%%%%

depthfirst(Drum,Nod,[Nod|Drum]):-scop(Nod).

depthfirst(Drum,Nod,Solution):-
	ss(Nod,Nod1),
	\+ (member(Nod1,Drum)),
	depthfirst([Nod|Drum],Nod1,Solution).
%%%%%%%%%%%%%%%%%%%%%%%%

cale(Nod,Nod,[Nod]).

cale(PrimNod,UltimNod,[UltimNod|Drum]):-
	cale(PrimNod,PenultimNod,Drum),
	ss(PenultimNod,UltimNod),
	\+(member(UltimNod,Drum)).

depth_first_iterative_deepening(Nod,Sol):-
	cale(Nod,NodScop,Sol),
	scop(NodScop),!.
%%%%%%%%%%%%%%%%%%%%%%%%
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	Este Scop?
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

scop(SUDOKU):-
	toateCifre(SUDOKU).
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	De implementat...
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

%% TOATE CIFRE
% primeste toata matricea si e adevarat daca nu am niciun n
% toateCifre/1
% ...
toateCifre([]) :- !.
toateCifre([H | T]) :-
	\+member(n, H),
	toateCifre(T).

%% CAUTA LINIE CU POZITIE GOALA
% caut o pozitie care sa contina n
% membruGol/4
% ...
% membruGol(Linie, Matr, Contor, I, J)
membruGol(Linie, [Linie | _], C, C, J) :-
	member(n, Linie),
	cauta(Linie, n, J).

membruGol(Linie, [H | T], C, I, J) :-
	\+member(n, H),
	C1 is C + 1,
	membruGol(Linie, T, C1, I, J).

% cauta(L, E, Contor)
cauta([H | _], H, 1).
cauta([_ | T], H, C) :-
	cauta(T, H, C1),
	C is C1 + 1, !.

%%	VERIFICA PATRATE
% verificaPatratele/6
verificaPatratele([H1|_],[H2|_],[H3|_],1,1,E) :-
	H1\==E,
	H2\==E,
	H3\==E.

verificaPatratele([_|T1],[_|T2],[_|T3],Start,Stop,E) :-
	Start>1,
	Stop>1,
  Start1 is Start-1,
	Stop1 is Stop-1,
	verificaPatratele(T1,T2,T3,Start1,Stop1,E).

verificaPatratele([H1|T1],[H2|T2],[H3|T3],1,Stop,E) :-
	Stop > 1,
	Stop1 is Stop-1,
	H1\==E,
	H2\==E,
	H3\==E,
	verificaPatratele(T1,T2,T3,1,Stop1,E).

%% VERIFICA LINII
% primeste matrice, pozitie(numarul liniei) si intoarce linie
% extrageLinie/3
% ...
extrageLinie([H | _], 1, H).
extrageLinie([_ | T], C, H) :-
	C > 1,
	C1 is C - 1,
	extrageLinie(T, C1, H).

% extrageElemente/2
% ...
extrageElemente([], []).
extrageElemente([n | T], T1) :-
	extrageElemente(T, T1).
extrageElemente([H | T], [H | T1]) :-
	H \== n,
	extrageElemente(T, T1).


%% ADAUGA
% adpos/4
% addpos(Pos, X, L, LN)

adpos(1, X, [_ | T], [X | T]).
adpos(C, X, [H | T], [H | T1]) :-
	C > 1,
	C1 is C - 1,
	adpos(C1, X, T, T1).

%%	TRANSPUNE
transpune(M, MT) :-
	numel(M,Len),
	transpune(M,MT,1,Len).

transpune(_,[],Len1, Len2) :-
	Len2 =:= Len1-1.

transpune(M,[L|Rest],P, Len) :-
	getLine(M,L,P), P1 is P+1,
	transpune(M,Rest,P1, Len).

getLine([],[],_).
getLine([H|T],[E|T1],P) :-
	get(H,P,E),
	getLine(T,T1,P).

numel([],0).
numel([_|T], Len) :-
	numel(T,Len1),
	Len is Len1 + 1.

get([],_,[]).
get([H|_],1,H).
get([_|T],Pozitie, Element) :-
	Poz1 is Pozitie - 1,
	get(T, Poz1, Element).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	Succesor
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
%% predicatul ss asteapta sa facem O SINGURA mutare. De restul mutarilor se ocupa algoritmul de cautare!
%% Pasi:
/*
1. alegem unde o sa punem un numar
2. alegem un numar intre 1 si 9.
3. adaugam numarul
*/
ss(Sudoku, NouSudoku):- membruGol(Linie, Sudoku,1,PozitieLinie, PozElementGol),
						extrageElemente(Linie, Elemente),
						transpune(Sudoku, Coloane),
						extrageLinie(Coloane, PozElementGol, ColoanaLinie),
						extrageElemente(ColoanaLinie, ElementeColoana),
						member(X,[1,2,3,4,5,6,7,8,9]),
						\+ member(X,Elemente),
						\+ member(X,ElementeColoana),
						(Sudoku = [L1,L2,L3,L4,L5,L6,L7,L8,L9],
							(
								 PozitieLinie=<3 ->
									(
										PozElementGol =<3,verificaPatratele(L1,L2,L3,1,3,X);
										PozElementGol>3, PozElementGol =<6,verificaPatratele(L1,L2,L3,4,6,X);
										PozElementGol>6, PozElementGol =<9,verificaPatratele(L1,L2,L3,7,9,X)
									);
								 PozitieLinie>3, PozitieLinie=<6 ->
									(
										PozElementGol =<3 -> verificaPatratele(L4,L5,L6,1,3,X);
										PozElementGol>3, PozElementGol =<6 -> verificaPatratele(L4,L5,L6,4,6,X);
										PozElementGol>6, PozElementGol =<9 -> verificaPatratele(L4,L5,L6,7,9,X)
									);
								 PozitieLinie>6, PozitieLinie=<9 ->
									(
										PozElementGol =<3 -> verificaPatratele(L7,L8,L9,1,3,X);
										PozElementGol>3, PozElementGol =<6 -> verificaPatratele(L7,L8,L9,4,6,X);
										PozElementGol>6, PozElementGol =<9 -> verificaPatratele(L7,L8,L9,7,9,X)
									)
							)
						),
						adpos(PozElementGol, X, Linie, LinieNoua),
						adpos(PozitieLinie, LinieNoua, Sudoku, NouSudoku),!.

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	Afisare
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
afis(Sudoku) :-
	tell('/home/lucian/Documents/University/AI/Code/Lab8/sudoku.txt'),
	reverse(Sudoku,Ukodus), nl,
	afisare(Ukodus, 0), told.

afisare([],_).
afisare([H|T], NR):-write(NR), nl,nl, scrie(H),nl,nl, NR1 is NR + 1, afisare(T, NR1).


scrie([]).
scrie([H|T]):- scrie(H,1), nl, scrie(T).


scrie([], _).
scrie([Row|Rows], _) :-(number(Row),
        write(Row); write('_')), tab(3),
        scrie(Rows, _).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% END SUDOKU %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
