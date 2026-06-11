#ifndef KLIENT_H
#define KLIENT_H

#include "Gosc.h"
#include "Koszyk.h"

#include <iostream>
#include <string>

using namespace std;

class Klient : public Gosc {
public:
    int id;
    string login;
    string haslo;
    Koszyk koszyk;

    Klient(
        int id,
        const string& login,
        const string& haslo,
        SerwisProduktow& serwisProduktow
    )
        : Gosc(serwisProduktow),
          id(id),
          login(login),
          haslo(haslo) {
    }

    ~Klient() {}

    void dodajProduktDoKoszyka(int idProduktu, int ilosc) {
    }

    void usunProduktZKoszyka(int idProduktu) {
    }
};

#endif // KLIENT_H