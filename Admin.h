#include "Pracownik.h"

class Admin : public Pracownik
{
public:
     static void dodawaniedopliku(string login, string haslo, string rola);
     static void usunUzytkownika(string login);
};
