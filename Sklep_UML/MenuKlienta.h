#pragma once

#include "Klient.h"
#include "MenuGoscia.h"
#include "SerwisAdresuDostaw.h"
#include "SerwisKartyPlatniczej.h"
#include "SerwisPlatnosci.h"
#include "SerwisProduktow.h"
#include "SerwisZamowien.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class MenuKlienta : public MenuGoscia {
private:
    Klient* klient;
    SerwisZamowien* serwisZamowien;
    SerwisAdresuDostaw* serwisAdresu;
    SerwisKartyPlatniczej* serwisKarty;
    SerwisPlatnosci* serwisPlatnosci;

public:
    MenuKlienta(Klient& klient, SerwisProduktow& serwisProduktow)
        : MenuGoscia(klient, serwisProduktow),
          klient(&klient),
          serwisZamowien(nullptr),
          serwisAdresu(nullptr),
          serwisKarty(nullptr),
          serwisPlatnosci(nullptr) {
    }

    MenuKlienta(
        Klient& klient,
        SerwisProduktow& serwisProduktow,
        SerwisZamowien& serwisZamowien,
        SerwisAdresuDostaw& serwisAdresu,
        SerwisKartyPlatniczej& serwisKarty,
        SerwisPlatnosci& serwisPlatnosci
    )
        : MenuGoscia(klient, serwisProduktow),
          klient(&klient),
          serwisZamowien(&serwisZamowien),
          serwisAdresu(&serwisAdresu),
          serwisKarty(&serwisKarty),
          serwisPlatnosci(&serwisPlatnosci) {
        klient.ustawSerwisy(serwisZamowien, serwisAdresu, serwisKarty);
    }

protected:
    bool obsluzWybor(int wybor) override {
        switch (wybor) {
        case 6:
            dodajProduktDoKoszyka();
            return true;

        case 7:
            zarzadzajKoszykiem();
            return true;

        case 8:
            zlozZamowienie();
            return true;

        case 9:
            oplacZamowienie();
            return true;

        case 10:
            sprawdzStatusZamowienia();
            return true;

        default:
            return MenuGoscia::obsluzWybor(wybor);
        }
    }

    void wyswietlMenu() const override {
        cout << "=== MENU KLIENTA ===" << endl;
        cout << "1. Wyswietl wszystkie produkty" << endl;
        cout << "2. Wyszukaj produkt po nazwie" << endl;
        cout << "3. Filtruj produkty po kategorii" << endl;
        cout << "4. Filtruj produkty po cenie" << endl;
        cout << "5. Pokaz szczegoly produktu" << endl;
        cout << "6. Dodaj produkt do koszyka" << endl;
        cout << "7. Zarzadzaj koszykiem" << endl;
        cout << "8. Zloz zamowienie" << endl;
        cout << "9. Oplac zamowienie" << endl;
        cout << "10. Sprawdz status zamowienia" << endl;
        cout << "0. Wyjdz" << endl;
        cout << endl;
    }

