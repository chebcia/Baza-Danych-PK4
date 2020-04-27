#include "Admin.h"
#include <QMessageBox>

void Admin::dodawaniedopliku(string login, string haslo, string rola)
{
	int id = 1;
	string linia;
	ifstream plik1("hasla.txt");

	if (plik1)
    {
        while (getline(plik1, linia))
        {
            if (atoi(linia.c_str()) > id)
                id = atoi(linia.c_str());
        }
		plik1.close();
	}
	id++;
	ofstream plik("hasla.txt", ios::out | ios::app);
	try
	{
		plik << id << " " << login << " " << haslo << " " << rola << '\n';
        plik.close(); //obowiązkowo należy zamknąć plik
	}
	catch (exception e)
	{
        plik.close();
        QMessageBox::critical(nullptr, "BazyDanych", (string("Blad podczas dostepu do bazy uzytkownikow\n") + string(e.what())).c_str());
	}
}

void Admin::usunUzytkownika(string login)
{
	fstream plik("hasla.txt", std::ios::in);
	try
	{
		string linia;
		string loginzpliku;
		// użycie vectora jako kontenera stl
		std::vector<string> liniezpliku;
        while (getline(plik, linia))
        {
			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			schowek = strtok(skonwertowany, " ");

			//druga kolumna, login
			schowek = strtok(NULL, " ");
			loginzpliku = schowek;

            if (login != loginzpliku)
                liniezpliku.push_back(linia + "\n");
            delete[] skonwertowany;
		}
		plik.close();
		plik.open("hasla.txt", std::ofstream::out | std::ofstream::trunc);
        if (plik.good())
        {
			// iterator stl 
			std::vector<string>::iterator cell = liniezpliku.begin();
            for (; cell != liniezpliku.end(); cell++)
                plik << *cell;
		}
		plik.close();
	}
	catch (exception e)
    {
        plik.close();
        QMessageBox::critical(nullptr, "BazyDanych", (string("Blad podczas dostepu do bazy uzytkownikow\n") + string(e.what())).c_str());
	}
}
