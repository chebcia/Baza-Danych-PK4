#include "Pracownik.h"

class Admin : public Pracownik {

public:
	 Admin();
	 void menu();


private:

	 void dodajUzytkownika();
	 void dodawaniedopliku(string login, string haslo, string rola);
	 void usunUzytkownika2(string login);
	 void usunUzytkownika();



};
