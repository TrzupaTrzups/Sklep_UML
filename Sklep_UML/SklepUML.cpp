#include <iostream>

#include "SerwisProduktow.h"
#include "Gosc.h"
#include "MenuKlienta.h"
#include "Klient.h"
#include "MenuGoscia.h"
#include "Administrator.h"
#include "MenuAdministartora.h"

using namespace std;

void ekranLogowania(Klient k, MenuGoscia& mg, MenuKlienta& mk, Administrator& administrator, MenuAdministrator& menuAdministrator) {
    cout << "=== EKRAN LOGOWANIA ===" << endl;
    cout << "1. Zaloguj sie jako klient" << endl;
    cout << "2. Kontynuuj jako gosc" << endl;
    cout << "3. Zaloguj sie jako administrator" << endl;
    cout << "0. Wyjdz" << endl;
    cout << endl;

    int wybor = mg.wczytajLiczbeCalkowita("Wybierz opcje: ");

    if(wybor == 1) {
        string login = mg.wczytajTekst("Podaj login: ");
        string haslo = mg.wczytajTekst("Podaj haslo: ");

        if (k.zaloguj(k, login, haslo)) {
            cout << "Zalogowano pomyslnie!" << endl;
            mk.uruchom();
        } else {
            cout << "Niepoprawny login lub haslo. Kontynuowanie jako gosc." << endl;
            mg.uruchom();
        }
    } else if(wybor == 2) {
        mg.uruchom();
    } else if(wybor == 3) {
        string login = mg.wczytajTekst("Podaj login: ");
        string haslo = mg.wczytajTekst("Podaj haslo: ");

        if (login == "admin" && haslo == "admin") {
            cout << "Zalogowano pomyslnie!" << endl;
            menuAdministrator.uruchom();
        } else {
            cout << "Niepoprawny login lub haslo. Kontynuowanie jako gosc." << endl;
            mg.uruchom();
        }
    }
}

int main() {
    string sciezkaDoPliku = "produkty.txt";
    SerwisProduktow serwisProduktow(sciezkaDoPliku);

    Gosc gosc(serwisProduktow);
    Klient klient(1, "Grzybeusz Smierdziuszko", "grzyby", serwisProduktow);
    Administrator administrator(1, "admin", "admin", serwisProduktow);

    MenuGoscia menuGoscia(gosc, serwisProduktow);
    MenuKlienta menuKlienta(klient, serwisProduktow);
    MenuAdministrator menuAdministrator(administrator, serwisProduktow);
    
    ekranLogowania(klient, menuGoscia, menuKlienta, administrator, menuAdministrator);

    cout << "Koniec programu." << endl;

    return 0;
}