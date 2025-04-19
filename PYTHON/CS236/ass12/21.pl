gcd(X, 0, X) :- !.
gcd(0, X, X) :- !.

gcd(A, B, X) :-
    C is A mod B,
    gcd(B, C, X).