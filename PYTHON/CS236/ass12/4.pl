has_divisor(X, 1) :-
    false.

has_divisor(X, N) :-
    (write(N), X mod N =:= 0, !);
    M is N - 1,
    has_divisor(X, M).

is_prime(X) :-
    N is floor(sqrt(X)),
    has_divisor(X, N).