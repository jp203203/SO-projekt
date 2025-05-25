# Systemy Operacyjne 2 - serwer czatu z wielowątkową obsługą klienta
## Wprowadzenie
Aplikacja jest implementacją serwera oraz klienta czatu służącego do komunikacji pomiędzy 
użytkownikami. Serwer przyjmuje połączenia od wielu klientów i obsługuje odbieranie i wysyłanie
wiadomości jako osobne wątki programu. Klient, po połączeniu się z serwerem może wysyłać wiadomości
i odbierać wiadomości od innych użytkowników.
## Działanie serwera i klienta
Aby zachować niezależność aplikacji od systemu operacyjnego, wykorzystywana jest biblioteka
Boost.Asio. Po uruchomieniu serwera tworzony jest obiekt akceptora, który nasłuchuje na podanym
porcie TCP (w programie jest to port 12345) i akceptuje nowe połączenia od klientów. Dla każdego
zaakceptowanego połączenia tworzy nowe gniazdo i uruchamia wątek obsługujący odbieranie i wysyłanie
wiadomości klientów. Gdy serwer otrzyma wiadomość od jednego z klientów, rozsyła ją do wszystkich
użytkowników. Aby uniknąć sytuacji, w której dwa oddzielne wątki starają się uzyskać dostęp do listy
klientów jednocześnie, wykorzystywany jest mutex chroniący dostęp do listy. Po uruchomieniu klienta,
tworzony jest obiekt resolvera, który znajduje możliwe endpointy na adresie IP serwera i następnie
łączy się z nim. Po udanym połączeniu, uruchamiane są dwa wątki - jeden obsługujący odbieranie
wiadomości i drugi obsługujący ich wysyłanie. Dzięki temu zachowany jest pełny dupleks, pozwalający
klientowi na odbieranie i wysyłanie wiadomości jednocześnie.
## Instrukcja uruchomienia projektu
Aby odpalić aplikację na systemie Linux, należy skorzystać z istniejącego pliku CMakeLists.txt.
Po przejściu do katalogu projektu, należy stworzyć wewnątrz niego nowy katalog, w którym będzie
znajdował się plik makefile i przejść do niego.
W terminalu należy wpisać:
```
cmake -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release ..
```
Po uruchomieniu CMake, można zbudować plik wykonywalny przy pomocy polecenia:
```
make
```
Następnie, można uruchomić aplikację serwera oraz klienta. Wystarczy wpisać
```
./ChatServer
./ChatClient
```
Aby przetestować interakcję pomiędzy kilkoma klientami, można odpalić aplikację klienta kilka razy.
## Wątki, sekcje krytyczne
### Wątki
Wątki w czacie wykorzystywane są w dwóch miejscach: w aplikacji serwera tworzone są osobne
wątki dla kaźdego nowego klienta, które uruchamiają funkcję obsługującą komunikację z tym
jednym klientem. Funkcja ta nasłuchuje wiadomości od klienta: na początku pobiera od niego
nazwę użytkownika i po upewnieniu się, że użytkownik z podaną nazwą nie korzysta w danym momencie
z czatu, dodaje go do listy użytkowników (jako mapa nazw użytkownika na gniazda). Następnie 
przechodzi do odbierania wiadomości przeznaczonych dla innych użytkowników - po wykryciu
wiadomości, jest ona rozsyłana do każdego użytkownika i wysyłana na strumień wyjściowy serwera.
W aplikacji klienta podczas inicjalizacji uruchamiane są dwa wątki: jeden do odczytywania
wiadomości z serwera oraz drugi, do wysyłania wiadomości na serwer. Wątek odczytywania
wiadomości nasłuchuje wiadomości przychodzących z serwera i jeśli jakąś odbierze, to wysyła
ją na strumień wyjściowy. Wątek wysyłania wiadomości pobiera tekst wpisany przez użytkownika
i jeżeli wiadomość nie jest pusta lub nie jest komendą zakończenia połączenia (/q lub /Q) to
wysyła ją do serwera. Jeśli wiadomość jest pusta, to program ją ignoruje, a jeśli jest koemndą
zakończenia połączenia to połączenie jest zrywane i działanie obu wątków kończy się.
### Sekcje krytyczne
W projekcie na sekcję krytyczną można napotkać się dwóch miejscach, jednak w obu przypadkach
jest ona związana z listą połączonych użytkowników. Pierwszą z nich jest dostęp do listy
użytkowników podczas dodawania klienta do tej listy przez wątek. Drugą sekcją krytyczną jest
rozsyłanie wiadomości do użytkowników - wątek musi uzyskać dostęp do listy użytkowników aby
wysłać wiadomość na ich gniazda. Do blokowania dostępu do listy klientów wykorzystywany jest
mutex - bez niego, wiele wątków mogłoby starać się uzyskać dostęp do listy klientów
jednocześnie, co mogłoby doprowadzić do uszkodzenia struktury mapy, prób odczytu elementu w
trakcie zmiany przez inny wątek, czy wyścigów danych.
