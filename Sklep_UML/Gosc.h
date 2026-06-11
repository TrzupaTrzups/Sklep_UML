#pragma once

#include "SerwisProduktow.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class Rola {
    GOSC,
    KLIENT,
    ADMIN
};

class Gosc {
protected:
    SerwisProduktow& serwisProduktow;

public:
    Gosc(SerwisProduktow& serwisProduktow)
        : serwisProduktow(serwisProduktow) {
    }

    virtual ~Gosc() = default;

    virtual Rola pobierzRole() const {
        return Rola::GOSC;
    }

    void przegladajProdukty() const {
        const vector<Produkt>& produkty = serwisProduktow.pobierzProdukty();
        wyswietlTabeleProduktow(produkty);
    }

    void wyszukajProdukt(const string& fraza) const {
        vector<Produkt> produkty = serwisProduktow.wyszukajProduktyPoNazwie(fraza);
        wyswietlTabeleProduktow(produkty);
    }

    vector<Produkt> filtrujProdukty(
        const string& kategoria,
        const string& cenaMinimalnaTekst,
        const string& cenaMaksymalnaTekst
    ) const {
        vector<Produkt> wszystkieProdukty = serwisProduktow.pobierzProdukty();
        vector<Produkt> wynik;

        bool czyFiltrowacKategorie = !kategoria.empty();
        bool czyFiltrowacCeneMinimalna = !cenaMinimalnaTekst.empty();
        bool czyFiltrowacCeneMaksymalna = !cenaMaksymalnaTekst.empty();

        double cenaMinimalna = 0;
        double cenaMaksymalna = 0;

        try {
            if (czyFiltrowacCeneMinimalna) {
                cenaMinimalna = stod(cenaMinimalnaTekst);
            }

            if (czyFiltrowacCeneMaksymalna) {
                cenaMaksymalna = stod(cenaMaksymalnaTekst);
            }
        }
        catch (...) {
            return wynik;
        }

        if (
            czyFiltrowacCeneMinimalna &&
            czyFiltrowacCeneMaksymalna &&
            cenaMinimalna > cenaMaksymalna
        ) {
            return wynik;
        }

        for (Produkt& produkt : wszystkieProdukty) {
            bool pasuje = true;

            if (czyFiltrowacKategorie && produkt.pobierzKategorie() != kategoria) {
                pasuje = false;
            }

            if (czyFiltrowacCeneMinimalna && produkt.pobierzCene() < cenaMinimalna) {
                pasuje = false;
            }

            if (czyFiltrowacCeneMaksymalna && produkt.pobierzCene() > cenaMaksymalna) {
                pasuje = false;
            }

            if (pasuje) {
                wynik.push_back(produkt);
            }
        }

        return wynik;
    }   

    void pokazSzczegolyProduktu(int idProduktu) const {
        const Produkt* produkt = serwisProduktow.znajdzProduktPoId(idProduktu);

        if (produkt == nullptr) {
            cout << "Nie znaleziono produktu." << endl;
            return;
        }

        const_cast<Produkt*>(produkt)->wyswietl();
    }

    void wyswietlProdukty(const vector<Produkt>& produkty) const {
        wyswietlTabeleProduktow(produkty);
    }

protected:
    void wyswietlTabeleProduktow(vector<Produkt> produkty) const {
        if (produkty.empty()) {
            cout << "Brak produktow do wyswietlenia." << endl;
            return;
        }

        cout << left
            << setw(6) << "ID"
            << setw(30) << "Nazwa"
            << setw(14) << "Cena"
            << setw(10) << "Stan"
            << setw(20) << "Kategoria"
            << endl;

        cout << string(80, '-') << endl;

        for (Produkt& produkt : produkty) {
            ostringstream cena;
            cena << fixed << setprecision(2) << produkt.pobierzCene() << " zl";

            cout << left
                << setw(6) << produkt.pobierzId()
                << setw(30) << skrocTekst(produkt.pobierzNazwe(), 29)
                << setw(14) << cena.str()
                << setw(10) << produkt.pobierzStanMagazynowy()
                << setw(20) << skrocTekst(produkt.pobierzKategorie(), 19)
                << endl;
        }
    }

    string skrocTekst(const string& tekst, int maksymalnaDlugosc) const {
        if (static_cast<int>(tekst.length()) <= maksymalnaDlugosc) {
            return tekst;
        }

        if (maksymalnaDlugosc <= 3) {
            return tekst.substr(0, maksymalnaDlugosc);
        }

        return tekst.substr(0, maksymalnaDlugosc - 3) + "...";
    }
};