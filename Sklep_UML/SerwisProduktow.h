#pragma once

#include "Produkt.h"
#include "RepozytoriumProduktow.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using std::find;
using std::remove_if;
using std::sort;
using std::string;
using std::tolower;
using std::vector;

class SerwisProduktow {
private:
    vector<Produkt> produkty;
    RepozytoriumProduktow repozytorium;

public:
    SerwisProduktow(string& sciezkaDoPliku)
        : repozytorium(sciezkaDoPliku) {
        produkty = repozytorium.wczytajProdukty();
    }

    const vector<Produkt>& pobierzWszystkieProdukty() const {
        return produkty;
    }

    const Produkt* znajdzProduktPoId(int id) const {
        for (const Produkt& produkt : produkty) {
            if (produkt.pobierzId() == id) {
                return &produkt;
            }
        }

        return nullptr;
    }

    bool dodajProdukt(const Produkt& produkt) {
        if (!produkt.czyPoprawny()) {
            return false;
        }

        if (czyProduktIstnieje(produkt.pobierzId())) {
            return false;
        }

        produkty.push_back(produkt);
        return zapiszZmiany();
    }

    bool usunProdukt(int id) {
        auto liczbaProduktowPrzedUsunieciem = produkty.size();

        produkty.erase(
            remove_if(
                produkty.begin(),
                produkty.end(),
                [id](const Produkt& produkt) {
                    return produkt.pobierzId() == id;
                }
            ),
            produkty.end()
        );

        if (produkty.size() == liczbaProduktowPrzedUsunieciem) {
            return false;
        }

        return zapiszZmiany();
    }

    vector<Produkt> wyszukajProduktyPoNazwie(const string& fraza) const {
        vector<Produkt> wynik;

        if (fraza.empty()) {
            return produkty;
        }

        string frazaMaleLitery = zamienNaMaleLitery(fraza);

        for (const Produkt& produkt : produkty) {
            string nazwaMaleLitery = zamienNaMaleLitery(produkt.pobierzNazwe());

            if (nazwaMaleLitery.find(frazaMaleLitery) != string::npos) {
                wynik.push_back(produkt);
            }
        }

        return wynik;
    }

    vector<Produkt> filtrujProduktyPoKategorii(const string& kategoria) const {
        vector<Produkt> wynik;

        if (kategoria.empty()) {
            return wynik;
        }

        string szukanaKategoria = zamienNaMaleLitery(kategoria);

        for (const Produkt& produkt : produkty) {
            string kategoriaProduktu = zamienNaMaleLitery(produkt.pobierzKategorie());

            if (kategoriaProduktu == szukanaKategoria) {
                wynik.push_back(produkt);
            }
        }

        return wynik;
    }

    vector<Produkt> filtrujProduktyPoCenie(double cenaMinimalna, double cenaMaksymalna) const {
        vector<Produkt> wynik;

        if (cenaMinimalna < 0 || cenaMaksymalna < 0) {
            return wynik;
        }

        if (cenaMinimalna > cenaMaksymalna) {
            return wynik;
        }

        for (const Produkt& produkt : produkty) {
            if (
                produkt.pobierzCene() >= cenaMinimalna &&
                produkt.pobierzCene() <= cenaMaksymalna
                ) {
                wynik.push_back(produkt);
            }
        }

        return wynik;
    }

    vector<string> pobierzKategorie() const {
        vector<string> kategorie;

        for (const Produkt& produkt : produkty) {
            string kategoria = produkt.pobierzKategorie();

            if (find(kategorie.begin(), kategorie.end(), kategoria) == kategorie.end()) {
                kategorie.push_back(kategoria);
            }
        }

        sort(kategorie.begin(), kategorie.end());

        return kategorie;
    }

private:
    bool czyProduktIstnieje(int id) const {
        return znajdzProduktPoId(id) != nullptr;
    }

    bool zapiszZmiany(){
        return repozytorium.zapiszProdukty(produkty);
    }

    string zamienNaMaleLitery(const string& tekst) const {
        string wynik = tekst;

        for (char& znak : wynik) {
            znak = static_cast<char>(
                tolower(static_cast<unsigned char>(znak))
                );
        }

        return wynik;
    }
};