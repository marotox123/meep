# meep

Proste narzędzie CLI w C do wyszukiwania fragmentu tekstu w pliku, linia po linii (coś w stylu uproszczonego `grep`).

## Build

```sh
make
```

Ewentualnie ręcznie, bez Makefile:

```sh
gcc main.c mainparser.c tekstparser.c match.c -o meep
```

Sprzątanie plików wynikowych (`meep`, `*.o`):

```sh
make clean
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

## Algorytm wyszukiwania — C4

Dopasowywanie tekstu w linii (`lineparser` w [tekstparser.c](tekstparser.c)) to własny, naiwny (brute-force) algorytm nazwany **C4** — bez tablic prefiksów i przeskoków jak w KMP czy Boyer-Moore, stąd złożoność `O(n * m)`.

```mermaid
%%{init: {"theme": "base", "themeVariables": {
  "primaryColor": "#eef2ff",
  "primaryBorderColor": "#6366f1",
  "primaryTextColor": "#1e1b4b",
  "lineColor": "#6366f1",
  "fontSize": "15px"
}}}%%
flowchart TD
    subgraph START["Start"]
        A["ptr = start<br/>(początek linii)"]
    end

    subgraph OUTER["Punkt startowy"]
        B{"ptr < end?"}
        C["p2 = ptr, j = 0, k = 0<br/>(nowa próba dopasowania)"]
    end

    subgraph COMPARE["Porównanie znak po znaku"]
        D{"*p2 == tekst[j]?"}
        E["k++, p2++, j++"]
    end

    subgraph RESULT["Wynik próby"]
        F{"k >= dlugosc(tekst)?"}
        G["ptr++<br/>(przesuń o jeden znak)"]
    end

    subgraph DONE["Koniec"]
        H["zwróć 0<br/>(znaleziono)"]
        I["zwróć 1<br/>(brak dopasowania)"]
    end

    A --> B
    B -- tak --> C --> D
    D -- tak --> E --> D
    D -- nie --> F
    F -- tak --> H
    F -- nie --> G --> B
    B -- nie --> I

    classDef start fill:#dbeafe,stroke:#3b82f6,stroke-width:1.5px;
    classDef outer fill:#fef3c7,stroke:#f59e0b,stroke-width:1.5px;
    classDef compare fill:#ede9fe,stroke:#8b5cf6,stroke-width:1.5px;
    classDef result fill:#dcfce7,stroke:#22c55e,stroke-width:1.5px;
    classDef done fill:#fce7f3,stroke:#ec4899,stroke-width:1.5px;

    class A start;
    class B,C outer;
    class D,E compare;
    class F,G result;
    class H,I done;
```

## Jak to działa

```mermaid
%%{init: {"theme": "base", "themeVariables": {
  "primaryColor": "#eef2ff",
  "primaryBorderColor": "#6366f1",
  "primaryTextColor": "#1e1b4b",
  "lineColor": "#6366f1",
  "fontSize": "15px"
}}}%%
flowchart TD
    subgraph IN["Wejście"]
        A["main.c<br/>parsowanie argv, flag -n/-c"]
    end

    subgraph READ["Wczytanie danych"]
        B["mainparser.c<br/>wczytanie pliku do bufora"]
    end

    subgraph PARSE["Parsowanie"]
        C["tekstparser.c<br/>podział bufora na linie"]
        D{"lineparser<br/>fragment pasuje?"}
    end

    subgraph STORE["Wynik"]
        E["match.c<br/>Match / MatchList"]
    end

    subgraph OUT["Wyjście"]
        F["wypisanie dopasowanych linii"]
        G["match_list_free<br/>zwolnienie pamięci"]
    end

    A --> B --> C --> D
    D -- tak --> E
    D -- nie --> C
    E --> F --> G

    classDef input fill:#dbeafe,stroke:#3b82f6,stroke-width:1.5px;
    classDef parse fill:#fef3c7,stroke:#f59e0b,stroke-width:1.5px;
    classDef store fill:#dcfce7,stroke:#22c55e,stroke-width:1.5px;
    classDef output fill:#fce7f3,stroke:#ec4899,stroke-width:1.5px;

    class A input;
    class B,C,D parse;
    class E store;
    class F,G output;
```

## Struktura plików

| Plik | Rola |
|---|---|
| `main.c` | punkt wejścia, parsowanie argumentów |
| `mainparser.c/h` | wczytanie pliku do pamięci, uruchomienie parsowania |
| `tekstparser.c/h` | podział tekstu na linie i wyszukiwanie dopasowań |
| `match.c/h` | struktura `Match`/`MatchList` przechowująca wyniki |
