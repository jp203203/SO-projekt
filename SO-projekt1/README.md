# Systemy Operacyjne 2 - problem ucztujących filozofów
## Opis problemu
Problem ucztujących filozofów to klasyczny problem zadania synchronizacji procesów. Sytuacja opisuje pięciu filozofów siedzących przy okrągłym stole,
którzy naprzemiennie rozmyślają lub jedzą makaron. Każdy filozof ma przed sobą talerz z makaronem oraz dwa widelce, które dzieli z filozofami siedzącymi obok niego.
Aby przystąpić do jedzenia, filozof potrzebuje dwóch widelców znajdujących się po jego lewej i prawej stronie - może jednak dojść do sytuacji, w której jeden, lub oba
z widelców będą zajęte przez sąsiednich filozofów. Filozofowie w tym problemie reprezentują procesy działające współbieżnie, a widelce - zasoby dzielone pomiędzy
tymi procesami. Dwa główne zagrożenia w tym problemie stanowią zaklesczenie oraz głodzenie. Zakleszczenie ma miejsce w sytuacji, gdy każdy z filozofów np. podniesie lewy
widelec i będzie czekał na widelec prawy - który jest zajęty przez sąsiedniego filozofa. W kontekście procesów współbieżnych odpowiada to sytuacji, w której wiele zadań
jednocześnie konkuruje o wyłączny dostęp do zasobów. Głodzenie ma miejsce wtedy, gdy jeden z filozofów nie przestaje jeść, więc filozof siedzący obok niego czeka w
nieskończoność na swoją kolej - tutaj analogia również dobrze reprezentuje rzeczywisty problem. Jego rozwiązaniem jest np. ograniczenie czasu dostępu procesu do zasobu.
## Instrukcja uruchomienia projektu
W katalogu cmake-build-debug znajduje się plik wykonywalny projektu "SO2_Projekt1.exe". Aby odpalić go na systemie Windows, należy odpalić linię komend w lokalizacji
pliku i wpisać:
```
start SO2_Projekt1 [liczba_filozofow]
```
Aby odpalić projekt na systemie Linux, należy najpierw zainstalować program **Wine**, pozwalający na uruchamianie plików .exe w środowisku Linux. Po przejściu do katalogu,
w którym znajduje się plik wykonywalny, należy wpisać w terminalu:
```
wine SO2_Projekt1.exe [liczba_filozofow]
```
Aby nie korzystać z programu Wine, należy samemu zbudować aplikację. W katalogu plików należy odpalić terminal i skorzystać z kompilatora G++:
```
g++ main.cpp Philosopher.cpp -o philosophers -std=c++17 -pthread
```
Aby uruchomić program, wystarczy wpisać w terminalu:
```
./philosophers [liczba_filozofow]
```

Liczba filozofów nie może być mniejsza od 2, w innym wypadku wywołanie programu zakończy się błędem.
## Wątki, sekcje krytyczne
### Wątki
W problemie ucztujących filozofów, przez wątki reprezentowani są tytułowi filozofowie. Ich działanie opiera się na nieustannym "rozmyślaniu" oraz "jedzeniu" (obie
funkcje realizujące te zachowanie wykonywane są w nieskończonej pętli). "Rozmyślanie" realizowane jest przez funkcję *think*, której jedynym zadaniem jest czekanie
przez losowy okres czasu z przedziału od 10 do 20 sekund. "Jedzenie" jest realizowane przez funkcję *eat*. Podczas wykonywania tej funkcji, proces czeka, aż oba "widelce"
będą wolne, aby samemu je zablokować. Po zablokowaniu obu, proces losowo czeka od 10 do 20 sekund, a na koniec zwalnia "widelce". Wątki informują o swoich stanach
(rozmyślanie, jedzenie, oczekiwanie na widelce).
### Sekcje krytyczne
W realizowanym projekcie, na sekcje krytyczne można napotkać się w dwóch miejscach: pierwszym z nich jest dostęp do "widelców", które w rzeczywistości są realizowane
jako mutexy, czyli blokady wzajemnego wykluczania. Aby uniknąć zakleszczenia, w kodzie wykorzystywana jest funkcja *std::lock*, która zapewnia, że wszystkie mutexy
przekazane jako argumenty będą zwolnione, zanim proces zablokuje do nich dostęp, co zapobiega występowaniu zakleszczeń.  
Kolejną sekcją krytyczną w programie jest dostęp do wyjścia konsoli *std::cout*. Bez jej rozwiązania, powiadomienia o stanach wątków byłyby "pmieszane" i ciężko byłoby
rozczytać się z któregokolwiek z nich. Aby zapewnić, że wszystkie wiadomości o stanach są spójne i odpowiednio poukładane, dodano kolejny, globalny mutex do klasy
*Philosopher*. Jego zadaniem jest zapewnienie dostępu na wyłączność do strumienia wyjściowego dla wątku, oraz zwolnienie tego dostępu po przekazaniu wiadomości o zmianie
stanu.
