is_leap_year(X) :-
    (\+ X mod 100 =:= 0, X mod 4 =:= 0, !);
    X mod 400 =:= 0.