# Zadanie 7.1
Pliki `files/srvfifo.c`, `files/cntfifo.c`, `files/fifo.h` implementują komunikację klient-server opartą na kolejkach FIFO.  
Proszę wprowadzić modyfikację tak aby:
- Serwer po uruchomieniu nie zatrzymywał się na otwieraniu łącza czytania danych od klienta, tylko przechodził do oczekiwania na dane od klienta.
- Klient po wysłaniu komunikatu nie zatrzymywał się na otwieraniu łącza czytania danych od serwera, tylko przechodził do oczekiwania na dane od serwera.