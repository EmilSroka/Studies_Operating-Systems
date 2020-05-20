# Zadanie 10.1
Jaki jest najwyższy numer portu dostępny do wykorzystania dla użytkownika niebędącego administratorem ?

> 65 535

Co oznaczają pojęcia:
* Network Byte Order?

> Określa kolejność zapisu bajtów liczby wielobajtowej.

* Big-Endian?

> Forma zapisu danych, w której najbardziej znaczący bajt zapisuje się jako pierwszy.

* Little-Endian?

> Forma zapisu, w której najmniej znaczący bajt zapisuje się jak pierwszy.

Proszę skompilować i przetestować program `files/server.c`.

```
$telnet remotehostname socket
```

Skompiluj i uruchom `files/client.c`. Przetestuj komunikację z serwerem.

Przetestuj komunikację, uruchamiając przykłady na dwóch różnych komputerach. Czy pojawiają się problemy? Jeżeli tak, to jakie i dlaczego?

> Problemem jest brak rekordu dns dla drugiego hosta.