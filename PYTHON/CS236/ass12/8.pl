last1([Element], Element) :- !.

last1([Head | Tail], Element) :-
    last1(Tail, Element).

last2(List, Element) :-
    append(Pre, [Element], List).