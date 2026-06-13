#pragma once

#include "Produkt.h"
#include "RepozytoriumProduktow.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

class SerwisProduktow {
private:
    vector<Produkt> produkty;
    RepozytoriumProduktow repozytorium;

public:
    SerwisProduktow(string& sciezkaDoPliku)
        : repozytorium(sciezkaDoPliku) {
        produkty = repozytorium.wczytajProdukty();
    }

// geter do vectora produktów.
    const vector<Produkt>& pobierzProdukty() const {
        return produkty;
    }

    // Szuka produktu po podanym ID.
    // Jeśli produkt istnieje, zwraca wskaźnik do tego produktu.
    // Jeśli produkt nie istnieje, zwraca nullptr.
    const Produkt* znajdzProduktPoId(int id) {
        for (Produkt& produkt : produkty) {
            if (produkt.pobierzId() == id) {
                return &produkt;
            }
        }

        return nullptr;
    }

    bool dodajProdukt(Produkt produkt) {
        if (!produkt.czyPoprawny()) {
            return false;
        }

        if (znajdzProduktPoId(produkt.pobierzId()) != nullptr) {
            return false;
        }

        produkty.push_back(produkt);
        return repozytorium.zapiszProdukty(produkty);
    }

    bool usunProdukt(int id) {
        auto liczbaProduktowPrzedUsunieciem = produkty.size();

        produkty.erase(
            remove_if(
                produkty.begin(),
                produkty.end(),
                [id](Produkt& produkt) {
                    return produkt.pobierzId() == id;
                }
            ),
            produkty.end()
        );

        if (produkty.size() == liczbaProduktowPrzedUsunieciem) {
            return false;
        }

        return repozytorium.zapiszProdukty(produkty);
    }

    // Metody pomocnicze edycji. Na diagramie operacje zmien... naleza do klasy
    // Administrator; tutaj jest warstwa, ktora realnie modyfikuje dane i zapisuje plik.
    bool zmienNazweProduktu(int id, string nowaNazwa) {
        if (nowaNazwa.empty()) {
            return false;
        }

        Produkt* produkt = znajdzModyfikowalny(id);

        if (produkt == nullptr) {
            return false;
        }

        produkt->ustawNazwe(nowaNazwa);
        return repozytorium.zapiszProdukty(produkty);
    }

    bool zmienCeneProduktu(int id, double nowaCena) {
        if (nowaCena < 0) {
            return false;
        }

        Produkt* produkt = znajdzModyfikowalny(id);

        if (produkt == nullptr) {
            return false;
        }

        produkt->ustawCene(nowaCena);
        return repozytorium.zapiszProdukty(produkty);
    }

    bool zmienStanMagazynowy(int id, int nowyStan) {
        if (nowyStan < 0) {
            return false;
        }

        Produkt* produkt = znajdzModyfikowalny(id);

        if (produkt == nullptr) {
            return false;
        }

        produkt->ustawStanMagazynowy(nowyStan);
        return repozytorium.zapiszProdukty(produkty);
    }

    bool zmienKategorieProduktu(int id, string nowaKategoria) {
        if (nowaKategoria.empty()) {
            return false;
        }

        Produkt* produkt = znajdzModyfikowalny(id);

        if (produkt == nullptr) {
            return false;
        }

        produkt->ustawKategorie(nowaKategoria);
        return repozytorium.zapiszProdukty(produkty);
    }

    vector<Produkt> wyszukajProduktyPoNazwie(const string& fraza) const {
        vector<Produkt> wynik;

        if (fraza.empty()) {
            return produkty;
        }

        string frazaMaleLitery = zamienNaMaleLitery(fraza);

        for (Produkt produkt : produkty) {
            string nazwaMaleLitery = zamienNaMaleLitery(produkt.pobierzNazwe());

            if (nazwaMaleLitery.find(frazaMaleLitery) != string::npos) {
                wynik.push_back(produkt);
            }
        }

        return wynik;
    }

    vector<Produkt> filtrujProduktyPoKategorii(const string& kategoria) const {
        vector<Produkt> wynik;

        if (kategoria.empty()) {
            return wynik;
        }

        string szukanaKategoria = zamienNaMaleLitery(kategoria);

        for (Produkt produkt : produkty) {
            string kategoriaProduktu = zamienNaMaleLitery(produkt.pobierzKategorie());

            if (kategoriaProduktu == szukanaKategoria) {
                wynik.push_back(produkt);
            }
        }

        return wynik;
    }

    vector<Produkt> filtrujProduktyPoCenie(double cenaMinimalna, double cenaMaksymalna) const {
        vector<Produkt> wynik;

        if (cenaMinimalna < 0 || cenaMaksymalna < 0) {
            return wynik;
        }

        if (cenaMinimalna > cenaMaksymalna) {
            return wynik;
        }

        for (Produkt produkt : produkty) {
            if (
                produkt.pobierzCene() >= cenaMinimalna &&
                produkt.pobierzCene() <= cenaMaksymalna
            ) {
                wynik.push_back(produkt);
            }
        }

        return wynik;
    }

    vector<string> pobierzKategorie() const {
        vector<string> kategorie;

        for (Produkt produkt : produkty) {
            string kategoria = produkt.pobierzKategorie();

            if (find(kategorie.begin(), kategorie.end(), kategoria) == kategorie.end()) {
                kategorie.push_back(kategoria);
            }
        }

        sort(kategorie.begin(), kategorie.end());

        return kategorie;
    }

private:

//Funkcja pomocnicza zwracajaca modyfikowalny wskaznik do produktu o danym ID, uzywana przez metody edycji.
    Produkt* znajdzModyfikowalny(int id) {
        for (Produkt& produkt : produkty) {
            if (produkt.pobierzId() == id) {
                return &produkt;
            }
        }

        return nullptr;
    }

//Funkcja pomocnicza do zamiany tekstu na małe litery, nie ma jej w diagramie klas. Pomocna do wyszukiwania produktów bez rozróżniania wielkości liter.
    string zamienNaMaleLitery(const string& tekst) const {
        string wynik = tekst;

        for (char& znak : wynik) {
            znak = static_cast<char>(
                tolower(static_cast<unsigned char>(znak))
            );
        }

        return wynik;
    }
};