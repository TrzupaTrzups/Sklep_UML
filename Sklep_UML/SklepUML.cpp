#include <iostream>

#include "SerwisProduktow.h"
#include "Gosc.h"
#include "MenuGoscia.h"

using std::cout;
using std::endl;

int main() {
    string sciezkaDoPliku = "produkty.txt";
    SerwisProduktow serwisProduktow(sciezkaDoPliku);

    Gosc gosc(serwisProduktow);

    MenuGoscia menuGoscia(gosc, serwisProduktow);
    menuGoscia.uruchom();

    cout << "Koniec programu." << endl;

    return 0;
}