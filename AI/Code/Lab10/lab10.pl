% marcheaza(TablouInit, Marcaj, TablouUrm)
marcheaza([gol | Rest], Marcaj, [Marcaj | Rest]).
marcheaza([P | Rest], Marcaj, [P | UrmRest]) :-
  marcheaza(Rest, Marcaj, UrmRest).
