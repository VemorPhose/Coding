palindrome_helper([], []) :-
    true.

palindrome_helper([Head1 | Tail1], [Head2 | Tail2]) :-
    Head1 = Head2,
    palindrome_helper(Tail1, Tail2).

palindrome(Atom) :-
    atom_chars(Atom, List1),
    reverse(List1, List2),
    palindrome_helper(List1, List2).