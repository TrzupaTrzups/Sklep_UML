#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H

#include "Koszyk.h"
#include "AdresDostawy.h"

enum class StatusZamowienia {
    Utworzone,
    OczekujeNaPlatnosc,
    Oplacone,
    Anulowane,
    Zrealizowane
};

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
    
    zmienStatus(StatusZamowienia nowyStatus);
    wyswietlPodsumowanie();
    wyswietlSzczegoly();
};

#endif // ZAMOWIENIE_H