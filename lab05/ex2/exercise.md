# Zadanie 5.2
Zmodyfikuj program z pierwszego zadania w taki sposób, aby wątek główny (`main`) czekał na zakończenie pracy przez pozostałe wątki. Aby przetestować poprawność rozwiązania zmień kod poprzedniego programu w następujący sposób:
* Usuń wywołanie sleep(1); z funkcji main.
* Dodaj identyczne wywołanie sleep(1); na samym początku funkcji rozpoczęcia.
* Bezpośrednio przed instrukcją return w funkcji main wypisz informację o zakończeniu wątku głównego np.
```c
printf("End of the main thread!\n");
```