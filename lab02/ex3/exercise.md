# Zadanie 2.3 
Dwa deskryptory: fd1 i fd2 użyto do otwarcia pliku podając tę samę ścieżkę dostępu do pliku. Wskaźnik pliku ustawiony jest na początku pliku. Następnie korzystając z deskryptora fd1 wykonano operację zapisania 100b do pliku. Następnie przy użyciu deskryptora fd2 wykonano operację czytania z pliku. Pytanie: Na jakiej pozycji jest wskaźnik pliku? Jakie dane odczytano przy użyciu fd2?

> Wskaźnik pliku (offset) (zarówno fd1, jak i fd2) jest na 99 pozycji.   
> Przy użyciu fd2 odczytano dane zapisane przy pomocy fd1.   

Do otwarcia pliku użyto jednego deskryptora fd3. Następnie wykonano kolejno operację pisania 100b i czytania 100b. Na jakiej pozycji jest wskaźnik pliku? Co zostało przeczytane?

> Wskaźnik jest na 199 pozycji.
> Został przeczytany fragment pliku od 100 do 199 pozycji.

Czy każdorazowe poprzedzenie operacji pisania ustawieniem wskaźnika pliku na końcu pliku za pomocą funkcji lseek daje taki sam rezultat jak otwarcie pliku w trybie z ustawioną flagą O_APPEND? Odpowiedź uzasadnij.

> Tak, ponieważ przy użyciu flagi O_APPEND funkcja write używa niejawnie lseek.

Jak wygląda wywołanie funkcji lseek które:
- ustawia wskaźnik na zadanej pozycji?  
> lseek(fileDescriptor, position, SEEK_SET);
- znajduje koniec pliku?  
> lseek(fileDescriptor, 0, SEEK_END);
- zwraca bieżącą pozycję wskaźnika?  
> lseek(fileDescriptor, 0, SEEK_CUR);
 
Proszę zmodyfikować (uprościć) funkcję z files/backwards.c zamieniając wywołania lseek i read na użycie funkcji pread. 

Napisać program realizujący funkcjonalność polecenia tail.