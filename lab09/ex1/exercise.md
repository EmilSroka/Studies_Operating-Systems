# Zadanie 9.1
Polecenie `stty(1)` służy do wyświetlania oraz zmiany ustawień linii terminala.  
W jaki sposób wyświetlić wszystkie aktualne ustawienia?

> stty -a

Jak przywrócić standardowe ustawienia ?

> stty sane

Jakie polecenie powłoki służy do odczytania nazwy pliku terminala? Jaka funkcja biblioteczna mu odpowiada (zwraca nazwę terminala)?

> tty oraz ttyname(3)

W programie `files/` przy użyciu odpowiednich funkcji i flag, ustanów nowe atrybuty terminala (zmodyfikuj odpowiednie wartości w polach struktury `termios`), aby w trakcie działania programu odczytywane były rzeczywiście pojedyncze znaki, a program dla każdej wczytywanej litery wyświetlał od razu jej odpowiednik w alfabecie Morse'a (przy czym program ma nie wyświetlać samej litery!). 