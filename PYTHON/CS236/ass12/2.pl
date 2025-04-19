max(X, Y, M) :-
    (X >= Y, M is X);
    (Y > X, M is Y).