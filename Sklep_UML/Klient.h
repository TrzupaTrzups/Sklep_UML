#ifndef KLIENT_H
#define KLIENT_H

#include "Gosc.h"
#include "Koszyk.h"

#include <iostream>

class Klient : public Gosc {
    public:
    int id;
    string login;
    string haslo;
    Koszyk koszyk;

    Klient() : id(0) {}
    ~Klient() {}

    Klient(int id, const string& login, const string& haslo)
        : id(id), login(login), haslo(haslo) {}

    void dodajProduktDoKoszyka(int idProduktu, int ilosc);
    void usunProduktZKoszyka(int idProduktu);
};

#endif // KLIENT_H