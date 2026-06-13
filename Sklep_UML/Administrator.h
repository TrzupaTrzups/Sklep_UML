#pragma once

#include "Gosc.h"

#include <iostream>
#include <string>

using namespace std;

class Administrator : public Gosc {
private:
    int id;
    string login;
    string haslo;

public:
    Administrator(
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

    int pobierzId() const {
        return id;
    }

    string pobierzLogin() const {
        return login;
    }

    string pobierzHaslo() const {
        return haslo;
    }

    // void wyswietlMenuAdministratora() const {
    //     cout << "=== MENU ADMINISTRATORA ===" << endl;
    //     cout << "1. Przegladaj produkty" << endl;
    //     cout << "2. Dodaj produkt" << endl;
    //     cout << "3. Usun produkt" << endl;
    //     cout << "4. Edytuj produkt" << endl;
    //     cout << "0. Wyjdz" << endl;
    //     cout << endl;
    // }

    bool dodajProdukt(const Produkt& produkt) {
    return serwisProduktow.dodajProdukt(produkt);
    }

    bool usunProdukt(int idProduktu) {
        return serwisProduktow.usunProdukt(idProduktu);
    }

    bool zmienNazweProduktu(int idProduktu, const string& nowaNazwa) {
        return serwisProduktow.zmienNazweProduktu(idProduktu, nowaNazwa);
    }

    bool zmienCeneProduktu(int idProduktu, double nowaCena) {
        return serwisProduktow.zmienCeneProduktu(idProduktu, nowaCena);
    }

    bool zmienStanMagazynowy(int idProduktu, int nowyStan) {
        return serwisProduktow.zmienStanMagazynowy(idProduktu, nowyStan);
    }

    bool zmienKategorieProduktu(int idProduktu, const string& nowaKategoria) {
        return serwisProduktow.zmienKategorieProduktu(idProduktu, nowaKategoria);
    }
        bool zaloguj(Administrator& admin, const string& login, const string& haslo) {
        if (admin.login == login && admin.haslo == haslo) {
            return true;
        } else {
            return false;
        }
    }
};