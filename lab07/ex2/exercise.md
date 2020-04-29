# Zadanie 7.2
Pliki `files/cntpsx.c`, `files/psx.h`, `files/srvpsx.c` zawierają błąd:
- Na czym on polega?

> 3\. atrybut funkcji `mq_receive` (czyli wielkość bufora do zapisania wiadomości) jest mniejszy niż `mq_msgsize` (maksymalna wielkość waidomości)

- Jak go naprawić?

> Należy ustawić odpowiednią wielkość `mq_msgsize` w funckji `mq_open`

- Gdzie można sprawdzić limity ilości i rozmiaru wiadomości?

> W strukturze `mq_attr` pobranej z pomocą funkcji `mq_getattr`