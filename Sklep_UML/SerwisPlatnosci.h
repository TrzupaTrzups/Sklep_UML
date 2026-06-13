#pragma once

#include "KartaPlatnicza.h"
#include "SerwisKartyPlatniczej.h"

#include <iomanip>
#include <iostream>

using namespace std;

// realizuje platnosc korzystajac z karty zapisanej w SerwisKartyPlatniczej
class SerwisPlatnosci {
private:
    SerwisKartyPlatniczej& skp;

public:
    SerwisPlatnosci(SerwisKartyPlatniczej& skp)
        : skp(skp) {
    }

    // Wykonuje platnosc na podana kwote przy uzyciu zapisanej karty.
    // Zwraca true, gdy kwota > 0 i karta jest poprawna (na diagramie void).
    bool wykonajPlatnosc(double kwota) {
        if (kwota <= 0) {
            cout << "Nieprawidlowa kwota platnosci." << endl;
            return false;
        }

        KartaPlatnicza karta = skp.pobierzKarte();

        if (!karta.czyPoprawna()) {
            cout << "Brak poprawnej karty platniczej. Platnosc odrzucona." << endl;
            return false;
        }

        cout
            << "Platnosc " << fixed << setprecision(2) << kwota
            << " zl karta " << karta.pobierzZamaskowanyNumer()
            << " zostala zrealizowana." << endl;

        return true;
    }
};
