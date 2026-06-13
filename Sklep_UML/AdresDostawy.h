#pragma once

#include <iostream>
#include <string>

using namespace std;

// adres dostawy do zamowienia (odbiorca + dane wysylki)
class AdresDostawy {
private:
    string odbiorca;
    string ulica;
    string kodPocztowy;
    string miasto;
    string telefon;

public:
    AdresDostawy() = default;

    AdresDostawy(
        const string& odbiorca,
        const string& ulica,
        const string& kodPocztowy,
        const string& miasto,
        const string& telefon
    )
        : odbiorca(odbiorca),
          ulica(ulica),
          kodPocztowy(kodPocztowy),
          miasto(miasto),
          telefon(telefon) {
    }

    const string& pobierzOdbiorce() const {
        return odbiorca;
    }

    const string& pobierzUlice() const {
        return ulica;
    }

    const string& pobierzKodPocztowy() const {
        return kodPocztowy;
    }

    const string& pobierzMiasto() const {
        return miasto;
    }

    const string& pobierzTelefon() const {
        return telefon;
    }

    // true tylko jak wszystkie pola adresu sa wypelnione
    bool czyKompletny() const {
        return !odbiorca.empty()
            && !ulica.empty()
            && !kodPocztowy.empty()
            && !miasto.empty()
            && !telefon.empty();
    }

    void wyswietl() const {
        cout
            << "Odbiorca: " << odbiorca << endl
            << "Ulica: " << ulica << endl
            << "Kod pocztowy: " << kodPocztowy << endl
            << "Miasto: " << miasto << endl
            << "Telefon: " << telefon << endl;
    }
};
