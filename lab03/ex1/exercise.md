# Zadanie 3.1
Proszę przejrzeć manual do funkcji z rodziny `stat(2)`. Czym różnią się te funkcje?

> stat(2) zwraca status pliku wskazywanego przez ścieżkę dostępu
> lstat(2) zwraca status dowiązania symbolicznego wskazywanego przez ścieżkę dostępu
> fstat(2) zwraca status pliku wskazywanego przez deskryptor

Co reprezentuje flaga `S_IFMT` zdefiniowana dla pola `st_mode` w stukturze `stat`?

> Dzięki zastosowaniu tej flagi na polu st_mode uzyskujemy dostęp do tej części pola, która zawiera typ pliku.

Zmienna `sb` jest wypełnioną strukturą typu `struct stat`. Czy można sprawdzić typ pliku (np. czy plik jest urządzeniem blokowym) w następujący sposób?  
```c
if ((sb.st_mode & S_IFBLK) == S_IFBLK) {/* plik jest urządzeniem blokowym */}  
```

> Nie, należy użyć flagi S_IFMT i wtedy porównać do S_IFBLK

Proszę zmodyfikować funkcję `print_type` z pliku `files/stat_info.c` tak aby badała wszystkie możliwe typy pliku i wyświetlała odpowiednią informację.

Proszę zmodyfikować funkcję `print_perms` tak aby wyświetlała prawa dostępu do pliku w postaci numerycznej, np. 755.

Proszę zmodyfikować funkcję `print_owner` tak aby wyświetlała nazwę właściciela i grupy właścicieli oraz podawała identyfikatory w nawiasach, np. wta(1234) iastaff(5678)

Proszę zmodyfikować funkcję `print_perms` tak aby wyświetlone zostały prawa dostępu do pliku użytkownika uruchamiającego program np. Your permisions: read: yes, write: no, execute: no. 

Proszę zmodyfikować funkcję `print_size` tak aby wyświetlała informacje o rozmiarze pliku w sformatowany sposób - w kilo/megabajtach itp., np. 1MB zamiast 1024bytes

Proszę zmodyfikować funkcje `print_laststch`, `print_lastacc` i `print_lastmod` tak aby wyświetlały czas, który minął od daty ostatniej zmiany statusu/dostępu/modyfikacji, np. 3 day ago

Proszę zmodyfikować funkcje `print_name` tak, aby w przypadku gdy podany jako argument plik jest linkiem symbolicznym wyświetlał jego nazwę w formacie: nazwa_linku → nazwa_plik_na_ktory_wskazuje.