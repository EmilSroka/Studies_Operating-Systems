# Zadanie 4.2
Program `files/save.c` pozwala na zapisanie określonej liczby bajtów do pliku o określonej nazwie.
Proszę rozbudować program tak aby wartość zmiennej `filename` (obowiązkowy) oraz `s` (opcjonalny) mogła być zadana jako argument wywołania programu.
Docelowo wywołanie programu save powinno mieć taką składnię:
```console
$ ./save [bytes] file
```

Rozbuduj program o sprawdzanie czy podano wystarczającą liczbę argumentów. Jeżeli nie to zakończ program zwracając 1.

Zmodyfikuj funkcję `main` programu shell ustawiając przed główną pętlą miękki limit maksymalnej wielkości tworzonych plików przez proces (`RLIMIT_FSIZE`) na wartość 50 bajtów. Sprawdź czy ustawiony limit jest dziedziczony przez procesy potomne wykorzystując w tym celu aplikację save. 