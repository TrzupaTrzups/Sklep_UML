#ifndef KOSZYK_H
#define KOSZYK_H

#include <vector>
#include "PozycjaKoszyka.h"

using namespace std;

class Koszyk {
    public:
    vector <PozycjaKoszyka> pozycje;

    bool dodajProdukt(Produkt p, int ilosc);
    bool usunProdukt(int idProduktu);
    bool zmienIlosc(int idProduktu, int ilosc);
    double obliczWartosc();
    void wyczysc();
    bool czyPusty();
    void wyswietlKoszyk();
};

#endif // KOSZYK_H