# Flapy Game

Prosta gra 2D stworzona w C++ z użyciem **Allegro 4**, inspirowana klasycznym Flappy Bird.  
Obsługuje podstawową fizykę ptaka, przeszkody (rury), tło i ekran Game Over.

Projekt został przygotowany w 2016 roku na dni otwarte technikum, do którego wtedy uczęszczałem w celu zachęcenia odwiedzających do wybrania naszej szkoły.

---

## Spis treści

- [Sterowanie](#sterowanie)
- [Wymagania](#wymagania)
- [Budowanie projektu](#budowanie-projektu)
- [Struktura projektu](#struktura-projektu)
- [Mechanika gry](#mechanika-gry)

---

## Setrowanie
| Klawisz | Funkcja       |
| ------- | ------------- |
| Spacja  | Skok ptaka    |
| P       | Pauza / Wznów |
| R       | Restart gry   |
| ESC     | Wyjście z gry |

## Wymagania

- Zainstalowany **CMake** (min. 3.15)
- Kompilator C++ (g++, clang++, MSVC)
- Biblioteka **Allegro 4** dostępna w systemie

## Budowanie projektu

### Linux

```bash
mkdir build
cd build
cmake ..
make
./FlappyBird
```

### Windows (MinGW)
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
FlappyBird.exe
```

### Struktura projektu

- main.cpp – główna pętla gry, inicjalizacja i logika restartu
- obiekty.cpp / obiekty.h – klasy gry: bird, object, background, fbpipe
- assets/flapy.pcx – grafiki ptaka, rur i tła
- config.h – konfiguracja i definicje

### Mechanika gry

- Bird (ptak) – fizyka oparta na prostych równaniach ruchu w pionie, uwzględnia skok i grawitację
- Rury (fbpipe) – przesuwają się w lewo z losową wysokością, licznik punktów przy przejściu ptaka
- Tło – przewija się w pętli, tworząc efekt ruchu
- Collision – detekcja kolizji AABB (axis-aligned bounding box)
- Wait / Timery – klasy zarządzające czasem