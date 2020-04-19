# Zadanie 5.3
Uzupełnij program `files/randomsearch.c` o:
* Przesłanie do tworzonych wątków argumentów (wykorzystaj strukturę `thread_params`) zawierających informację o:
    * Indeksie wątku, który jest równy wartości `ti` w pętli tworzącej wątki.
    * Wartości szukanej.
* Informację o liczbie iteracji jakie wykonał każdy kończący się wątek w celu odnalezienia wartości (wykorzystaj mechanizmy czyszczące `pthread_cleanup_push`, `pthread_cleanup_pop`, ).

