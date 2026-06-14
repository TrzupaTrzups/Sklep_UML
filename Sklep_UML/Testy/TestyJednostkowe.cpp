#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "NarzedziaTestowe.h"
#include "../AdresDostawy.h"
#include "../KartaPlatnicza.h"
#include "../Koszyk.h"
#include "../SerwisProduktow.h"
#include "../SerwisZamowien.h"

using namespace std;

// Zwraca sciezke do pliku z produktami testowymi niezaleznie od katalogu uruchomienia testow.
string sciezkaPlikuProduktowTestowych() {
    vector<string> sciezki = {
        "Sklep_UML/Testy/produkty_testowe.txt",
        "Testy/produkty_testowe.txt",
        "produkty_testowe.txt"
    };

    for (string& sciezka : sciezki) {
        ifstream plik(sciezka);

        if (plik.is_open()) {
            return sciezka;
        }
    }

    return sciezki[0];
}

// Porownuje liczby zmiennoprzecinkowe z mala tolerancja, aby uniknac problemow z precyzja double.
bool rowneDouble(double a, double b) {
    return fabs(a - b) < 0.001;
}

// Sprawdza, czy adres jest uznawany za kompletny tylko wtedy, gdy ma wypelnione wszystkie pola.
void testAdresDostawyKompletny() {
    AdresDostawy adres(
        "Jan Kowalski",
        "ul. Testowa 1",
        "00-001",
        "Warszawa",
        "123456789"
    );

    AdresDostawy niekompletny(
        "Jan Kowalski",
        "",
        "00-001",
        "Warszawa",
        "123456789"
    );

    assert(adres.czyKompletny());
    assert(!niekompletny.czyKompletny());
}

// Sprawdza walidacje danych karty oraz maskowanie numeru karty.
void testKartaPlatniczaWalidacjaIMaskowanie() {
    KartaPlatnicza karta(
        "Jan Kowalski",
        "4111111111111111",
        "12/30",
        "123"
    );

    KartaPlatnicza zlyNumer(
        "Jan Kowalski",
        "4111abcd11111111",
        "12/30",
        "123"
    );

    KartaPlatnicza zlyCvv(
        "Jan Kowalski",
        "4111111111111111",
        "12/30",
        "12x"
    );

    assert(karta.czyPoprawna());
    assert(karta.pobierzZamaskowanyNumer() == "**** **** **** 1111");
    assert(!zlyNumer.czyPoprawna());
    assert(!zlyCvv.czyPoprawna());
}

// Sprawdza podstawowy przeplyw koszyka: dodawanie, sumowanie, zmiane ilosci i usuwanie produktu.
void testKoszykDodawanieZmianaUsuniecie() {
    string sciezka = sciezkaPlikuProduktowTestowych();
    SerwisProduktow serwisProduktow(sciezka);
    Koszyk koszyk(&serwisProduktow);

    assert(koszyk.czyPusty());
    assert(koszyk.dodajProdukt(1, 2));
    assert(!koszyk.czyPusty());
    assert(koszyk.pozycje.size() == 1);
    assert(rowneDouble(koszyk.obliczWartosc(), 20.0));

    assert(koszyk.dodajProdukt(1, 1));
    assert(koszyk.pozycje.size() == 1);
    assert(koszyk.pozycje[0].pobierzIlosc() == 3);
    assert(rowneDouble(koszyk.obliczWartosc(), 30.0));

    assert(koszyk.zmienIlosc(1, 4));
    assert(koszyk.pozycje[0].pobierzIlosc() == 4);
    assert(rowneDouble(koszyk.obliczWartosc(), 40.0));

    assert(koszyk.usunProdukt(1));
    assert(koszyk.czyPusty());
}

// Sprawdza utworzenie zamowienia z koszyka oraz zmiane jego statusu.
void testSerwisZamowienTworzenieIStatus() {
    string sciezka = sciezkaPlikuProduktowTestowych();
    SerwisProduktow serwisProduktow(sciezka);
    Koszyk koszyk(&serwisProduktow);
    SerwisZamowien serwisZamowien;

    AdresDostawy adres(
        "Jan Kowalski",
        "ul. Testowa 1",
        "00-001",
        "Warszawa",
        "123456789"
    );

    assert(koszyk.dodajProdukt(2, 2));
    assert(serwisZamowien.utworzZamowienie(7, koszyk, adres));

    Zamowienie* zamowienie = serwisZamowien.pobierzZamowieniePoId(1);

    assert(zamowienie != nullptr);
    assert(zamowienie->id == 1);
    assert(zamowienie->idKlienta == 7);
    assert(zamowienie->status == StatusZamowienia::Utworzone);
    assert(rowneDouble(zamowienie->wartosc, 51.0));

    assert(serwisZamowien.zmienStatus(1, StatusZamowienia::Oplacone));
    assert(zamowienie->status == StatusZamowienia::Oplacone);
    assert(!serwisZamowien.zmienStatus(999, StatusZamowienia::Oplacone));
}

// Sprawdza, czy serwis zamowien odrzuca pusty koszyk i niekompletny adres dostawy.
void testSerwisZamowienOdrzucaNiepoprawneDane() {
    string sciezka = sciezkaPlikuProduktowTestowych();
    SerwisProduktow serwisProduktow(sciezka);
    Koszyk pustyKoszyk(&serwisProduktow);
    Koszyk koszyk(&serwisProduktow);
    SerwisZamowien serwisZamowien;

    AdresDostawy adres(
        "Jan Kowalski",
        "ul. Testowa 1",
        "00-001",
        "Warszawa",
        "123456789"
    );

    AdresDostawy niekompletnyAdres;

    assert(!serwisZamowien.utworzZamowienie(1, pustyKoszyk, adres));

    assert(koszyk.dodajProdukt(1, 1));
    assert(!serwisZamowien.utworzZamowienie(1, koszyk, niekompletnyAdres));
}

// Uruchamia wszystkie testy jednostkowe i wypisuje podsumowanie.
int main() {
    int liczbaZaliczonych = 0;

    cout << "=== TESTY JEDNOSTKOWE ===" << endl;
    cout << endl;

    uruchomTest(
        "Adres dostawy - kompletnosc",
        testAdresDostawyKompletny,
        liczbaZaliczonych
    );

    uruchomTest(
        "Karta platnicza - walidacja i maskowanie",
        testKartaPlatniczaWalidacjaIMaskowanie,
        liczbaZaliczonych
    );

    uruchomTest(
        "Koszyk - dodawanie, zmiana ilosci i usuwanie",
        testKoszykDodawanieZmianaUsuniecie,
        liczbaZaliczonych
    );

    uruchomTest(
        "Serwis zamowien - tworzenie i status",
        testSerwisZamowienTworzenieIStatus,
        liczbaZaliczonych
    );

    uruchomTest(
        "Serwis zamowien - odrzucanie niepoprawnych danych",
        testSerwisZamowienOdrzucaNiepoprawneDane,
        liczbaZaliczonych
    );

    cout << endl;
    cout << "Zaliczone testy: " << liczbaZaliczonych << endl;

    return 0;
}
