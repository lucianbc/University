cale(Nod, Nod, [Nod]).
cale(PrimNod, UltimNod, [UltimNod | Drum]) :-
  cale(PrimNod, PenultimNod, Drum),
  s(PenultimNod, UltimNod),
  \+(membru(UltimNod, Drum)).

depth_first_iterative_deepening(Nod, Sol) :-
  cale(Nod, NodScop, Sol),
  scop(NodScop).
