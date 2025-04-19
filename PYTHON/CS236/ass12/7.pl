my_length([], L) :-
    L = 0.

my_length([Head | Tail], L) :-
    my_length(Tail, M),
    L is M + 1.