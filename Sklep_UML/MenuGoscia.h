#pragma once

#include "Gosc.h"
#include "SerwisProduktow.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class MenuGoscia {
    protected:
    Gosc* gosc;
    SerwisProduktow* serwisProduktow;

    vector<Produkt> aktualneProdukty;
    string aktualnyTytul;
    

    public:

    MenuGoscia()
        : gosc(nullptr),
          serwisProduktow(nullptr),
          aktualneProdukty(),
          aktualnyTytul("WSZYSTKIE PRODUKTY") {
    }

    MenuGoscia(Gosc& gosc, SerwisProduktow& serwisProduktow)
        : gosc(&gosc),
          serwisProduktow(&serwisProduktow),
          aktualneProdukty(serwisProduktow.pobierzProdukty()),
          aktualnyTytul("WSZYSTKIE PRODUKTY") {
    }

    virtual ~MenuGoscia() = default;

    void uruchom() {
        bool czyDziala = true;

        wyswietlWidok();

        while (czyDziala) {
            int wybor = wczytajLiczbeCalkowita("Wybierz opcje: ");
            czyDziala = obsluzWybor(wybor);
        }
    }
    virtual bool obsluzWybor(int wybor) {
        switch (wybor) {
        case 1:
            pokazWszystkieProdukty();
            break;

        case 2:
            wyszukajProdukt();
            break;

        case 3:
            filtrujPoKategorii();
            break;

        case 4:
            filtrujPoCenie();
            break;

        case 5:
            pokazSzczegolyProduktu();
            break;

        case 0:
            return false;

        default:
            wyswietlWidok();
            cout << "Nie ma takiej opcji. Sprobuj ponownie." << endl;
            cout << endl;
            break;
        }

        return true;
    }


    protected:
    virtual void wyswietlMenu() const {
        cout << "=== MENU GLOWNE ===" << endl;
        cout << "1. Wyswietl wszystkie produkty" << endl;
        cout << "2. Wyszukaj produkt po nazwie" << endl;
        cout << "3. Filtruj produkty po kategorii" << endl;
        cout << "4. Filtruj produkty po cenie" << endl;
        cout << "5. Pokaz szczegoly produktu" << endl;
        cout << "0. Wyjdz" << endl;
        cout << endl;
    }

    void wyswietlWidok() const {
        wyczyscEkran();

        wyswietlMenu();

        cout << "=== " << aktualnyTytul << " ===" << endl;
        gosc->wyswietlProdukty(aktualneProdukty);

        cout << endl;
    }

    void pokazWszystkieProdukty() {
        aktualneProdukty = serwisProduktow->pobierzProdukty();
        aktualnyTytul = "WSZYSTKIE PRODUKTY";

        wyswietlWidok();
    }

    void wyszukajProdukt() {
        string fraza = wczytajTekst("Podaj nazwe lub fragment nazwy produktu: ");

        aktualneProdukty = serwisProduktow->wyszukajProduktyPoNazwie(fraza);
        aktualnyTytul = "WYNIKI WYSZUKIWANIA: " + fraza;

        wyswietlWidok();
    }

    void filtrujPoKategorii() {
        string kategoria = wczytajTekst("Podaj kategorie: ");

        aktualneProdukty = serwisProduktow->filtrujProduktyPoKategorii(kategoria);
        aktualnyTytul = "PRODUKTY Z KATEGORII: " + kategoria;

        wyswietlWidok();
    }

    void filtrujPoCenie() {
        double cenaMinimalna = wczytajLiczbeZmiennoprzecinkowa("Podaj cene minimalna: ");
        double cenaMaksymalna = wczytajLiczbeZmiennoprzecinkowa("Podaj cene maksymalna: ");

        aktualneProdukty = serwisProduktow->filtrujProduktyPoCenie(
            cenaMinimalna,
            cenaMaksymalna
        );

        aktualnyTytul = "PRODUKTY W ZAKRESIE CEN";

        wyswietlWidok();
    }

    void pokazSzczegolyProduktu() {
        int idProduktu = wczytajLiczbeCalkowita("Podaj ID produktu: ");

        wyczyscEkran();
        wyswietlMenu();

        cout << "=== SZCZEGOLY PRODUKTU ===" << endl;
        gosc->pokazSzczegolyProduktu(idProduktu);

        cout << endl;
    }

    void wyczyscEkran() const {
        cout << "\033[H\033[2J" << flush;
    }

    public:
    int wczytajLiczbeCalkowita(const string& komunikat) const {
        int liczba;

        while (true) {
            cout << komunikat;

            if (cin >> liczba) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return liczba;
            }

            cout << "Nieprawidlowa liczba. Sprobuj ponownie." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double wczytajLiczbeZmiennoprzecinkowa(const string& komunikat) const {
        double liczba;

        while (true) {
            cout << komunikat;

            if (cin >> liczba) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return liczba;
            }

            cout << "Nieprawidlowa liczba. Sprobuj ponownie." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string wczytajTekst(const string& komunikat) const {
        string tekst;

        cout << komunikat;
        getline(cin, tekst);

        return tekst;
    }
};