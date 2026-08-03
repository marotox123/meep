# meep

Proste narzędzie CLI w C do wyszukiwania fragmentu tekstu w pliku, linia po linii (coś w stylu uproszczonego `grep`).

## Build

```sh
gcc main.c mainparser.c tekstparser.c match.c -o meep
```

## Użycie

```sh
./meep <szukany_tekst> <plik>
```

Przykład:

```sh
./meep haha haha.txt
```

Program wypisze wszystkie linie z pliku zawierające podany fragment tekstu.

> Flagi `-n` (numery linii) i `-c` (liczba dopasowań) są rozpoznawane, ale ich logika nie jest jeszcze zaimplementowana — obecnie tylko wypisują komunikat i kończą działanie.

## Jak to działa

```mermaid
flowchart TD
    A["main.c<br/>parsowanie argv, flag -n/-c"] --> B["mainparser.c<br/>wczytanie pliku do bufora"]
    B --> C["tekstparser.c<br/>podział bufora na linie"]
    C --> D["lineparser<br/>dopasowanie fragmentu tekstu w linii"]
    D -- dopasowano --> E["match.c<br/>Match / MatchList<br/>zapis wyniku na listę"]
    D -- brak dopasowania --> C
    E --> F["main.c<br/>wypisanie dopasowanych linii"]
    E --> G["match_list_free<br/>zwolnienie pamięci"]
```

## Struktura plików

| Plik | Rola |
|---|---|
| `main.c` | punkt wejścia, parsowanie argumentów |
| `mainparser.c/h` | wczytanie pliku do pamięci, uruchomienie parsowania |
| `tekstparser.c/h` | podział tekstu na linie i wyszukiwanie dopasowań |
| `match.c/h` | struktura `Match`/`MatchList` przechowująca wyniki |
