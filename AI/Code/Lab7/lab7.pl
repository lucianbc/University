%% START mutare blocuri
% ----------------------------------------
% Cautare de tip breadth-first
% ----------------------------------------
rezolva_b(NodInitial,Solutie) :-
  breadthfirst([[NodInitial]],Solutie).

breadthfirst([[Nod|Drum]|_],[Nod|Drum]) :-
  scop(Nod).

breadthfirst([Drum|Drumuri],Solutie) :-
  extinde(Drum,DrumNoi),
  append(Drumuri,DrumNoi,Drumuri1),
  breadthfirst(Drumuri1,Solutie).

extinde([Nod|Drum],DrumNoi):-
  bagof([NodNou,Nod|Drum], (
    s(Nod,NodNou),
    \+ (member(NodNou,[Nod|Drum]))
    ), DrumNoi
  ),!.

extinde(_,[]).
% ----------------------------------------
%Cautare de tip depth-first cu mecanism de detectare a ciclurilor
% ----------------------------------------
rezolva(Nod,Solutie) :-
  depthfirst([],Nod,Solutie).

depthfirst(Drum, Nod,[Nod|Drum]) :-
  scop(Nod).

depthfirst(Drum,Nod,Solution) :-
  s(Nod,Nod1),
  \+ (member(Nod1,Drum)),
  depthfirst([Nod|Drum],Nod1,Solution).
% ----------------------------------------
%Cautare de tip iterative deepening
% ----------------------------------------
cale(Nod,Nod,[Nod]).
cale(PrimNod,UltimNod,[UltimNod|Drum]):- cale(PrimNod,PenultimNod,Drum),
s(PenultimNod,UltimNod),
\+(member(UltimNod,Drum)).
depth_first_iterative_deepening(Nod,Solutie):- cale(Nod,NodScop,Solutie),
scop(NodScop),!.
% ----------------------------------------
%Predicatele specifice problemei mutarii blocurilor
% ----------------------------------------
s(Lista_stive,Lista_stive_rez):-
  member(X,Lista_stive),X=[Varf|_],
  det_poz_el(Lista_stive,N,X),
  sterg_la_n(Lista_stive,Lista_stive_inter,N),
  member(Y,Lista_stive),
  det_poz_el(Lista_stive,N1,Y),N1\==N,
  adaug_la_n(Varf,Lista_stive_inter,Lista_stive_rez,N1).
% configuratia initiala a stivelor.
initial([[d],[a,b],[c]]).
% configuratia-scop a stivelor, cea pe care o cauta fiecare dintre algoritmii de cautare folositi.
scop([[],[a,b,c,d],[]]).
% Mai jos se gasesc trei posibilitati de apel pentru problema mutarii blocurilor. Alegeti cate una, in
% functie de ce algoritm doriti sa folositi
% Inlocuiti calea de mai jos cu una catre directorul in care lucrati voi
pb_bf:-tell('C:\\bloc_mut_ies_bf.txt'), initial(S),rezolva_b(S,Solutie),afisare(Solutie),told.
pb_df:-tell('C:\\bloc_mut_ies_df.txt'), initial(S),rezolva(S,Solutie),afisare(Solutie),told.
pb_df_id:-tell('C:\\block_mut_ies_df_id_.txt'), initial(S), depth_first_iterative_deepening(S,Solutie),
afisare(Solutie),told.
% ----------------------------------------
%% END mutare blocuri
% ----------------------------------------

% det_poz_el(Lista, Poz, Element)
det_poz_el([H | _], N, H, N).
det_poz_el([_ | T], N, E, I) :-
  I1 is I + 1,
  det_poz_el(T, N, E, I1).
det_poz_el(L, P, E) :- det_poz_el(L, P, E, 1).

% sterg_la_n(Lis, Lfin, N)
sterg_la_n([H | T], Lfin, N, N) :-
  H = [_ | H1],
  Lfin = [H1 | T],
  !.
sterg_la_n([H | T], [H | T2], N, I) :-
  I1 is I + 1,
  sterg_la_n(T, T2, N, I1).

sterg_la_n(Lis, Lfin, N) :- sterg_la_n(Lis, Lfin, N, 1).

% adaug_la_n(Elem, Lis, Lfin, N)
adaug_la_n(E, [H | T], Lfin, N, N) :-
  Hd = [E | H],
  Lfin = [Hd | T],
  !.
adaug_la_n(E, [H | T], [H | T2], N, I) :-
  I1 is I + 1,
  adaug_la_n(E, T, T2, N, I1).

adaug_la_n(E, Lis, Lfin, N) :- adaug_la_n(E, Lis, Lfin, N, 1).

afisare([]).
afisare([H | T]) :- afis1(H), afisare(T).

afis1(L) :- lungime(L, 0), write('\n'), !.
afis1(L) :- lungime(L, Lung), afis2(L, Lung, L1), afis1(L1).

max(A, B, A) :- A > B, !.
max(A, B, B) :- A =< B.

lungime([], 0).
lungime([H | T], Max) :-
  lungime(T, MMax),
  length(H, CMax),
  max(MMax, CMax, Max).

afis2([], _, []) :- write('\n'), !.

afis2([H | T], Lung, [H1 | T1]) :-
  length(H, Lung),
  H = [E | Rest],
  write(E),
  H1 = Rest,
  afis2(T, Lung, T1),
  !.

afis2([H | T], Lung, [H | T1]) :-
  write(' '),
  afis2(T, Lung, T1).
