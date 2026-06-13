#pragma once

#include "AdresDostawy.h"
#include "RepozytoriumAdresuDostaw.h"

#include <string>

using namespace std;

class SerwisAdresuDostaw {
private:
    RepozytoriumAdresuDostaw repozytorium;
    AdresDostawy adres;

public:
    SerwisAdresuDostaw(const string& sciezkaPliku)
        : repozytorium(sciezkaPliku) {
        // Proba wczytania zapisanego adresu na starcie (spojnie z SerwisProduktow).
        repozytorium.wczytaj(adres);
    }

    // Kopiuje aktualnie przechowywany adres do przekazanego obiektu
    // (na diagramie pobierzAdres(a):void).
    void pobierzAdres(AdresDostawy& a) {
        a = adres;
    }

    // Ustawia adres i zapisuje go do pliku. Zwraca true przy powodzeniu zapisu
    // (na diagramie void).
    bool zapiszAdres(const AdresDostawy& a) {
        adres = a;
        return repozytorium.zapisz(adres);
    }

    // Wczytuje adres z pliku do pola adres. Zwraca true, gdy sie udalo
    // (na diagramie void).
    bool wczytajAdresZPliku() {
        return repozytorium.wczytaj(adres);
    }
};
