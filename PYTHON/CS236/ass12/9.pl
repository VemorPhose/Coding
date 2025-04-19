replace([X], Old, New, [X]) :-
    X \== Old, !.

replace([X], Old, New, [New]) :-
    X = Old, !.

replace([Head | Tail], Old, New, ListOut) :-
    ((Head = Old, !,
    Cur = New);
    Cur = Head),
    replace(Tail, Old, New, Next),
    ListOut = [Cur | Next].