private:
    void dodajProduktDoKoszyka() {
        int idProduktu = wczytajLiczbeCalkowita("Podaj ID produktu: ");
        int ilosc = wczytajLiczbeCalkowita("Podaj ilosc: ");

        const Produkt* produkt = serwisProduktow->znajdzProduktPoId(idProduktu);

        if (produkt == nullptr) {
            wyswietlWidok();
            cout << "Nie znaleziono produktu o podanym ID." << endl;
            cout << endl;
            return;
        }

        if (!czyIloscPoprawna(*produkt, ilosc, pobierzIloscWKoszyku(idProduktu))) {
            wyswietlWidok();
            cout << "Nie mozna dodac produktu. Sprawdz ilosc i stan magazynowy." << endl;
            cout << endl;
            return;
        }

        bool czyDodano = klient->koszyk.dodajProdukt(idProduktu, ilosc);

        wyswietlWidok();

        if (czyDodano) {
            cout << "Produkt zostal dodany do koszyka." << endl;
        } else {
            cout << "Nie udalo sie dodac produktu do koszyka." << endl;
        }

        cout << endl;
    }

    void zarzadzajKoszykiem() {
        bool czyZarzadzac = true;

        while (czyZarzadzac) {
            wyczyscEkran();

            cout << "=== ZARZADZANIE KOSZYKIEM ===" << endl;
            klient->pokazKoszyk();
            cout << endl;
            cout << "1. Zmien ilosc produktu" << endl;
            cout << "2. Usun produkt z koszyka" << endl;
            cout << "3. Wyczysc koszyk" << endl;
            cout << "0. Powrot" << endl;
            cout << endl;

            int wybor = wczytajLiczbeCalkowita("Wybierz opcje: ");

            switch (wybor) {
            case 1:
                zmienIloscProduktuWKoszyku();
                break;

            case 2:
                usunProduktZKoszyka();
                break;

            case 3:
                klient->koszyk.wyczysc();
                cout << "Koszyk zostal wyczyszczony." << endl;
                break;

            case 0:
                czyZarzadzac = false;
                break;

            default:
                cout << "Nie ma takiej opcji. Sprobuj ponownie." << endl;
                break;
            }
        }

        wyswietlWidok();
    }

    void zmienIloscProduktuWKoszyku() {
        int idProduktu = wczytajLiczbeCalkowita("Podaj ID produktu w koszyku: ");
        int ilosc = wczytajLiczbeCalkowita("Podaj nowa ilosc: ");

        const Produkt* produkt = serwisProduktow->znajdzProduktPoId(idProduktu);

        if (produkt == nullptr) {
            cout << "Nie znaleziono produktu." << endl;
            return;
        }

        if (!czyIloscPoprawna(*produkt, ilosc, 0)) {
            cout << "Nieprawidlowa ilosc albo za maly stan magazynowy." << endl;
            return;
        }

        if (klient->koszyk.zmienIlosc(idProduktu, ilosc)) {
            cout << "Ilosc zostala zmieniona." << endl;
        } else {
            cout << "Nie znaleziono produktu w koszyku." << endl;
        }
    }

    void usunProduktZKoszyka() {
        int idProduktu = wczytajLiczbeCalkowita("Podaj ID produktu do usuniecia: ");

        if (klient->koszyk.usunProdukt(idProduktu)) {
            cout << "Produkt zostal usuniety z koszyka." << endl;
        } else {
            cout << "Nie znaleziono produktu w koszyku." << endl;
        }
    }

    void zlozZamowienie() {
        if (klient->koszyk.czyPusty()) {
            wyswietlWidok();
            cout << "Koszyk jest pusty. Nie mozna zlozyc zamowienia." << endl;
            cout << endl;
            return;
        }

        if (serwisZamowien == nullptr || serwisAdresu == nullptr) {
            wyswietlWidok();
            klient->zlozZamowienie();
            cout << endl;
            return;
        }

        AdresDostawy adres;
        serwisAdresu->pobierzAdres(adres);

        if (!adres.czyKompletny()) {
            cout << "Brak kompletnego adresu dostawy." << endl;

            if (!czyTak("Czy chcesz wprowadzic adres teraz? (t/n): ")) {
                wyswietlWidok();
                cout << "Zamowienie nie zostalo zlozone." << endl;
                cout << endl;
                return;
            }

            if (!wczytajIZapiszAdres()) {
                wyswietlWidok();
                cout << "Nie udalo sie zapisac adresu dostawy." << endl;
                cout << endl;
                return;
            }

            serwisAdresu->pobierzAdres(adres);
        }

        bool czyUtworzono =
            serwisZamowien->utworzZamowienie(klient->id, klient->koszyk, adres);

        wyswietlWidok();

        if (!czyUtworzono) {
            cout << "Nie udalo sie zlozyc zamowienia." << endl;
            cout << endl;
            return;
        }

        int idZamowienia = pobierzOstatnieIdZamowieniaKlienta();

        if (idZamowienia != 0) {
            serwisZamowien->zmienStatus(
                idZamowienia,
                StatusZamowienia::OczekujeNaPlatnosc
            );
        }

        klient->koszyk.wyczysc();

        cout << "Zamowienie zostalo zlozone.";

        if (idZamowienia != 0) {
            cout << " ID zamowienia: " << idZamowienia << ".";
        }

        cout << endl;
        cout << endl;
    }

    void oplacZamowienie() {
        if (serwisZamowien == nullptr || serwisPlatnosci == nullptr || serwisKarty == nullptr) {
            wyswietlWidok();
            cout << "Platnosci sa niedostepne." << endl;
            cout << endl;
            return;
        }

        int idZamowienia = wczytajLiczbeCalkowita("Podaj ID zamowienia do oplacenia: ");
        Zamowienie* zamowienie = serwisZamowien->pobierzZamowieniePoId(idZamowienia);

        wyswietlWidok();

        if (!czyZamowienieNalezyDoKlienta(zamowienie)) {
            cout << "Nie znaleziono Twojego zamowienia o podanym ID." << endl;
            cout << endl;
            return;
        }

        if (zamowienie->status == StatusZamowienia::Oplacone) {
            cout << "To zamowienie jest juz oplacone." << endl;
            cout << endl;
            return;
        }

        if (
            zamowienie->status == StatusZamowienia::Anulowane ||
            zamowienie->status == StatusZamowienia::Zrealizowane
        ) {
            cout << "Tego zamowienia nie mozna juz oplacic." << endl;
            cout << endl;
            return;
        }

        KartaPlatnicza karta = serwisKarty->pobierzKarte();

        if (!karta.czyPoprawna()) {
            cout << "Brak poprawnej karty platniczej." << endl;

            if (!czyTak("Czy chcesz wprowadzic karte teraz? (t/n): ")) {
                cout << "Platnosc przerwana." << endl;
                cout << endl;
                return;
            }

            if (!wczytajIZapiszKarte()) {
                cout << "Nie udalo sie zapisac poprawnej karty." << endl;
                cout << endl;
                return;
            }
        }

        if (zamowienie->status == StatusZamowienia::Utworzone) {
            serwisZamowien->zmienStatus(
                idZamowienia,
                StatusZamowienia::OczekujeNaPlatnosc
            );
        }

        if (serwisPlatnosci->wykonajPlatnosc(zamowienie->wartosc)) {
            serwisZamowien->zmienStatus(idZamowienia, StatusZamowienia::Oplacone);
            cout << "Zamowienie zostalo oplacone." << endl;
        } else {
            cout << "Nie udalo sie oplacic zamowienia." << endl;
        }

        cout << endl;
    }

    void sprawdzStatusZamowienia() {
        int idZamowienia = wczytajLiczbeCalkowita("Podaj ID zamowienia: ");

        wyswietlWidok();

        if (serwisZamowien == nullptr) {
            klient->pokazStatusZamowienia(idZamowienia);
            cout << endl;
            return;
        }

        Zamowienie* zamowienie = serwisZamowien->pobierzZamowieniePoId(idZamowienia);

        if (!czyZamowienieNalezyDoKlienta(zamowienie)) {
            cout << "Nie znaleziono Twojego zamowienia o podanym ID." << endl;
            cout << endl;
            return;
        }

        zamowienie->wyswietlPodsumowanie();
        cout << endl;
    }

    bool wczytajIZapiszAdres() {
        string odbiorca = wczytajTekst("Odbiorca: ");
        string ulica = wczytajTekst("Ulica: ");
        string kodPocztowy = wczytajTekst("Kod pocztowy: ");
        string miasto = wczytajTekst("Miasto: ");
        string telefon = wczytajTekst("Telefon: ");

        AdresDostawy adres(odbiorca, ulica, kodPocztowy, miasto, telefon);

        if (!adres.czyKompletny()) {
            return false;
        }

        return serwisAdresu->zapiszAdres(adres);
    }

    bool wczytajIZapiszKarte() {
        string wlasciciel = wczytajTekst("Wlasciciel karty: ");
        string numerKarty = wczytajTekst("Numer karty: ");
        string dataWaznosci = wczytajTekst("Data waznosci: ");
        string cvv = wczytajTekst("CVV: ");

        KartaPlatnicza karta(wlasciciel, numerKarty, dataWaznosci, cvv);

        if (!karta.czyPoprawna()) {
            return false;
        }

        return serwisKarty->zapiszKarte(karta);
    }

    bool czyTak(const string& komunikat) const {
        string odpowiedz = wczytajTekst(komunikat);

        return odpowiedz == "t" ||
               odpowiedz == "T" ||
               odpowiedz == "tak" ||
               odpowiedz == "Tak" ||
               odpowiedz == "TAK";
    }

    bool czyIloscPoprawna(
        const Produkt& produkt,
        int ilosc,
        int iloscJuzWKoszyku
    ) const {
        if (ilosc <= 0) {
            return false;
        }

        return ilosc + iloscJuzWKoszyku <= produkt.pobierzStanMagazynowy();
    }

    int pobierzIloscWKoszyku(int idProduktu) {
        for (PozycjaKoszyka& pozycja : klient->koszyk.pozycje) {
            if (pozycja.pobierzProdukt().pobierzId() == idProduktu) {
                return pozycja.pobierzIlosc();
            }
        }

        return 0;
    }

    int pobierzOstatnieIdZamowieniaKlienta() {
        if (serwisZamowien == nullptr) {
            return 0;
        }

        vector<Zamowienie> zamowienia =
            serwisZamowien->pobierzZamowieniaKlienta(klient->id);

        if (zamowienia.empty()) {
            return 0;
        }

        return zamowienia.back().id;
    }

    bool czyZamowienieNalezyDoKlienta(Zamowienie* zamowienie) const {
        return zamowienie != nullptr && zamowienie->idKlienta == klient->id;
    }
};
