#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "SerwisProduktow.h"
#include "Gosc.h"

using namespace std;

void wyczyscEkran() {
    system("cls");
}

int wczytajLiczbeCalkowita(const string& komunikat) {
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

double wczytajLiczbeZmiennoprzecinkowa(const string& komunikat) {
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

string wczytajTekst(const string& komunikat) {
    string tekst;

    cout << komunikat;
    getline(cin, tekst);

    return tekst;
}

void wyswietlMenuGoscia() {
    cout << "=== MENU GOSCIA ===" << endl;
    cout << "1. Wyswietl wszystkie produkty" << endl;
    cout << "2. Wyszukaj produkt po nazwie" << endl;
    cout << "3. Filtruj produkty po kategorii" << endl;
    cout << "4. Filtruj produkty po cenie" << endl;
    cout << "5. Pokaz szczegoly produktu" << endl;
    cout << "0. Wyjdz" << endl;
    cout << endl;
}

void wyswietlWidokGoscia(
    Gosc& gosc,
    const string& tytul,
    const vector<Produkt>& produkty
) {
    wyczyscEkran();

    wyswietlMenuGoscia();

    cout << "=== " << tytul << " ===" << endl;
    gosc.wyswietlProdukty(produkty);

    cout << endl;
}

void uruchomMenuGoscia(Gosc& gosc, SerwisProduktow& serwisProduktow) {
    bool czyDziala = true;

    vector<Produkt> aktualneProdukty = serwisProduktow.pobierzWszystkieProdukty();
    string aktualnyTytul = "WSZYSTKIE PRODUKTY";

    wyswietlWidokGoscia(gosc, aktualnyTytul, aktualneProdukty);

    while (czyDziala) {
        int wybor = wczytajLiczbeCalkowita("Wybierz opcje: ");

        switch (wybor) {
        case 1:
            aktualneProdukty = serwisProduktow.pobierzWszystkieProdukty();
            aktualnyTytul = "WSZYSTKIE PRODUKTY";

            wyswietlWidokGoscia(gosc, aktualnyTytul, aktualneProdukty);
            break;

        case 2: {
            string fraza = wczytajTekst("Podaj nazwe lub fragment nazwy produktu: ");

            aktualneProdukty = serwisProduktow.wyszukajProduktyPoNazwie(fraza);
            aktualnyTytul = "WYNIKI WYSZUKIWANIA: " + fraza;

            wyswietlWidokGoscia(gosc, aktualnyTytul, aktualneProdukty);
            break;
        }

        case 3: {
            string kategoria = wczytajTekst("Podaj kategorie: ");

            aktualneProdukty = serwisProduktow.filtrujProduktyPoKategorii(kategoria);
            aktualnyTytul = "PRODUKTY Z KATEGORII: " + kategoria;

            wyswietlWidokGoscia(gosc, aktualnyTytul, aktualneProdukty);
            break;
        }

        case 4: {
            double cenaMinimalna = wczytajLiczbeZmiennoprzecinkowa("Podaj cene minimalna: ");
            double cenaMaksymalna = wczytajLiczbeZmiennoprzecinkowa("Podaj cene maksymalna: ");

            aktualneProdukty = serwisProduktow.filtrujProduktyPoCenie(
                cenaMinimalna,
                cenaMaksymalna
            );

            aktualnyTytul = "PRODUKTY W ZAKRESIE CEN";

            wyswietlWidokGoscia(gosc, aktualnyTytul, aktualneProdukty);
            break;
        }

        case 5: {
            int idProduktu = wczytajLiczbeCalkowita("Podaj ID produktu: ");

            wyczyscEkran();
            wyswietlMenuGoscia();

            cout << "=== SZCZEGOLY PRODUKTU ===" << endl;
            gosc.pokazSzczegolyProduktu(idProduktu);

            cout << endl;
            break;
        }

        case 0:
            czyDziala = false;
            break;

        default:
            wyswietlWidokGoscia(gosc, aktualnyTytul, aktualneProdukty);
            cout << "Nie ma takiej opcji. Sprobuj ponownie." << endl;
            cout << endl;
            break;
        }
    }
}

int main() {
    SerwisProduktow serwisProduktow("produkty.txt");

    Gosc gosc(serwisProduktow);

    uruchomMenuGoscia(gosc, serwisProduktow);

    wyczyscEkran();
    cout << "Koniec programu." << endl;

    return 0;
}