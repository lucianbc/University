% Ex1: Zebra Puzzle
la_dreapta(X, Y) :-
  Y is X - 1.
la_stanga(X, Y) :-
  Y is X + 1.
langa(X, Y) :-
  (
    la_dreapta(X, Y);
    la_stanga(X, Y)
  ).

% casa(Numar, Nationalitate, Culoare, AnimalCompanie, Bautura, Tigari)
solutie(Strada, PosesorZebra) :-
  Strada = [
    casa(1, _, _, _, _, _),
    casa(2, _, _, _, _, _),
    casa(3, _, _, _, _, _),
    casa(4, _, _, _, _, _),
    casa(5, _, _, _, _, _)
  ],
  member(casa(_, englez, rosie, _, _, _), Strada),
  member(casa(_, spaniol, _, caine, _, _), Strada),
  member(casa(Nr_verde, _, verde, _, cafea, _), Strada),
  member(casa(_, ucrainean, _, _, ceai, _), Strada),
  member(casa(Nr_bej, _, bej, _, _, _), Strada),
  la_dreapta(Nr_verde, Nr_bej),
  member(casa(_, _, _, melci, _, 'Old Gold'), Strada),
  member(casa(_, _, galben, _, _, 'Kools'), Strada),
  member(casa(3, _, _, _, lapte, _), Strada),
  member(casa(1, norvegian, _, _, _, _), Strada),
  member(casa(Nr_chesterfields, _, _, _, _, 'Chesterfields'), Strada),
  member(casa(Nr_vulpe, _, _, vulpe, _, _), Strada),
  langa(Nr_chesterfields, Nr_vulpe),
  member(casa(Nr_kools, _, _, _, _, 'Kools'), Strada),
  member(casa(Nr_cal, _, _, cal, _, _), Strada),
  langa(Nr_kools, Nr_cal),
  member(casa(_, _, _, _, suc_de_portocale, 'Lucky Strike'), Strada),
  member(casa(_, japonez, _, _, _, 'Parliaments'), Strada),
  member(casa(Nr_norvegian, norvegian, _, _, _, _), Strada),
  member(casa(Nr_albastra, _, albastra, _, _, _), Strada),
  langa(Nr_norvegian, Nr_albastra),
  member(casa(_, PosesorZebra, _, zebra, _, _), Strada).
