# Zadanie 2.1 
Jakie są standardowe deskryptory otwierane dla procesów?

> - 0: Standardowe wejście (stdin) - STDIN_FILENO
> - 1: Standardowe wyjście (stdout) - STDOUT_FILENO
> - 2: Standardowe wyjście diagnostyczne (stderr) - STDERR_FILENO

Jakie flagi trzeba ustawić w funkcji open aby otrzymać funkcjonalność funkcji creat?

> O_WRONLY, O_CREAT, O_TRUNC

W wyniku wykonania polecenia umask otrzymano 0022. Jakie prawa dostępu będzie miał plik otwarty w następujący sposób:  
open(pathname, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)

> 755

Proszę rozbudować program files/copy1.c o obsługę błędow. Proszę wyszczególnić następujące problemy: brak pliku oraz złe prawa dostępu do pliku.