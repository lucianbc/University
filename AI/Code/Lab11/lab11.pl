% ex1
it([H | _], H, 1).
it([_ | T], E, I) :-
  it(T, E, I1),
  I is I1 + 1.

filter(Matrix, Element) :-
  it(Matrix, L, Line),
  it(L, Element, Column),
  Element < (Line + Column).

collect(Matrix, Elements) :-
  findall(X, filter(Matrix, X), Elements).

print([]) :- nl.
print([H | T]) :-
  write(H),
  write(' '),
  print(T).

ex1(Matrix) :-
  collect(Matrix, Elements),
  print(Elements).

% ex2
tree(1, t(
  t(
    t(n, 2, n),
    3,
    n
  ),
  1,
  t(
    t(
      t(n, 6, n),
      7,
      t(n, 8, n)
    ),
    4,
    n
  )
  )
).

nr_elem(n, 0).

nr_elem(t(S, _, D), N) :-
  nr_elem(S, Ns),
  nr_elem(D, Nd),
  N is Ns + Nd + 1.

ex_2(n, []) :- !.
ex_2(t(S, R, D), L) :-
  ex_2(S, Ls),
  ex_2(D, Ld),
  nr_elem(S, Ns),
  nr_elem(D, Nd),
  write(Ns), write(' '), write(Nd), write(' | '),
  (
    Ns =:= Nd, conc(Ls, [R | Ld], L), !;
    conc(Ls, Ld, L)
  ).

conc([], L, L).
conc([H | L1], L2, [H | L3]) :-
  conc(L1, L2, L3).

% ex3
om(popescu, ana, 20).
om(georgescu, alex, 53).
om(ionescu, george, 14).
om(popescu, denisa, 6).
om(ionescu, liliana, 78).
om(georgescu, oana, 35).
om(georgescu, vlad, 14).
om(ionescu, anca, 2).
om(popescu, ioana, 40).
om(ionescu, dan, 16).

group(Val) :-
  setof(Varsta, Prenume ^ om(Nume, Prenume, Varsta), Grupe),
  Grupe = [First | _],
  om(Nume, Prenume, First),
  Val = Nume / Prenume / First.

show([]).
show([H | Fam]) :-
  H = Nume / Prenume / First,
  write(Nume), write(': '), write(Prenume),
  write(' '), write(First), write('\n'),
  show(Fam).

ex3 :-
  tell('./fam.txt'),
  bagof(V, group(V), Fams),
  show(Fams),
  told.
