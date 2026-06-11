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

    bool zapiszProdukty(const vector<Produkt>& produkty, char separator = '|'){
        ofstream plik(sciezkaDoPliku, ios::trunc);

        if (!plik.is_open()) {
            return false;
        }

        for(const Produkt& produkt : produkty){
            plik
                <<produkt.pobierzId() << separator
                <<produkt.pobierzNazwe() << separator
                <<fixed << setprecision(2) << produkt.pobierzCene() << separator
                <<produkt.pobierzStanMagazynowy() << separator
                <<produkt.pobierzKategorie()
                << "\n";
        }

        return true;
    }


//Funkcja pomocnicza do zamiany tekstu z separatorem na wektor stringów nie ma jej w diagrami klas.
private:
    vector<string> podzielTekst(const string& tekst, char separator){
        vector<string> wynik;
        stringstream strumien(tekst);
        string element;

        while (getline(strumien, element, separator)) {
            wynik.push_back(element);
        }

        return wynik;
    }
};