#pragma once

#include <iostream>
#include <string>

using namespace std;

class Produkt {
private:
    int id;
    string nazwa;
    double cena;
    int stanMagazynowy;
    string kategoria;
    string opis;

public:
    Produkt(
        int id,
        string& nazwa,
        double cena,
        int stanMagazynowy,
        string& kategoria,
        string& opis
    )
        : id(id),
        nazwa(nazwa),
        cena(cena),
        stanMagazynowy(stanMagazynowy),
        kategoria(kategoria),
        opis(opis) {
    }

    int pobierzId() const {
        return id;
    }

    const string& pobierzNazwe() const {
        return nazwa;
    }

    double pobierzCene() const {
        return cena;
    }

    int pobierzStanMagazynowy() const {
        return stanMagazynowy;
    }

    const string& pobierzKategorie() const {
        return kategoria;
    }

    const string& pobierzOpis() const {
        return opis;
    }

    void ustawNazwe(string& nowaNazwa) {
        nazwa = nowaNazwa;
    }

    void ustawCene(double nowaCena) {
        cena = nowaCena;
    }

    void ustawStanMagazynowy(int nowyStanMagazynowy) {
        stanMagazynowy = nowyStanMagazynowy;
    }

    void ustawKategorie(string& nowaKategoria) {
        kategoria = nowaKategoria;
    }

    void ustawOpis(string& nowyOpis) {
        opis = nowyOpis;
    }

    bool czyPoprawny() {
        return id > 0
            && !nazwa.empty()
            && cena >= 0
            && stanMagazynowy >= 0
            && !kategoria.empty();
    }

    void wyswietl() {
        cout
            << "ID: " << id
            << ", Nazwa: " << nazwa
            << ", Cena: " << cena << " zl"
            << ", Stan magazynowy: " << stanMagazynowy
            << ", Kategoria: " << kategoria
            << ", Opis: " << opis
            << endl;
    }

    
};