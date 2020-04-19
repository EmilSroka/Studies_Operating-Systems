# Zadanie 5.3
Program `files/func.c` realizuje sumowanie wartości w tablicy przy pomocy wątków.
Wątek główny wypełnia tablicę wartościami znajdującą się w globalnej instancji struktury `CommonData`.
Tworzy `NUM` nowych wątków, których zadaniem jest obliczenie sumy poszczególnych fragmentów tablicy:
* Długość każdego fragmentu tablicy wynosi `LENGTH`.
* Tablica składa się z `NUM` fragmentów/partycji.
* W sumie tablica posiada `NUM*LENGTH` elementów.
* Każdy wątek jako argument otrzymuje numer partycji tablicy, której elementy powinien zsumować.
Wątki zapisują obliczone przez siebie wyniki (cząstkowe) do pola `sum` zmiennej `CommonData`, do której dostęp jest synchronizowany mutex-ami.
Uzupełnij program, tak aby realizował powyższą funkcjonalność.