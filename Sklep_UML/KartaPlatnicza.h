#pragma once

#include <iostream>
#include <string>

using namespace std;

class KartaPlatnicza {
private:
    string wlasciciel;
    string numerKarty;
    string dataWaznosci;
    string cvv;

public:
    KartaPlatnicza() = default;

    KartaPlatnicza(
        const string& wlasciciel,
        const string& numerKarty,
        const string& dataWaznosci,
        const string& cvv
    )
        : wlasciciel(wlasciciel),
          numerKarty(numerKarty),
          dataWaznosci(dataWaznosci),
          cvv(cvv) {
    }

    const string& pobierzWlasciciela() const {
        return wlasciciel;
    }

    const string& pobierzNumerKarty() const {
        return numerKarty;
    }

    const string& pobierzDateWaznosci() const {
        return dataWaznosci;
    }

    const string& pobierzCvv() const {
        return cvv;
    }

    bool czyPoprawna() const {
        if (wlasciciel.empty() || dataWaznosci.empty()) {
            return false;
        }

        if (!samaCyfry(numerKarty) || numerKarty.size() < 13 || numerKarty.size() > 19) {
            return false;
        }

        if (!samaCyfry(cvv) || cvv.size() < 3 || cvv.size() > 4) {
            return false;
        }

        return true;
    }

    // Zwraca numer z ukrytymi cyframi, widoczne tylko ostatnie 4.
    string pobierzZamaskowanyNumer() const {
        if (numerKarty.size() < 4) {
            return string(numerKarty.size(), '*');
        }

        string ostatnie4 = numerKarty.substr(numerKarty.size() - 4);
        return "**** **** **** " + ostatnie4;
    }

    void wyswietl() const {
        cout << "Wlasciciel: " << wlasciciel << endl;
        cout << "Numer karty: " << pobierzZamaskowanyNumer() << endl;
        cout << "Data waznosci: " << dataWaznosci << endl;
    }

private:
    static bool samaCyfry(const string& tekst) {
        if (tekst.empty()) {
            return false;
        }

        for (char znak : tekst) {
            if (znak < '0' || znak > '9') {
                return false;
            }
        }

        return true;
    }
};
