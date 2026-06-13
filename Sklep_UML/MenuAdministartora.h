#pragma once

#include "Administrator.h"
#include "SerwisProduktow.h"
#include "MenuGoscia.h"

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

class MenuAdministrator : public MenuGoscia {
private:
    Administrator* administrator;


public:
    MenuAdministrator(Administrator& administrator, SerwisProduktow& serwisProduktow)
        : MenuGoscia(administrator, serwisProduktow),
          administrator(&administrator) {

    }

protected:

    bool obsluzWybor(int wybor) override {
        switch (wybor) {
        case 6:
            dodajProdukt();
            return true;

        case 7:
            usunProdukt();
            return true;

        case 8:
            edytujProdukt();
            return true;

        default:
            return MenuGoscia::obsluzWybor(wybor);
        }
    }

    void wyswietlMenu() const {
        cout << "=== MENU ADMINISTRATORA ===" << endl;
        cout << "1. Wyswietl wszystkie produkty" << endl;
        cout << "2. Wyszukaj produkt po nazwie" << endl;
        cout << "3. Filtruj produkty po kategorii" << endl;
        cout << "4. Filtruj produkty po cenie" << endl;
        cout << "5. Pokaz szczegoly produktu" << endl;
        cout << "6. Dodaj produkt" << endl;
        cout << "7. Usun produkt" << endl;
        cout << "8. Edytuj produkt" << endl;
        cout << "0. Wyjdz" << endl;
        cout << endl;
    }

private:
    void dodajProdukt(){
        int id = wczytajLiczbeCalkowita("Podaj ID produktu:");
        string nazwa = wczytajTekst("Podaj nazwe produktu:");
        double cena = wczytajLiczbeZmiennoprzecinkowa("Podaj cene produktu:");
        int stanMagazynowy = wczytajLiczbeCalkowita("Podaj stan magazynowy produktu:");
        string kategoria = wczytajTekst("Podaj kategorie produktu:");
        string opis = wczytajTekst("Podaj opis produktu:");

        Produkt nowyProdukt(id, nazwa, cena, stanMagazynowy, kategoria, opis);
        bool czyDodano = administrator->dodajProdukt(nowyProdukt);

        aktualneProdukty = serwisProduktow->pobierzProdukty();
        aktualnyTytul = "WSZYSTKIE PRODUKTY";
        wyswietlWidok();

        if (czyDodano) {
            cout << "Produkt dodany pomyslnie." << endl;
        } else {
            cout << "Nie udalo sie dodac produktu. Sprawdz dane i sprobuj ponownie." << endl;
        }
    }

    void usunProdukt() {
        int idProduktu =
            wczytajLiczbeCalkowita(
                "Podaj ID produktu do usuniecia: "
            );

        bool czyUsunieto =
            administrator->usunProdukt(idProduktu);

        aktualneProdukty =
            serwisProduktow->pobierzProdukty();

        aktualnyTytul = "WSZYSTKIE PRODUKTY";

        wyswietlWidok();

        if (czyUsunieto) {
            cout << "Produkt zostal usuniety." << endl;
        }
        else {
            cout
                << "Nie znaleziono produktu "
                << "o podanym ID."
                << endl;
        }

        cout << endl;
    }

    void edytujProdukt() {
        int idProduktu = wczytajLiczbeCalkowita("Podaj ID produktu do edycji: ");

        cout << "Co chcesz zmienic?" << endl;
        cout << "1. Nazwe" << endl;
        cout << "2. Cene" << endl;
        cout << "3. Stan magazynowy" << endl;
        cout << "4. Kategorie" << endl;

        int co = wczytajLiczbeCalkowita("Wybierz opcje: ");

        bool czyZmieniono = false;

        switch (co) {
        case 1: {
            string nowaNazwa = wczytajTekst("Podaj nowa nazwe: ");
            czyZmieniono = administrator->zmienNazweProduktu(idProduktu, nowaNazwa);
            break;
        }
        case 2: {
            double nowaCena = wczytajLiczbeZmiennoprzecinkowa("Podaj nowa cene: ");
            czyZmieniono = administrator->zmienCeneProduktu(idProduktu, nowaCena);
            break;
        }
        case 3: {
            int nowyStan = wczytajLiczbeCalkowita("Podaj nowy stan magazynowy: ");
            czyZmieniono = administrator->zmienStanMagazynowy(idProduktu, nowyStan);
            break;
        }
        case 4: {
            string nowaKategoria = wczytajTekst("Podaj nowa kategorie: ");
            czyZmieniono = administrator->zmienKategorieProduktu(idProduktu, nowaKategoria);
            break;
        }
        default:
            cout << "Nie ma takiej opcji." << endl;
            break;
        }

        aktualneProdukty = serwisProduktow->pobierzProdukty();
        aktualnyTytul = "WSZYSTKIE PRODUKTY";
        wyswietlWidok();

        if (czyZmieniono) {
            cout << "Produkt zostal zaktualizowany." << endl;
        }
        else {
            cout << "Nie udalo sie zaktualizowac produktu. Sprawdz ID i dane." << endl;
        }

        cout << endl;
    }
};