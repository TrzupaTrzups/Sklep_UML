#pragma once

#include <iostream>
#include <string>

using namespace std;

// Uruchamia pojedynczy test, wypisuje jego nazwe i zwieksza licznik zaliczonych testow.
void uruchomTest(
    const string& nazwa,
    void (*funkcjaTestowa)(),
    int& liczbaZaliczonych
) {
    cout << "[TEST] " << nazwa << "... ";

    funkcjaTestowa();

    liczbaZaliczonych++;
    cout << "OK" << endl;
}
