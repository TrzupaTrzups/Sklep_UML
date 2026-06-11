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
        string& nazwa,
        double cena,
        int stanMagazynowy,
        string& kategoria
    )
        : id(id),
        nazwa(nazwa),
        cena(cena),
        stanMagazynowy(stanMagazynowy),
        kategoria(kategoria) {
    }

    int pobierzId() {
        return id;
    }

    string& pobierzNazwe() {
        return nazwa;
    }

    double pobierzCene() {
        return cena;
    }

    int pobierzStanMagazynowy() {
        return stanMagazynowy;
    }

    string& pobierzKategorie() {
        return kategoria;
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
            << endl;
    }
};