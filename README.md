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
