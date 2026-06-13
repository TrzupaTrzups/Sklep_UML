#pragma once

#include "Produkt.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class RepozytoriumProduktow {
private:
    string sciezkaDoPliku;

public:
    RepozytoriumProduktow(string& sciezkaDoPliku)
        : sciezkaDoPliku(sciezkaDoPliku) {
    }

    string& pobierzSciezkeDoPliku() {
        return sciezkaDoPliku;
    }

    vector<Produkt> wczytajProdukty() {
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

            if (pola.size() != 6) {
                continue;
            }

            try {
                int id = stoi(pola[0]);
                string nazwa = pola[1];
                double cena = stod(pola[2]);
                int stanMagazynowy = stoi(pola[3]);
                string kategoria = pola[4];
                string opis = pola[5];

                Produkt produkt(
                    id,
                    nazwa,
                    cena,
                    stanMagazynowy,
                    kategoria,
                    opis
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

    bool zapiszProdukty(vector<Produkt>& produkty, char separator = '|'){
        ofstream plik(sciezkaDoPliku, ios::trunc);

        if (!plik.is_open()) {
            return false;
        }

        for(Produkt& produkt : produkty){
            plik
                <<produkt.pobierzId() << separator
                <<produkt.pobierzNazwe() << separator
                <<fixed << setprecision(2) << produkt.pobierzCene() << separator
                <<produkt.pobierzStanMagazynowy() << separator
                <<produkt.pobierzKategorie() << separator
                <<produkt.pobierzOpis()
                << "\n";
        }

        return true;
    }


//Funkcja pomocnicza do zamiany tekstu z separatorem na wektor stringów nie ma jej w diagrami klas.
private:
    vector<string> podzielTekst(string& tekst, char separator){
        vector<string> wynik;
        string element;

        // Dzielimy recznie (nie przez getline), aby zachowac puste ostatnie pole,
        // np. gdy opis jest pusty: "...|kategoria|" ma byc 6 pol, a nie 5.
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