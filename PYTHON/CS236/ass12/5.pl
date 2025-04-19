analyse_list([]) :-
    write('Empty List.'), !.

analyse_list(List) :-
    is_list(List),
    List = [Head | Tail],
    write('Head: '),
    write(Head), write('\n'),
    write('Tail: '),
    write(Tail), write('\n').