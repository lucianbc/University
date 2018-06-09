% ex1
f2(X, Y) :- X < 3, Y = 0, !.
f2(X, Y) :- X > 3, X =<6, Y = 2, !.
f2(X, Y) :- X > 6, Y = 4.

f(X, 0) :- X =< 3.
f(X, 2) :- X > 3, X =< 6.
f(X, 4) :- X > 6.

% ex2
fact(X, 1) :- X =:= 1 ; X =:= 0.
fact(X, Y) :- X1 is X - 1, fact(X1, Y1), Y is Y1 * X.

% ex3
asoc(0) :- write('(0, zero)').
asoc(1) :- write('(1, unu)').
asoc(2) :- write('(2, doi)').
asoc(3) :- write('(3, trei)').
asoc(4) :- write('(4, patru)').
asoc(5) :- write('(5, cinci)').
asoc(6) :- write('(6, sase)').
asoc(7) :- write('(7, sapte)').
asoc(8) :- write('(8, opt)').
asoc(9) :- write('(9, noua)').

spell(0) :- asoc(0).
spell(1) :- asoc(1).
spell(3) :- asoc(3).
spell(4) :- asoc(4).
spell(5) :- asoc(5).
spell(6) :- asoc(6).
spell(7) :- asoc(7).
spell(8) :- asoc(8).
spell(9) :- asoc(9).
spell(X) :- X1 is X mod 10, X2 is X // 10, spell(X2), asoc(X1).

% ex4
spatii(0) :- write('').
spatii(X) :- X1 is X - 1, write(' '), spatii(X1).
stelute(0) :- write('').
stelute(1) :- write('*').
stelute(X) :- write('* '), X1 is X - 1, stelute(X1).
line(H, C) :- H1 is H - C, spatii(H1), stelute(C), spatii(H1), nl.
rec(N, 0) :- write('').
rec(N, C) :- C1 is C - 1, rec(N, C1), line(N, C).
bradut(N) :- rec(N, N).

% ex5
sstelute(1) :- write('*').
sstelute(X) :- write('**'), X1 is X - 1, sstelute(X1).
full_line(H, C) :- H1 is H - C, spatii(H1), sstelute(C), spatii(H1), nl.
in_line(H, C) :- H1 is H - C, spatii(H1), iin_line(C), spatii(H1), nl.
iin_line(2) :- write('*=*').
iin_line(X) :- write('*='), X1 is X - 2, eq(X1), write('=*').
eq(0) :- write('').
eq(1) :- write('=').
eq(X) :- write('=='), X1 is X - 1, eq(X1).
bradut2(X) :- rec2(X, X).
rec2(H, 1) :- full_line(H, 1).
rec2(H, H) :- X1 is H - 1, rec2(H, X1), full_line(H, H).
rec2(H, C) :- X1 is C - 1, rec2(H, X1), in_line(H, C).
