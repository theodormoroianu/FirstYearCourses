# Final project - Tehnici Web 2020

_Proiectul acesta este bazat pe proiectul de laborator, pentru a il vedea in forma lui initiala, puteti sa navigati in istoricul acestei pagini._

## Ideea din spatele proiectului

* Proiectul este un single-page application, facut cu `nodejs` in backend si in `javascript` pur in frontend.
* Aplicatia web permite crearea si editarea rapida a unor notite de tip text.
* Fiecare notita are un istoric, versiunile acesteia formand un arbore.

## Securitate

* Securitatea aplicatiei este creata cu ajutorul unui sistem de sign-in.
* Desi se pot salva in localstorage informatii pentru a nu deloga utilizatorul la fiecare sign-in, nu se salveaza passwordul ci un token dat de server.
* Pentru a putea accesa o notita sau informatiile unui user, este nevoie de un token valid.

## Implementare - API

Paginile cu informatii (mai mult sau mai putin complete) despre API sunt:
* [LOGIN API](documentation/login_signup.md)
* [Notes navigator API](documentation/menu.md)
* [Server INFO](documentation/server.md)

## Package-uri necesare

* `npm express`
* `npm morgan`
* `python3`
* `graphviz`

**NOTE: `graphviz` only runs on linux so this server won't work as intented on other platforms**

![Sample](documentation/Sample.png)

