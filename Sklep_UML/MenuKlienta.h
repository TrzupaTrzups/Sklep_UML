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

        AdresDostawy adres = wybierzAdresDostawy();

        if (!adres.czyKompletny()) {
            wyswietlWidok();
            cout << "Zamowienie nie zostalo zlozone. Nie wybrano adresu dostawy." << endl;
            cout << endl;
            return;
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

        if (!wybierzIZapiszKarteDoPlatnosci()) {
            cout << "Platnosc przerwana. Nie wybrano poprawnej karty." << endl;
            cout << endl;
            return;
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

    AdresDostawy wybierzAdresDostawy() {
        AdresDostawy zapisanyAdres;
        serwisAdresu->pobierzAdres(zapisanyAdres);

        AdresDostawy domyslnyAdres = pobierzDomyslnyAdres();

        while (true) {
            cout << "=== WYBOR ADRESU DOSTAWY ===" << endl;

            if (zapisanyAdres.czyKompletny()) {
                cout << "1. Uzyj zapisanego adresu: ";
                wyswietlAdresWKrotkiejFormie(zapisanyAdres);
            } else {
                cout << "1. Uzyj zapisanego adresu (brak zapisanego adresu)" << endl;
            }

            cout << "2. Uzyj domyslnego adresu: ";
            wyswietlAdresWKrotkiejFormie(domyslnyAdres);
            cout << "3. Wpisz nowy adres" << endl;
            cout << "0. Anuluj skladanie zamowienia" << endl;
            cout << endl;

            int wybor = wczytajLiczbeCalkowita("Wybierz adres dostawy: ");

            switch (wybor) {
            case 1:
                if (zapisanyAdres.czyKompletny()) {
                    return zapisanyAdres;
                }

                cout << "Brak kompletnego zapisanego adresu." << endl;
                break;

            case 2:
                return domyslnyAdres;

            case 3:
                if (wczytajIZapiszAdres()) {
                    serwisAdresu->pobierzAdres(zapisanyAdres);
                    return zapisanyAdres;
                }

                cout << "Nie udalo sie zapisac kompletnego adresu." << endl;
                break;

            case 0:
                return AdresDostawy();

            default:
                cout << "Nie ma takiej opcji. Sprobuj ponownie." << endl;
                break;
            }

            cout << endl;
        }
    }

    bool wybierzIZapiszKarteDoPlatnosci() {
        KartaPlatnicza zapisanaKarta = serwisKarty->pobierzKarte();
        KartaPlatnicza domyslnaKarta = pobierzDomyslnaKarte();

        while (true) {
            cout << "=== WYBOR KARTY PLATNICZEJ ===" << endl;

            if (zapisanaKarta.czyPoprawna()) {
                cout << "1. Uzyj zapisanej karty: ";
                wyswietlKarteWKrotkiejFormie(zapisanaKarta);
            } else {
                cout << "1. Uzyj zapisanej karty (brak poprawnej zapisanej karty)" << endl;
            }

            cout << "2. Uzyj domyslnej karty: ";
            wyswietlKarteWKrotkiejFormie(domyslnaKarta);
            cout << "3. Wpisz nowa karte" << endl;
            cout << "0. Anuluj platnosc" << endl;
            cout << endl;

            int wybor = wczytajLiczbeCalkowita("Wybierz karte platnicza: ");

            switch (wybor) {
            case 1:
                if (zapisanaKarta.czyPoprawna()) {
                    return true;
                }

                cout << "Brak poprawnej zapisanej karty." << endl;
                break;

            case 2:
                return serwisKarty->zapiszKarte(domyslnaKarta);

            case 3:
                if (wczytajIZapiszKarte()) {
                    return true;
                }

                cout << "Nie udalo sie zapisac poprawnej karty." << endl;
                break;

            case 0:
                return false;

            default:
                cout << "Nie ma takiej opcji. Sprobuj ponownie." << endl;
                break;
            }

            cout << endl;
        }
    }

    AdresDostawy pobierzDomyslnyAdres() const {
        return AdresDostawy(
            "Jan Kowalski",
            "ul. Przykladowa 1",
            "00-001",
            "Warszawa",
            "123456789"
        );
    }

    KartaPlatnicza pobierzDomyslnaKarte() const {
        return KartaPlatnicza(
            "Jan Kowalski",
            "4111111111111111",
            "12/30",
            "123"
        );
    }

    void wyswietlAdresWKrotkiejFormie(const AdresDostawy& adres) const {
        cout
            << adres.pobierzOdbiorce()
            << ", " << adres.pobierzUlice()
            << ", " << adres.pobierzKodPocztowy()
            << " " << adres.pobierzMiasto()
            << ", tel. " << adres.pobierzTelefon()
            << endl;
    }

    void wyswietlKarteWKrotkiejFormie(const KartaPlatnicza& karta) const {
        cout
            << karta.pobierzWlasciciela()
            << ", " << karta.pobierzZamaskowanyNumer()
            << ", wazna do " << karta.pobierzDateWaznosci()
            << endl;
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
