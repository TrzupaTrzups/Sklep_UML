#pragma once

#include "KartaPlatnicza.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

// zapisuje i wczytuje karte platnicza z pliku
class RepozytoriumKartPlatniczych {
private:
    string sciezkaPliku;

public:
    RepozytoriumKartPlatniczych(const string& sciezkaPliku)
        : sciezkaPliku(sciezkaPliku) {
    }

    const string& pobierzSciezkePliku() const {
        return sciezkaPliku;
    }

    // Wczytuje karte z pliku do przekazanego obiektu. Zwraca true przy powodzeniu
    // (na diagramie void; bool dla wygody).
    // Uwaga: w prawdziwym systemie CVV NIGDY nie jest zapisywany - tu uproszczenie dydaktyczne.
    bool wczytaj(KartaPlatnicza& karta) {
        ifstream plik(sciezkaPliku);

        if (!plik.is_open()) {
            return false;
        }

        string linia;

        if (!getline(plik, linia)) {
            return false;
        }

        vector<string> pola = podzielTekst(linia, '|');

        if (pola.size() != 4) {
            return false;
        }

        karta = KartaPlatnicza(pola[0], pola[1], pola[2], pola[3]);
        return true;
    }

    bool zapisz(const KartaPlatnicza& karta) {
        ofstream plik(sciezkaPliku, ios::trunc);

        if (!plik.is_open()) {
            return false;
        }

        plik
            << karta.pobierzWlasciciela() << '|'
            << karta.pobierzNumerKarty() << '|'
            << karta.pobierzDateWaznosci() << '|'
            << karta.pobierzCvv()
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
