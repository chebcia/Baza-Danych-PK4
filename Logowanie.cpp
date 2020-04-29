#include "Logowanie.h"
#include <QMessageBox>

bool Logowanie::sprawdzDane(string login, string haslo)
{
	std::regex wyrazenieDuzaLitera{ "[A-Z]+" }; //znajdz dużą litere
	std::regex wyrazenieMalaLitera{ "[a-z]+" }; //znadz mała liere
	std::regex wyrazenieCyfra{ "[0-9]+" }; //znajdz cyfre
	std::regex wyrazenieZnakSpecjalny{ "[@!?.]+" };// znadz znak
	bool duzaLitera = false; 
	bool malaLitera = false; 
	bool cyfra = false; 
	bool znakSpecjalny = false;
	duzaLitera = std::regex_search(login, wyrazenieDuzaLitera);
	malaLitera = std::regex_search(login, wyrazenieMalaLitera);
	cyfra = std::regex_search(login, wyrazenieCyfra);
	//sprawdz login
    if (malaLitera&&cyfra)
	{
		duzaLitera = std::regex_search(haslo, wyrazenieDuzaLitera);
		malaLitera = std::regex_search(haslo, wyrazenieMalaLitera);
		cyfra = std::regex_search(haslo, wyrazenieCyfra);
		znakSpecjalny = std::regex_search(haslo, wyrazenieZnakSpecjalny);
        if (duzaLitera&&malaLitera&&cyfra&&znakSpecjalny)
            return true;
    }
    return false;
}

string Logowanie::zalogujSie(string login, string haslo)
{
	fstream plik;
	try
	{
		plik.open("hasla.txt", std::ios::in);
		while (!plik.eof())
		{
			string linia;
			string rola;
			getline(plik, linia, '\n');

			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
            if (strlen(skonwertowany) == 0)
                break;
			string id = strtok(skonwertowany, " ");
			string loginzPliku = strtok(NULL, " ");
			string haslozPliku = strtok(NULL, " ");
            if (login == loginzPliku && haslo == haslozPliku)
            {
				plik.close();
				return strtok(NULL, " ");
			}
            else if (login == loginzPliku && haslo != haslozPliku)
            {
                plik.close();
                QMessageBox::critical(nullptr, "BazyDanych", "Podano bledne haslo aplikacja zostanie wylaczona!");
                exit(-1);
			}
		}
    }
    catch (exception e)
    {
        QMessageBox::critical(nullptr, "BazyDanych", e.what());
    }
    plik.close();
    QMessageBox::critical(nullptr, "BazyDanych", "Nie znaleziono uzytkownika o podanym hasle, aplikacja zostanie wylaczona!");
    exit(-1);
    return "";
}
