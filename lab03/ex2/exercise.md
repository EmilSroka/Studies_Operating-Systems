# Zadanie 3.2
Do programu z poprzedniego ćwiczenia dopisz funkcję `print_content`, której deklaracja może wyglądać następująco: 
```c 
static void print_content(char *name);  
```
Powyższa funkcja implementuje następującą funkcjonalność:  
- Pyta użytkownika czy chce wypisać zawartość podanego jako argument pliku.
- Jeżeli tak, to otwiera i przy pomocy funkcji czytania asynchronicznego `aio_read(3)` odczytuje zawartość pliku i wypisuje ją na ekran.

