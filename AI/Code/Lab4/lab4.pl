% ex 1
% scan(Element, Lista, Ix, Rez)
scan(E, [E | _], I, I).
scan(E, [_ | T], I, Poz) :-
  I2 is I + 1,
  scan(E, T, I2, Poz).
scan(E, L, Poz) :-
  scan(E, L, 1, Poz).

find(L, E, LR) :-
  findall(Poz, scan(E, L, Poz), LR).

% ex 2
at([H | _], 1, H) :- !.
at([_ | T], P, E) :-
  P1 is P - 1,
  at(T, P1, E).

at_all(List, [P | Pos], X) :-
  at(List, P, X);
  at_all(List, Pos, X).

show_all(L, LP) :-
  findall(X, at_all(L, LP, X), Rez),
  write(Rez).

% ex 3
% I. media_std(1, informatica, A).
media_std(Id_std, Fac, Avg) :-
  get_std(Id_std, Fac, S),
  get_grades_for(S, Grades),
  media(Grades, Avg).

% II. media_materie(cineticaChimica, A).
media_materie(Materie, Avg) :-
  get_grades_topic(Materie, Note),
  media(Note, Avg).

% III. media_facultate(informatica, A).
media_facultate(Facultate, Avg) :-
  get_grades_facultate(Facultate, Grades),
  media(Grades, Avg).

% IV. prima_facultate(F).
prima_facultate(Fac) :-
  facultate_medii_sortate(Medii),
  inverse(Medii, DescMedii),
  get_first(DescMedii, First),
  media_facultate(Fac, First).

% V. primul_student(fizicaCuantica, S).
primul_student(Materie, Student) :-
  get_grades_topic(Materie, Grades),
  setof(X, iterate(Grades, X), UqGrades),
  inverse(UqGrades, Inv),
  get_first(Inv, FirstGrade),
  catalog(Materie, Id_fac, FirstGrade, Id_std),
  get_std_id_fac(Id_std, Id_fac, Student).

% VI. top_n_studenti(fizicaCuantica, 2, S).
top_n_studenti(Materie, N, Student) :-
  get_grades_topic(Materie, Grades),
  setof(X, iterate(Grades, X), UqGrades),
  inverse(UqGrades, Inv),
  bagof(Std, map_to_student(Materie, Inv, Std), All_std),
  first_n(All_std, N, Studenti_List),
  iterate(Studenti_List, Student).

% VII. restantieri(informatica, R).
restantieri(Facultate, Restantier) :-
  get_materii_facultate(Facultate, Materii),
  iterate(Materii, Materie),
  write(Materie),
  write('\n'),
  restantieri_materie(Materie, Restantier).


% helper
get_grades_for(Std, Grades) :-
  Std = studenti(_, _, Id_fac, Id_std),
  bagof(Grade, M ^ catalog(M, Id_fac, Grade, Id_std), Grades).

% helper
get_std_id_fac(Id_std, Id_fac, X) :-
  studenti(N, P, Id_fac, Id_std),
  X =..[studenti, N, P, Id_fac, Id_std].

% helper
get_std(Id_std, Fac, X) :-
  facultati(Fac, Id_fac),
  get_std_id_fac(Id_std, Id_fac, X).

% helper
sum([], 0).
sum([H | T], S) :-
  sum(T, S1),
  S is S1 + H.

% helper
media(List, Avg) :-
  length(List, N), sum(List, Sum),
  Avg is Sum / N.

% helper
get_grades_topic(Topic, Grades) :-
  bagof(Grade, S^catalog(Topic, _, Grade, S), Grades).

% helper
get_grades_facultate(Facultate, Grades) :-
  facultati(Facultate, Id_fac),
  bagof(Grade, S^M^catalog(M, Id_fac, Grade, S), Grades).

% helper
facultate_medii_sortate(Medii) :-
  setof(Avg, F^media_facultate(F, Avg), Medii).

% helper
% inverse(L, Temp, Inversed)
inverse([], I, I).
inverse([H | T], I, Temp) :- inverse(T, [H | I], Temp).
inverse(L, I) :- inverse(L, [], I).

% helper
get_first([H | _], H).

% helper
iterate([H | _], H).
iterate([_ | T], X) :- iterate(T, X).

% helper
map_to_catalog(Materie, [N | _], Catalog) :-
  catalog(Materie, Id_fac, N, Id_std),
  Catalog =..[catalog, Materie, Id_fac, N, Id_std].
map_to_catalog(Materie, [_ | Note], Catalog) :-
  map_to_catalog(Materie, Note, Catalog).

% helper
map_to_student(Materie, [N | _], Std) :-
  catalog(Materie, Id_fac, N, Id_std),
  get_std_id_fac(Id_std, Id_fac, Std).
map_to_student(Materie, [_ | Note], Std) :-
  map_to_student(Materie, Note, Std).

% helper
first_n(_, 0, []) :- !.
first_n([], _, []) :- !.
first_n([H | T], N, [H | NL]) :-
  N1 is N - 1,
  first_n(T, N1, NL).

% helper
get_lower_than([], _, []) :- !.
get_lower_than([H | In], Max, [H | Out]) :-
  get_lower_than(In, Max, Out),
  H =< Max, !.
get_lower_than([_ | In], Max, Out) :-
  get_lower_than(In, Max, Out).

% helper
restantieri_materie(Materie, Restantier) :-
  get_grades_topic(Materie, Grades),
  setof(X, iterate(Grades, X), UqGrades),
  get_lower_than(UqGrades, 4, NoteRestante),
  bagof(Std, map_to_student(Materie, NoteRestante, Std), All_std),
  iterate(All_std, Restantier).

% helper
get_materii_facultate(Facultate, Materii) :-
  facultati(Facultate, Id_fac),
  setof(Materie, N^S^catalog(Materie, Id_fac, N, S), Materii).
