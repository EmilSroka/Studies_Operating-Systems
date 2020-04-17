# Zadanie 4.1
W folderze `files` znajdują się trzy pliki implementujące prostą powłokę:
* `shell.c` - główny plik aplikacji, w tym pliku wprowadzamy modyfikacje w celu wykonania ćwiczeń.
* `funcs.h` - plik nagłówkowy zawierający definicję struktury, stałych oraz deklaracje funkcji.
* `funcs.c` - plik z funkcjami których nie trzeba modyfikować aby zrealizować ćwiczenia, jednak trzeba się z nim zapoznać.

Przetestuj działanie powłoki wpisując polecenia np.:
```
@ ls
@ ls -l
@ echo test
@ ps
@ top
```
Dlaczego znak zachęty nie wyświetla się dopiero po wykonaniu procesu?

> Ponieważ funkcja nie czeka na zakończenie procesu potomnego, tylko natychmiastowo wypisuje znak zachęty.

Zmodyfikuj funkcję executecmds w taki sposób aby można było zakończyć działania powłoki poleceniem `exit`.

Po uruchomieniu powłoki spróbuj uruchomić polecenie, które nie istnieje wpisując np. `werwersdd`. Następnie wpisz polecenie `exit`.
Co się stało? Dlaczego polecenie nie działa poprawnie? Jak naprawić ten błąd?

> Ponieważ polecenie nie istnieje, funkcja execvp nie zmieniła kodu programu (process image). W rezultacie mamy już dwie działające jednocześnie powłoki. Uruchomienie exit pozwala wyjść z jednej powłoki, natomiast druga dalej działa w tle, czytając stdin. Aby naprawić błąd, wystarczy w przypadku błędu execvp zamknąć proces.  

Zmodyfikuj funkcję `executecmds` w taki sposób aby oczekiwała na zakończenie się uruchomionego procesu oraz uzupełnij obsługę błędów nowoużytej funkcji.
Przetestuj modyfikację jak w p. 1. i zwróć uwagę czy znak zachęty pojawia się dopiero po zakończeniu procesu.

Zmodyfikuj funkcję `executecmds` w taki sposób aby do zmiennej `int procres` zapisywała wartość oznaczającą sposób zakończenia się ostatniego procesu (1 w przypadku pomyślnego zakończenia, 0 w przeciwnym wypadku) a następnie wyświetlała kod wyjścia procesu.
Przetestuj zmiany wpisując np.:
```
@ echo test             # powinno wyświetlić 0
@ ls                    # powinno wyświetlić 0
@ ls hhh                # powinno wyświetlić wartość różną od 0 (o ile folder hhh nie istnieje)
@ cat aaa               # powinno wyświetlić wartość różną od 0 (o ile plik aaa nie istnieje lub nie da się go przeczytać)
```

Zmodyfikuj funkcję `parsecmd`, w taki sposób, aby poprawnie interpretowała operatory `||` oraz `&&`, a następnie zmodyfikuj funkcję `executecmds`, w taki sposób, aby uruchamiała procesy zgodnie z podanymi operatorami `&&` oraz `||`. 