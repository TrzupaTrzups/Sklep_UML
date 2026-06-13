#pragma once

#include "KartaPlatnicza.h"
#include "RepozytoriumKartPlatniczych.h"

#include <string>

using namespace std;

class SerwisKartyPlatniczej {
private:
    RepozytoriumKartPlatniczych repozytorium;
    KartaPlatnicza karta;

public:
    SerwisKartyPlatniczej(const string& sciezkaPliku)
        : repozytorium(sciezkaPliku) {
        // Proba wczytania zapisanej karty na starcie (spojnie z SerwisAdresuDostaw).
        repozytorium.wczytaj(karta);
    }

    // Zwraca aktualnie przechowywana karte (na diagramie pobierzKarte():void).
    KartaPlatnicza pobierzKarte() const {
        return karta;
    }

    // Ustawia karte i zapisuje ja do pliku. Zwraca true przy powodzeniu (na diagramie void).
    bool zapiszKarte(const KartaPlatnicza& k) {
        karta = k;
        return repozytorium.zapisz(karta);
    }

    // Wczytuje karte z pliku do pola karta. Zwraca true przy powodzeniu (na diagramie void).
    bool pobierzKarteZPliku() {
        return repozytorium.wczytaj(karta);
    }
};
