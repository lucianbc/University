word(atomar).
word(atentat).
word(antena).
word(tainic).
word(harnic).
word(atentie).
word(angina).
word(uniune).

word_letters(L) :-
  word(X),
  atom_chars(X, L).

rez(H11, H22, V11, V22) :-
  H1 = [_, H1V1, _, _, H1V2, _],
  H2 = [_, H2V1, _, _, H2V2, _],
  V1 = [_, H1V1, _, H2V1, _, _, _],
  V2 = [_, H1V2, _, H2V2, _, _],
  word_letters(H1),
  word_letters(H2),
  word_letters(V1),
  word_letters(V2),
  atom_chars(H11, H1),
  atom_chars(H22, H2),
  atom_chars(V11, V1),
  atom_chars(V22, V2).
