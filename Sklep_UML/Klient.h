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
        SerwisProduktow serwisProduktow
    )
        : Gosc(serwisProduktow),
          id(id),
          login(login),
          haslo(haslo) {
    }

    ~Klient() {}

    bool zaloguj(Klient& k, const string& login, const string& haslo) {
        if (k.login == login && k.haslo == haslo) {
            return true;
        } else {
            return false;
        }
    }

    void dodajProduktDoKoszyka(int idProduktu, int ilosc) {
        koszyk.dodajProdukt(idProduktu, ilosc);
    }

    void usunProduktZKoszyka(int idProduktu) {
        koszyk.usunProdukt(idProduktu);
    }

    void zmienIloscProduktu(int idProduktu, int ilosc) {
        koszyk.zmienIlosc(idProduktu, ilosc);
    }
    
    void zlozZamowienie() {
        if (koszyk.czyPusty()) {
            cout << "Koszyk jest pusty. Nie mozna zlozyc zamowienia." << endl;
            return;
        }

        double wartoscZamowienia = koszyk.obliczWartosc();
        cout << "Zlozono zamowienie o wartosci: " << wartoscZamowienia << " PLN" << endl;
        koszyk.wyczysc();
    }

    void pokazHistoriaZamowien() const {
    }

    void pokazStatusZamowienia(int idZamowienia) const {
    }

    void ZarzadzajAdresemDostawy() {
    }

    void zarzadzajKartaPlatnicza() {
    }

    void zmienHaslo(const string& noweHaslo) {
        haslo = noweHaslo;
        cout << "Haslo zostalo zmienione." << endl;
    }

    void pokazKoszyk() {
        koszyk.wyswietlKoszyk();
    }
};

#endif // KLIENT_H