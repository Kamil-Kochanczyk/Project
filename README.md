Kamil Kochańczyk, 16.06.2022, Kraków


------------------------
Projekt zaliczeniowy C++
------------------------


Jak uruchomić?
- do uruchomienia programu wystarczy folder Distribute
- aby uruchomić program należy uruchomić aplikację Project.exe
- ścieżka: Distribute/Release/Project.exe

Uwaga: aby uruchomić program na Linuxie należy np. zainstalować program WineHQ, który pozwala uruchamiać pliki .exe na Linuxie, i otworzyć za jego pomocą aplikację Project.exe, np. używając komendy "wine Project.exe", gdy się jest w tym samym folderze co aplikacja

Uwaga: może się też zdarzyć, że po wyjściu z jakiejś gry i powrocie do menu, nie będzie widać żadnych opcji, a jedynie czarny ekran. Jest to bug, lecz po kliknięciu strzałki w górę lub w dół, opcje powinny znów się pojawić.


Opis:
- program, który wyświetla dwa okna - menu i konsolę/terminal
- menu pozwala wybrać i zagrać w jedną z 4 gier
- konsola wyświetla informacje tekstowe, np. instrukcję danej gry, a także wyniki gracza
- dostępne gry to: Aim Trainer, Reaction Time, Sequence Memory, Visual Memory


Gry:
- Aim Trainer to gra, która sprawdza koordynację ręka-oko; gracz musi jak najszybciej zniszczyć 30 tarcz, które pojawiają się w losowych miejscach na ekranie

- Reaction Time to gra, która sprawdza refleks; gracz musi chwilkę poczekać aż kolor ekranu zmieni się z czerwonego na zielony i jak najszybciej kliknąć wtedy ekran

- Sequence Memory to gra, która sprawdza pamięć; na ekranie pojawią się kwadraciki, które będą podświetlane w losowej kolejności, a zadaniem gracza będzie kliknąć te same kwadraciki, które zostały podświetlone, i to w tej samej kolejności

- Visual Memory to gra, która sprawdza pamięć wizualną; na ekranie pojawią się kwadraciki, niektóre z nich zostaną podświetlone tworząc pewien wzór, a zadaniem gracza będzie odtworzyć później ten wzór

Więcej informacji na temat każdej gry pojawi się w konsoli po uruchomieniu programu.


Kody źródłowe (znajdują się w folderze Project):
- AimTrainer.cpp
- AimTrainer.h
- Game.cpp
- Game.h
- Main.cpp
- Menu.cpp
- Menu.h
- ReactionTime.cpp
- ReactionTime.h
- SequenceMemory.cpp
- SequenceMemory.h
- VisualMemory.cpp
- VisualMemory.h
