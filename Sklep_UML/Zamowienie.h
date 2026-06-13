#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H

#include "Koszyk.h"
#include "AdresDostawy.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// mozliwe stany w jakich moze byc zamowienie
enum class StatusZamowienia {
    Utworzone,
    OczekujeNaPlatnosc,
    Oplacone,
    Anulowane,
    Zrealizowane
};

// jedno zamowienie zlozone przez klienta (kopia koszyka + adres + status)
class Zamowienie {
    public:
    int id;
    int idKlienta;
    
    Koszyk koszyk;
    
    double wartosc;
    
    AdresDostawy adresDostawy;
    StatusZamowienia status;

    Zamowienie() : id(0), idKlienta(0), wartosc(0.0), status(StatusZamowienia::Utworzone) {}
    ~Zamowienie() {}

    Zamowienie(int id, int idKlienta, const Koszyk& koszyk, double wartosc, const AdresDostawy& adresDostawy, StatusZamowienia status)
        : id(id), idKlienta(idKlienta), koszyk(koszyk), wartosc(wartosc), adresDostawy(adresDostawy), status(status) {}

    bool zmienStatus(StatusZamowienia nowyStatus) {
        status = nowyStatus;
        return true;
    }

    // krotka info o zamowieniu w jednej linii (do historii)
    void wyswietlPodsumowanie() {
        cout
            << "Zamowienie #" << id
            << " | Klient: " << idKlienta
            << " | Wartosc: " << fixed << setprecision(2) << wartosc << " zl"
            << " | Status: " << statusNaTekst(status)
            << endl;
    }

    // pelne szczegoly zamowienia - adres, zawartosc koszyka i wartosc
    void wyswietlSzczegoly() {
        cout << "=== SZCZEGOLY ZAMOWIENIA #" << id << " ===" << endl;
        cout << "Klient (ID): " << idKlienta << endl;
        cout << "Status: " << statusNaTekst(status) << endl;
        cout << "--- Adres dostawy ---" << endl;
        adresDostawy.wyswietl();
        cout << "--- Zawartosc ---" << endl;
        koszyk.wyswietlKoszyk();
        cout
            << "Wartosc zamowienia: "
            << fixed << setprecision(2) << wartosc << " zl"
            << endl;
    }

private:
    string statusNaTekst(StatusZamowienia s) const {
        switch (s) {
        case StatusZamowienia::Utworzone:          return "Utworzone";
        case StatusZamowienia::OczekujeNaPlatnosc: return "Oczekuje na platnosc";
        case StatusZamowienia::Oplacone:           return "Oplacone";
        case StatusZamowienia::Anulowane:          return "Anulowane";
        case StatusZamowienia::Zrealizowane:       return "Zrealizowane";
        }

        return "Nieznany";
    }
};

#endif // ZAMOWIENIE_H