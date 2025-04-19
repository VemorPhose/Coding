split_list(Threshold, [], [], []) :- !.

split_list(Threshold, [Head | Tail], L, GE) :-
    (Head < Threshold, !,
    split_list(Threshold, Tail, L1, GE),
    L = [Head | L1]);
    split_list(Threshold, Tail, L, GE1),
    GE = [Head | GE1].