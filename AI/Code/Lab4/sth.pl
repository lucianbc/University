student(ion, 1, 1).
student(cristi, 2, 1).

find(Id, List) :- bagof(student(A, B, Id), student(A, B, Id), List).
