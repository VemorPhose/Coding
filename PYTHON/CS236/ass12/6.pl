membership(X, []) :-
    false.

membership(X, [Head | Tail]) :-
    (X = Head, !);
    membership(X, Tail).