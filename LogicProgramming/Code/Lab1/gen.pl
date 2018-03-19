male(rickard_stark).
male(eddard_stark).
male(brandon_stark).
male(benjen_stark).
male(rob_stark).
male(bran_stark).
male(rickon_stark).

male(aerys_targaryen).
male(rhaegar_targaryen).
male(viserys_targaryen).
male(aegon_targaryen).

male(john_snow).

female(rhaella_targaryen).
female(elia_targaryen).
female(daenerys_targaryen).
female(rhaenys_targaryen).

female(lyarra_stark).
female(catelyn_stark).
female(lyanna_stark).
female(sansa_stark).
female(arya_stark).

parent_of(rickard_stark, eddard_stark).
parent_of(rickard_stark, brandon_stark).
parent_of(rickard_stark, benjen_stark).
parent_of(rickard_stark, lyanna_stark).
parent_of(lyarra_stark, eddard_stark).
parent_of(lyarra_stark, brandon_stark).
parent_of(lyarra_stark, benjen_stark).
parent_of(lyarra_stark, lyanna_stark).

parent_of(catelyn_stark, robb_stark).
parent_of(catelyn_stark, sansa_stark).
parent_of(catelyn_stark, arya_stark).
parent_of(catelyn_stark, bran_stark).
parent_of(catelyn_stark, rickon_stark).

parent_of(eddard_stark, robb_stark).
parent_of(eddard_stark, sansa_stark).
parent_of(eddard_stark, arya_stark).
parent_of(eddard_stark, bran_stark).
parent_of(eddard_stark, rickon_stark).

parent_of(aerys_targaryen, rhaegar_targaryen).
parent_of(aerys_targaryen, viserys_targaryen).
parent_of(aerys_targaryen, daenerys_targaryen).

parent_of(rhaella_targaryen, rhaegar_targaryen).
parent_of(rhaella_targaryen, viserys_targaryen).
parent_of(rhaella_targaryen, daenerys_targaryen).

parent_of(rhaegar_targaryen, rhaenys_targaryen).
parent_of(rhaegar_targaryen, aegon_targaryen).

parent_of(elia_targaryen, rhaenys_targaryen).
parent_of(elia_targaryen, aegon_targaryen).

parent_of(rhaegar_targaryen, john_snow).
parent_of(lyanna_stark, john_snow).

father_of(F, C) :- male(F), parent_of(F, C).
mother_of(M, C) :- female(M), parent_of(M, C).

grandfather_of(G, C) :- male(G), parent_of(G, Y), parent_of(Y, C).
grandmother_of(G, C) :- female(G), parent_of(G, Y), parent_of(Y, C).

sister_of(S, P) :- female(S), parent_of(Y, P), parent_of(Y, S), S \== P.
brother_of(B, P) :- male(B), parent_of(Y, P), parent_of(Y, B), B \== P.

aunt_of(A, Pers) :- female(A), parent_of(Par, Pers), sister_of(A, Par).
uncle_of(U, Pers) :- male(U), parent_of(Par, Pers), brother_of(A, Par).
