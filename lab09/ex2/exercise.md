# Zadanie 9.2

Skompiluj i uruchom program `files/sessions.c`

Jakie polecenie pozwala utworzyć nową sesję dla procesu potomnego ?
> setsid

Jak przy użyciu polecenia ps wyświetlić sid procesu?  
> ps -o pid,sid,tt,time,cmd

Przy użyciu funkcji `setsid` stwórz demona, który będzie pracował nawet po wylogowaniu się użytkownika. Demon co kilkadziesiąt sekund ma losować 6 liczb z przedziału \[1,49] i zapisywać je do pliku `wyniki_lotto`. Po uruchomieniu demona, zamknij terminal, w którym został uruchomiony, natomiast w innym terminalu sprawdź, czy rzeczywiście co kilkadziesiąt sekund zmieniają się wyniki losowań. 