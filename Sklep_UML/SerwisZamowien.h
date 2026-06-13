#pragma once

#include "Zamowienie.h"
#include "Koszyk.h"
#include "AdresDostawy.h"

#include <vector>

using namespace std;

// trzyma wszystkie zamowienia w pamieci i pozwala je tworzyc/szukac/zmieniac status
class SerwisZamowien {
private:
    vector<Zamowienie> zamowienia;
    int nastepneId = 1;

public:
    // Na diagramie return typy serwisu sa niespojne (np. "vector"/"boolean" tam,
    // gdzie logicznie powinien byc pojedynczy obiekt). Nazwy i parametry sa wg
    // diagramu; typy zwracane dobrane logicznie.

    // Tworzy zamowienie z koszyka i adresu. Zwraca true, gdy sie udalo
    // (koszyk niepusty i adres kompletny). Nadaje kolejne unikalne ID.
    bool utworzZamowienie(int idKlienta, Koszyk& koszyk, AdresDostawy& adres) {
        if (koszyk.czyPusty()) {
            return false;
        }

        if (!adres.czyKompletny()) {
            return false;
        }

        double wartosc = koszyk.obliczWartosc();

        Zamowienie zamowienie(
            nastepneId,
            idKlienta,
            koszyk,
            wartosc,
            adres,
            StatusZamowienia::Utworzone
        );

        zamowienia.push_back(zamowienie);
        nastepneId++;

        return true;
    }

    bool zmienStatus(int idZamowienia, StatusZamowienia nowyStatus) {
        for (Zamowienie& zamowienie : zamowienia) {
            if (zamowienie.id == idZamowienia) {
                return zamowienie.zmienStatus(nowyStatus);
            }
        }

        return false;
    }

    // Zwraca wskaznik do zamowienia o danym ID, lub nullptr jesli nie istnieje
    // (spojnie z SerwisProduktow::znajdzProduktPoId).
    Zamowienie* pobierzZamowieniePoId(int idZamowienia) {
        for (Zamowienie& zamowienie : zamowienia) {
            if (zamowienie.id == idZamowienia) {
                return &zamowienie;
            }
        }

        return nullptr;
    }

    vector<Zamowienie> pobierzZamowieniaKlienta(int idKlienta) {
        vector<Zamowienie> wynik;

        for (Zamowienie& zamowienie : zamowienia) {
            if (zamowienie.idKlienta == idKlienta) {
                wynik.push_back(zamowienie);
            }
        }

        return wynik;
    }

    const vector<Zamowienie>& pobierzWszystkieZamowienia() const {
        return zamowienia;
    }
};
