#ifndef KLIENT_H
#define KLIENT_H

#include "Gosc.h"
#include "Koszyk.h"
#include "SerwisZamowien.h"
#include "SerwisAdresuDostaw.h"
#include "SerwisKartyPlatniczej.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// zalogowany klient - ma swoj koszyk i moze skladac zamowienia, ogladac historie itd.
class Klient : public Gosc {
public:
    int id;
    string login;
    string haslo;
    Koszyk koszyk;

private:
    // Serwisy potrzebne do zamowien/adresu/karty. Opcjonalne (moga byc nullptr),
    // bo na diagramie Klient ich nie trzyma jako pol - ustawiane konstruktorem pelnym
    // lub metoda ustawSerwisy.
    SerwisZamowien* serwisZamowien = nullptr;
    SerwisAdresuDostaw* serwisAdresu = nullptr;
    SerwisKartyPlatniczej* serwisKarty = nullptr;

public:
    // Konstruktor podstawowy - bez serwisow zamowien/adresu/karty.
    Klient(
        int id,
        const string& login,
        const string& haslo,
        SerwisProduktow& serwisProduktow
    )
        : Gosc(serwisProduktow),
          id(id),
          login(login),
          haslo(haslo),
          koszyk(&serwisProduktow) {
    }

    // Konstruktor pelny - z serwisami do zamowien, adresu i karty.
    Klient(
        int id,
        const string& login,
        const string& haslo,
        SerwisProduktow& serwisProduktow,
        SerwisZamowien& serwisZamowien,
        SerwisAdresuDostaw& serwisAdresu,
        SerwisKartyPlatniczej& serwisKarty
    )
        : Gosc(serwisProduktow),
          id(id),
          login(login),
          haslo(haslo),
          koszyk(&serwisProduktow),
          serwisZamowien(&serwisZamowien),
          serwisAdresu(&serwisAdresu),
          serwisKarty(&serwisKarty) {
    }

    ~Klient() {}

    void ustawSerwisy(
        SerwisZamowien& sz,
        SerwisAdresuDostaw& sa,
        SerwisKartyPlatniczej& sk
    ) {
        serwisZamowien = &sz;
        serwisAdresu = &sa;
        serwisKarty = &sk;
    }

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

    // sklada zamowienie z koszyka - bierze zapisany adres, tworzy zamowienie i czysci koszyk
    void zlozZamowienie() {
        if (koszyk.czyPusty()) {
            cout << "Koszyk jest pusty. Nie mozna zlozyc zamowienia." << endl;
            return;
        }

        if (serwisZamowien == nullptr || serwisAdresu == nullptr) {
            // Brak podpietych serwisow - wariant uproszczony.
            double wartoscZamowienia = koszyk.obliczWartosc();
            cout << "Zlozono zamowienie o wartosci: " << wartoscZamowienia << " PLN" << endl;
            koszyk.wyczysc();
            return;
        }

        AdresDostawy adres;
        serwisAdresu->pobierzAdres(adres);

        if (!adres.czyKompletny()) {
            cout << "Brak kompletnego adresu dostawy. Uzupelnij adres przed zlozeniem zamowienia." << endl;
            return;
        }

        if (serwisZamowien->utworzZamowienie(id, koszyk, adres)) {
            cout << "Zamowienie zostalo zlozone." << endl;
            koszyk.wyczysc();
        } else {
            cout << "Nie udalo sie zlozyc zamowienia." << endl;
        }
    }

    // wypisuje wszystkie zamowienia tego klienta
    void pokazHistorieZamowien() {
        if (serwisZamowien == nullptr) {
            cout << "Historia zamowien niedostepna." << endl;
            return;
        }

        vector<Zamowienie> zamowienia = serwisZamowien->pobierzZamowieniaKlienta(id);

        if (zamowienia.empty()) {
            cout << "Brak zamowien." << endl;
            return;
        }

        cout << "=== HISTORIA ZAMOWIEN ===" << endl;
        for (Zamowienie& zamowienie : zamowienia) {
            zamowienie.wyswietlPodsumowanie();
        }
    }

    // pokazuje status jednego zamowienia po jego ID
    void pokazStatusZamowienia(int idZamowienia) {
        if (serwisZamowien == nullptr) {
            cout << "Status zamowienia niedostepny." << endl;
            return;
        }

        Zamowienie* zamowienie = serwisZamowien->pobierzZamowieniePoId(idZamowienia);

        if (zamowienie == nullptr) {
            cout << "Nie znaleziono zamowienia o ID: " << idZamowienia << endl;
            return;
        }

        zamowienie->wyswietlPodsumowanie();
    }

    // Wyswietla zapisany adres dostawy. Zwraca true, gdy adres jest kompletny.
    // (Wpisywanie/edycja adresu nalezy do warstwy menu.)
    bool zarzadzajAdresemDostawy() {
        if (serwisAdresu == nullptr) {
            cout << "Serwis adresu niedostepny." << endl;
            return false;
        }

        AdresDostawy adres;
        serwisAdresu->pobierzAdres(adres);

        if (!adres.czyKompletny()) {
            cout << "Brak zapisanego adresu dostawy." << endl;
            return false;
        }

        cout << "=== ADRES DOSTAWY ===" << endl;
        adres.wyswietl();
        return true;
    }

    // Wyswietla zapisana karte platnicza. Zwraca true, gdy karta jest poprawna.
    bool zarzadzajKartaPlatnicza() {
        if (serwisKarty == nullptr) {
            cout << "Serwis karty niedostepny." << endl;
            return false;
        }

        KartaPlatnicza karta = serwisKarty->pobierzKarte();

        if (!karta.czyPoprawna()) {
            cout << "Brak zapisanej karty platniczej." << endl;
            return false;
        }

        cout << "=== KARTA PLATNICZA ===" << endl;
        karta.wyswietl();
        return true;
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
