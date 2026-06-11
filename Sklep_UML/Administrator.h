#include "Gosc.h"

using namespace std;

class Administrator : public Gosc {
    private:
    int id;
    string login;
    string haslo;
    SerwisProduktow& serwisProduktow;
    
    public:
    Administrator(int id, string& login, string& hasło, SerwisProduktow& serwisProduktow) 
    : Gosc(serwisProduktow), 
    id(id), login(login), 
    haslo(hasło) 
    {

    }

    int pobierzId() const {
        return id;
    }
    string pobierzLogin() const {
        return login;
    }
    string pobierzHaslo() const {
        return haslo;


}