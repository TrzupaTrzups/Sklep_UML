#pragma once

#include "Produkt.h"
#include <iostream>

class PozycjaKoszyka {
private:
    Produkt produkt;
    int ilosc;

public:
    PozycjaKoszyka(const Produkt& produkt, int ilosc)
        : produkt(produkt),
          ilosc(ilosc) {
    }

    const Produkt& pobierzProdukt() const {
        return produkt;
    }

    int pobierzIlosc() {
        return ilosc;
    }

    void ustawIlosc(int nowaIlosc) {
        ilosc = nowaIlosc;
    }

    double obliczWartosc(){
        return produkt.pobierzCene() * ilosc;
    }

    void wyswietl() {
        cout
            << "Produkt: " << produkt.pobierzNazwe()
            << ", Cena: " << produkt.pobierzCene() << " zl"
            << ", Ilosc: " << ilosc
            << ", Wartosc: " << obliczWartosc() << " zl"
            << endl;
    }
};