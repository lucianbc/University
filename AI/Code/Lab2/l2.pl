culoare(rosu).
culoare(galben).
culoare(alb).

frunze(alterne).
frunze(mari).
frunze(nervuri_paralele).

petale(multepetale).
petale(petalegalbene).
petale(grupate_trompeta).

fl(trandafir, rosu, alterne, multepetale).
fl(floarea_soarelui, galben, mari, petalegalbene).
fl(crin, alb, nervuri_paralele, grupate_trompeta).

floare(A, X, Y, Z) :-
  culoare(X),
  frunze(Y),
  petale(Z),
  fl(A,X,Y,Z).
