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

public:
    Produkt(
        int id,
        const string& nazwa,
        double cena,
        int stanMagazynowy,
        const string& kategoria
    )
        : id(id),
        nazwa(nazwa),
        cena(cena),
        stanMagazynowy(stanMagazynowy),
        kategoria(kategoria) {
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

    void ustawNazwe(const string& nowaNazwa) {
        nazwa = nowaNazwa;
    }

    void ustawCene(double nowaCena) {
        cena = nowaCena;
    }

    void ustawStanMagazynowy(int nowyStanMagazynowy) {
        stanMagazynowy = nowyStanMagazynowy;
    }

    void ustawKategorie(const string& nowaKategoria) {
        kategoria = nowaKategoria;
    }

    bool czyPoprawny() const {
        return id > 0
            && !nazwa.empty()
            && cena >= 0
            && stanMagazynowy >= 0
            && !kategoria.empty();
    }

    void wyswietl() const {
        cout
            << "ID: " << id
            << ", Nazwa: " << nazwa
            << ", Cena: " << cena << " zl"
            << ", Stan magazynowy: " << stanMagazynowy
            << ", Kategoria: " << kategoria
            << endl;
    }
};