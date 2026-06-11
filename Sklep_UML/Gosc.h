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
    explicit Gosc(SerwisProduktow& serwisProduktow)
        : serwisProduktow(serwisProduktow) {
    }

    virtual ~Gosc() = default;

    virtual Rola pobierzRole() const {
        return Rola::GOSC;
    }

    void przegladajProdukty() const {
        const vector<Produkt>& produkty = serwisProduktow.pobierzWszystkieProdukty();
        wyswietlTabeleProduktow(produkty);
    }

    void wyszukajProdukt(const string& fraza) const {
        vector<Produkt> produkty = serwisProduktow.wyszukajProduktyPoNazwie(fraza);
        wyswietlTabeleProduktow(produkty);
    }

    void filtrujProduktyPoKategorii(const string& kategoria) const {
        vector<Produkt> produkty = serwisProduktow.filtrujProduktyPoKategorii(kategoria);
        wyswietlTabeleProduktow(produkty);
    }

    void filtrujProduktyPoCenie(double cenaMinimalna, double cenaMaksymalna) const {
        vector<Produkt> produkty = serwisProduktow.filtrujProduktyPoCenie(
            cenaMinimalna,
            cenaMaksymalna
        );

        wyswietlTabeleProduktow(produkty);
    }

    void pokazSzczegolyProduktu(int idProduktu) const {
        const Produkt* produkt = serwisProduktow.znajdzProduktPoId(idProduktu);

        if (produkt == nullptr) {
            cout << "Nie znaleziono produktu." << endl;
            return;
        }

        produkt->wyswietl();
    }

    void wyswietlProdukty(const vector<Produkt>& produkty) const {
        wyswietlTabeleProduktow(produkty);
    }

protected:
    void wyswietlTabeleProduktow(const vector<Produkt>& produkty) const {
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

        for (const Produkt& produkt : produkty) {
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