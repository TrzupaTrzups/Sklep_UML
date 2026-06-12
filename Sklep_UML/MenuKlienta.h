#pragma once

#include "Klient.h"
#include "MenuGoscia.h"
#include "SerwisProduktow.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class MenuKlienta : public MenuGoscia {
private:
    Klient& klient;
    SerwisProduktow& serwisProduktow;

public:
    MenuKlienta(Klient& klient, SerwisProduktow& serwisProduktow)
        : MenuGoscia(klient, serwisProduktow),
          klient(klient),
          serwisProduktow(serwisProduktow) {
    }

};
