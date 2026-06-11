#pragma once

#include "Produkt.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using std::fixed;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::setprecision;
using std::stoi;
using std::stod;
using std::string;
using std::stringstream;
using std::vector;

class RepozytoriumProduktow {
private:
    string sciezkaDoPliku;

public:
    explicit RepozytoriumProduktow(const string& sciezkaDoPliku)
        : sciezkaDoPliku(sciezkaDoPliku) {
    }

    const string& pobierzSciezkeDoPliku() const {
        return sciezkaDoPliku;
    }

    vector<Produkt> wczytajProdukty() const {
        vector<Produkt> produkty;

        ifstream plik(sciezkaDoPliku);

        if (!plik.is_open()) {
            return produkty;
        }

        string linia;

        while (getline(plik, linia)) {
            if (linia.empty()) {
                continue;
            }

            vector<string> pola = podzielTekst(linia, '|');

            if (pola.size() != 5) {
                continue;
            }

            try {
                int id = stoi(pola[0]);
                string nazwa = pola[1];
                double cena = stod(pola[2]);
                int stanMagazynowy = stoi(pola[3]);
                string kategoria = pola[4];

                Produkt produkt(
                    id,
                    nazwa,
                    cena,
                    stanMagazynowy,
                    kategoria
                );

                if (produkt.czyPoprawny()) {
                    produkty.push_back(produkt);
                }
            }
            catch (...) {
                continue;
            }
        }

        return produkty;
    }

    bool zapiszProdukty(const vector<Produkt>& produkty) const {
        ofstream plik(sciezkaDoPliku, ios::trunc);

        if (!plik.is_open()) {
            return false;
        }

        for (const Produkt& produkt : produkty) {
            plik
                << produkt.pobierzId() << "|"
                << produkt.pobierzNazwe() << "|"
                << fixed << setprecision(2) << produkt.pobierzCene() << "|"
                << produkt.pobierzStanMagazynowy() << "|"
                << produkt.pobierzKategorie()
                << "\n";
        }

        return true;
    }

private:
    vector<string> podzielTekst(const string& tekst, char separator) const {
        vector<string> wynik;
        stringstream strumien(tekst);
        string element;

        while (getline(strumien, element, separator)) {
            wynik.push_back(element);
        }

        return wynik;
    }
};