element_at([], _, _) :- !, false.

element_at([Head | Tail], 1, Head) :- !.

element_at([Head | Tail], N, Element) :-
    M is N - 1,
    element_at(Tail, M, Element).