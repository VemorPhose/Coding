remove_duplicates([], []) :- !.

remove_duplicates([Head | Tail], List) :-
    (member(Head, Tail), !,
    remove_duplicates(Tail, List));
    (remove_duplicates(Tail, L),
    List = [Head | L]).