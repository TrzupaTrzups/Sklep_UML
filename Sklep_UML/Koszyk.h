#ifndef KOSZYK_H
#define KOSZYK_H

#include <iostream>
#include <vector>
#include "PozycjaKoszyka.h"
#include "SerwisProduktow.h"

using namespace std;

class Koszyk {
    public:
    vector <PozycjaKoszyka> pozycje;
    SerwisProduktow* serwisProduktow;

    Koszyk() {
        serwisProduktow = nullptr;
    }

    Koszyk(SerwisProduktow* serwisProduktow)
        : serwisProduktow(serwisProduktow) {
    }

    bool dodajProdukt(int idProduktu, int ilosc) {
        const Produkt* produkt = serwisProduktow->znajdzProduktPoId(idProduktu);

        if (produkt == nullptr) {
            cout << "Nie znaleziono produktu o ID: " << idProduktu << endl;
            return false;
        }

        for (PozycjaKoszyka& pozycja : pozycje) {
            if(pozycja.pobierzProdukt().pobierzId() == idProduktu) {
                pozycja.ustawIlosc(pozycja.pobierzIlosc() + ilosc);
                return true;
            }
        }

        PozycjaKoszyka nowaPozycja(*produkt, ilosc);
        pozycje.push_back(nowaPozycja);
        return true;
    };
    bool usunProdukt(int idProduktu);
    bool zmienIlosc(int idProduktu, int ilosc);
    double obliczWartosc() {
        double wartosc = 0.0;

        for (PozycjaKoszyka& pozycja : pozycje) {
            wartosc += pozycja.obliczWartosc();
        }

        return wartosc;
    };
    void wyczysc() {
        pozycje.clear();
    };
    bool czyPusty() {
        return pozycje.empty();
    };
    void wyswietlKoszyk() {
        if (pozycje.empty()) {
            cout << "Koszyk jest pusty." << endl;
        }

        cout << "Zawartosc koszyka:" << endl;

        for (PozycjaKoszyka& pozycja : pozycje) {
            pozycja.wyswietl();
        }

        cout << "Laczna wartosc: " << obliczWartosc() << " PLN" << endl;
    };
};

#endif // KOSZYK_H