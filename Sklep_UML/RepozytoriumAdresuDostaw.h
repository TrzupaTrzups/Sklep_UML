#pragma once

#include "AdresDostawy.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

// zapisuje i wczytuje adres dostawy z pliku
class RepozytoriumAdresuDostaw {
private:
    string sciezkaPliku;

public:
    RepozytoriumAdresuDostaw(const string& sciezkaPliku)
        : sciezkaPliku(sciezkaPliku) {
    }

    const string& pobierzSciezkePliku() const {
        return sciezkaPliku;
    }

    // Wczytuje adres z pliku do przekazanego obiektu. Zwraca true, gdy plik
    // istnieje i ma poprawny format (na diagramie zwraca void; bool dla wygody).
    bool wczytaj(AdresDostawy& adres) {
        ifstream plik(sciezkaPliku);

        if (!plik.is_open()) {
            return false;
        }

        string linia;

        if (!getline(plik, linia)) {
            return false;
        }

        vector<string> pola = podzielTekst(linia, '|');

        if (pola.size() != 5) {
            return false;
        }

        adres = AdresDostawy(pola[0], pola[1], pola[2], pola[3], pola[4]);
        return true;
    }

    // Zapisuje adres do pliku (nadpisuje). Zwraca true przy powodzeniu
    // (na diagramie void; bool dla spojnosci z RepozytoriumProduktow).
    bool zapisz(const AdresDostawy& adres) {
        ofstream plik(sciezkaPliku, ios::trunc);

        if (!plik.is_open()) {
            return false;
        }

        plik
            << adres.pobierzOdbiorce() << '|'
            << adres.pobierzUlice() << '|'
            << adres.pobierzKodPocztowy() << '|'
            << adres.pobierzMiasto() << '|'
            << adres.pobierzTelefon()
            << "\n";

        return true;
    }

private:
    vector<string> podzielTekst(const string& tekst, char separator) {
        vector<string> wynik;
        string element;

        for (char znak : tekst) {
            if (znak == separator) {
                wynik.push_back(element);
                element.clear();
            } else {
                element.push_back(znak);
            }
        }

        wynik.push_back(element);
        return wynik;
    }
};
