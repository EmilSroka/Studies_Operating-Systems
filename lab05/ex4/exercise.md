# Zadanie 5.3
Rozbuduj program `files/cond.c`, który ma realizować prostą funkcjonalność:
* 2 wątki inkrementują (funkcja `increment`) wartość zmiennej globalnej `globalvariable`.
* Trzeci wątek (funkcja `printinfo`) oczekuje na sygnał, aby oznajmić, że osiągnięto żądaną wartość `MAXVAL`.
* Po wypisaniu informacji wszystkie wątki i cały program kończą działanie.