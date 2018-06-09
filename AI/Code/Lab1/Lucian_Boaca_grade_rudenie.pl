ct(ana, vasile).
ct(sergiu, ioana).
ct(gheorghe, andrada).
ct(claudia, alexandru).
ct(florin, alina).
ct(andrei, sorana).

% copil, parinte
cp(georgiana, florin).
cp(alin, sergiu).
cp(alina, sergiu).
cp(ioana, ana).
cp(dan, ana).
cp(gheorghe, ana).
cp(andrada, claudia).
cp(claudiu, gheorghe).
cp(andrei, gheorghe).
cp(bogdan, andrei).

barbat(florin).
barbat(sergiu).
barbat(vasile).
barbat(alexandru).
barbat(andrei).
barbat(gheorghe).
barbat(alin).
barbat(dan).
barbat(claudiu).
barbat(bogdan).

femeie(georgiana).
femeie(alina).
femeie(ioana).
femeie(ana).
femeie(andrada).
femeie(claudia).
femeie(sorana).

casatorit(X, Y) :- ct(X, Y) ; ct(Y, X).

copil(C, P) :- cp(C, P) ; cp(C, S), casatorit(P, S).
copil(C, P1, P2) :- copil(C, P1), copil(C, P2).

parinte(P, C) :- copil(C, P).

% A sora M
sora(A, M) :- femeie(A), parinte(P, A), parinte(P, M), A\=M.
% M frate A
frate(M, A) :- barbat(M), parinte(P, A), parinte(P, M), A\=M.

sib(C1, C2) :- C1\=C2, parinte(P, C1), parinte(P, C2).

bunic(B, C) :- barbat(B), parinte(B, X), parinte(X, C).
bunica(B, C) :- femeie(B), parinte(B, X), parinte(X, C).

bun(B, C) :- parinte(B, X), parinte(X, C).

strabunic(S, C) :- barbat(S), parinte(S, X), (bunic(X, C) ; bunica(X, C)).
strabunica(S, C) :- femeie(S), parinte(S, X), (bunica(X, C) ; bunic(X, C)).

verisor(V, A) :- barbat(V), bun(X, V), bun(X, A).
verisoara(V, A) :- femeie(V), bun(X, A), bun(X, V).

unchi(U, C) :- parinte(X, C), (frate(U, X) ; sora(Y, X) , casatorit(U, Y)).
matusa(M, C) :- parinte(X, C), (sora(M, X) ; frate(Y, X), casatorit(M, Y)).

cumnat(C, S) :- casatorit(X, S) , ( frate(C, X) ; frate(C, Y) , casatorit(Y, X) ).
cumnata(C, S) :- casatorit(X, S), ( sora(C, X) ; sora(C, Y), casatorit(Y, X)  ).
    
