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
};