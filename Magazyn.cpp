#include "Magazyn.h"
#include <QInputDialog>

using namespace std;

Lek* Magazyn::znajdzlek(string nazwaleku, string nazwarodzaju) //parametr metody z klasy lek
{
	fstream plik;
	// sprawdzenie fragmentu instrukcją try
	try
	{
		plik.open(nazwarodzaju + ".txt", std::ios::in);
        if (!plik.good())
            throw "Nie istnieje taki rodzaj leku";
		while (!plik.eof())
		{
			string napis;

			string nazwazpliku;
			bool refundacja;
			double cena;
			int ograniczenia;
			int iloscsztuk;
			string numerserii;
			getline(plik, napis, '\n');
			if (napis.compare("") != 0)
			{
				stringstream ss(napis);
				ss >> nazwazpliku >> refundacja >> cena >> ograniczenia >> iloscsztuk >> numerserii;
				if (nazwazpliku == nazwaleku)
				{
                    plik.close();
                    return new Lek(nazwaleku, cena, refundacja, ograniczenia, numerserii, iloscsztuk);
				}
            }
            else
                plik.close();
        }
	}
	// złapanie wyjątku w przypadku niepowodzenia dostępu do pliku
	catch (const std::exception &e )
	{
        plik.close();
        QMessageBox::critical(nullptr, "BazyDancyh", e.what());
	}
    return nullptr;
}

Listalekow * Magazyn::znajdzLeki()
{
	return zarzadzanieLekami.znajdzLekarstwa();
}

void Magazyn::dodajlek(string nazwaleku, string nazwarodzaju)
{
	Lek *lek = znajdzlek(nazwaleku, nazwarodzaju);

	if (lek != nullptr)
	{
        delete lek;
        QMessageBox::warning(nullptr, "BazyDanych", "Istnieje juz taki lek");
	}
	else
	{
        bool refundacja;
		// sprawdznie fragmentu kodu podejrzanego o wyjątek 
		ofstream plik;
		ofstream zamienniki;
		// jeżeli otwarcie pliku by się nie powiodło rzucany jest wyjątek który łapie instrukcja catch
		// jeżeli do jakiegoś obiektu nie można było by się odwołać to rzucany jest wyjątek exception

        double cena = QInputDialog::getDouble(nullptr, "BazyDanych", "Podaj cene");
        int ograniczenia = QInputDialog::getInt(nullptr, "BazyDanych", "Podaj ograniczenia");
        int iloscsztuk = QInputDialog::getInt(nullptr, "BazyDanych", "Podaj ilosc");
        string numerserii = QInputDialog::getText(nullptr, "BazyDanych", "Podaj numer serii").toStdString();
        if (QInputDialog::getText(nullptr, "BazyDanych", "Czy jest refundacja? (tak/nie)").toStdString().compare("tak") == 0)
            refundacja = true;
        else
            refundacja = false;

		try
		{
			plik.open(nazwarodzaju + ".txt", ios::out | ios::app);
			plik << nazwaleku << " " << refundacja << " " << cena << " " << ograniczenia << " " << iloscsztuk << " " << numerserii << "\n";
			plik.close(); //obowiązkowo należy zamknąć plik

		}
		catch (const exception &e)
		{
            QMessageBox::critical(nullptr, "BazyDancyh", (string("cos poszlo nie tak przy otwieraniu pliku!\n") + e.what()).c_str());
		}
        try
        {
			zamienniki.open("zamienniki.txt", ios::out | ios::app);
            string choroba = "";
            zamienniki << nazwaleku + " ";
			while (choroba != "0") {
				if (choroba == "0") {
					zamienniki << '\n';
				}
                choroba = QInputDialog::getText(nullptr, "BazyDanych",
                                                "Wpisz choroby dla ktorych twoj lek jest zamiennikiem jezeli chcesz przestac wpisz 0").toStdString();
				zamienniki << choroba + " ";
			}
			zamienniki << "\n";
			zamienniki.close();
		}
		// złpanie wyjątku
		catch (const exception &e)
		{
            zamienniki.close();
            QMessageBox::critical(nullptr, "BazyDancyh", (string("cos poszlo nie tak przy otwieraniu pliku zamienniki.txt!\n") + e.what()).c_str());
		}		
	}
 }

void Magazyn::znajdzzamiennik(string choroba)
{
	fstream plik;
    try
    {
		plik.open("zamienniki.txt", std::ios::in);

		while (!plik.eof())
		{
			string napis;
            string nazwazpliku;
			getline(plik, napis, '\n');
			char * schowek;
			char* skonwertowany = new char[napis.length() + 1];
			strcpy(skonwertowany, napis.c_str());
			schowek = strtok(skonwertowany, " ");
			if (napis.compare("") != 0)
			{
                nazwazpliku = schowek;
                while (schowek != NULL)
                {
                    if (schowek == choroba)
                        QMessageBox::information(nullptr, "BazyDancyh",
                                                 (string("lekiem dzialajacym na te chorobe jest:") + nazwazpliku).c_str());
					schowek = strtok(NULL, " ");
				}
			}
		}
		plik.close();
	}
	catch (std::exception &e)
    {
        plik.close();
        QMessageBox::critical(nullptr, "BazyDancyh", (string("Dostep do pliku zostal zabroniony!\n") + e.what()).c_str());
	}
}

void Magazyn::usunlekzzamiennikow(string nazwaleku)
{
	fstream plik;
	// sprawdzenie kodu podejrzanego o wyjątek
	try
	{
        plik.open("zamienniki.txt", std::ios::in);
		string linia;
		string nazwalekuzpliku;
		vector<string> liniezpliku;
        while (getline(plik, linia))
        {
			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			schowek = strtok(skonwertowany, " ");

			if (linia.compare("") != 0)
			{
				nazwalekuzpliku = schowek;
                if (nazwaleku != nazwalekuzpliku)
                    liniezpliku.push_back(linia);
			}
            delete[] skonwertowany;
		}
		plik.close();
		plik.open("zamienniki.txt", std::ofstream::out | std::ofstream::trunc);
		if (plik.good()) 
		{
			std::vector<string>::iterator cell = liniezpliku.begin();
            for (; cell!= liniezpliku.end(); cell++)
                plik << *cell;
		}
		plik.close();
	}
	// złapanie wyjątku 
	catch (std::exception &e)
    {
        plik.close();
        QMessageBox::critical(nullptr, "BazyDancyh", (string("Dostep do pliku zostal zabroniony!\n") + e.what()).c_str());
	}
}

void Magazyn::zmniejszilosclekowojeden(string nazwaleku, string nazwarodzaju)
{
	fstream plik;
	try
	{
        plik.open(nazwarodzaju + ".txt", std::ios::in);
		bool znaleziono = false;
		string linia;
		string nazwalekuzpliku;
		bool refundacja;
		double cena;
		int ograniczenia;
		string numerserii;
		int iloscsztuk;
		Listalekow* lista = NULL;

        while (getline(plik, linia))
        {
			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			schowek = strtok(skonwertowany, " ");
            if (schowek != NULL)
            {
				nazwalekuzpliku = schowek;
				schowek = strtok(NULL, " ");
				refundacja = schowek;
				schowek = strtok(NULL, " ");
				cena = stoi(schowek);
				schowek = strtok(NULL, " ");
				ograniczenia = stoi(schowek);
				schowek = strtok(NULL, " ");
				iloscsztuk = stoi(schowek);
				schowek = strtok(NULL, " ");
				numerserii = schowek;

				if (nazwaleku.compare( nazwalekuzpliku)==0) {
					znaleziono = true;
                    if (iloscsztuk <= 0)
                        QMessageBox::warning(nullptr, "BazyDancyh", (string("za malo leku: ") + nazwaleku +
                                                                     string(" w bazie aby sprzedac, skontaktuj sie z managerem")).c_str());
                    else
                    {
                        iloscsztuk--;
                        QMessageBox::information(nullptr, "BazyDancyh", (string("sprzedano lek: ") + nazwaleku + string(" pozostalo jeszcze: ") +
                                                                         to_string(iloscsztuk) + string(" w bazie")).c_str());
					}
				}
				Lek* lek = new Lek(nazwalekuzpliku, refundacja, cena, ograniczenia,numerserii, iloscsztuk);
				lista->dodajlekdolisty(lek, lista);
			}

            delete[] skonwertowany;
		}
        if (znaleziono == false)
            QMessageBox::warning(nullptr, "BazyDancyh", "Nie znaleziono podanego leku w bazie sprobuj ponownie dla innego rodzaju");
		plik.close();
		wypiszlistedopliku(nazwarodzaju, lista);
	}
	catch (std::exception &e)
    {
		plik.close();
        QMessageBox::critical(nullptr, "BazyDancyh", (string("Dostep do bazy zabroniony\n") + e.what()).c_str());
    }
}

void Magazyn::uzupelnijlek(string nazwaleku, string nazwarodzaju, int nowailosc)
{
	fstream plik;
	try
	{
	plik.open(nazwarodzaju + ".txt", std::ios::in);

		string linia;
		string nazwalekuzpliku;
		bool refundacja;
		double cena;
		int ograniczenia;
		int iloscsztuk;
		string numerserii;
		Listalekow* lista = NULL;

        while (getline(plik, linia))
        {
			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			schowek = strtok(skonwertowany, " ");
            if (schowek != NULL)
            {
				nazwalekuzpliku = schowek;
				schowek = strtok(NULL, " ");
				refundacja = schowek;
				schowek = strtok(NULL, " ");
				cena = stoi(schowek);
				schowek = strtok(NULL, " ");
				ograniczenia = stoi(schowek);
				schowek = strtok(NULL, " ");
				iloscsztuk = stoi(schowek);
				schowek = strtok(NULL, " ");
				numerserii = schowek;

                if (nazwaleku.compare(nazwalekuzpliku) == 0)
                    iloscsztuk = nowailosc;
				Lek* lek = new Lek(nazwalekuzpliku, refundacja, cena, ograniczenia, numerserii, iloscsztuk);
				lista->dodajlekdolisty(lek, lista);
			}
            delete[] skonwertowany;
		}
		plik.close();
		wypiszlistedopliku(nazwarodzaju, lista);
	}
	catch (exception & e)
	{
        plik.close();
        QMessageBox::critical(nullptr, "BazyDancyh", (string("cos poszlo nie tak przy otwieraniu pliku!\n") + e.what()).c_str());
	}
}

void Magazyn::wypiszlistedopliku(string nazwarodzaju, Listalekow* lista) //metoda ktora sobie bierze listelekow a lista lekow to obiekt co nie?
{
	fstream plik;
	// sprawdź fragment kodu podejrzany o rzucenie wyjątku
	try
	{
		plik.open(nazwarodzaju + ".txt", std::ofstream::out | std::ofstream::trunc);
		Listalekow* przechowywatorglowy = lista;
		while (przechowywatorglowy)
		{
			plik << przechowywatorglowy->lek->getNazwaleku() << " " << przechowywatorglowy->lek->getRefundacja() <<
                " " << przechowywatorglowy->lek->getCena() << " " << przechowywatorglowy->lek->getOgraniczenia() <<
                " " << przechowywatorglowy->lek->getIloscsztuk() <<" "<< przechowywatorglowy->lek->getNumerserii() << '\n';

			przechowywatorglowy = przechowywatorglowy->pNext;
		}

		Listalekow::wyczyscliste(lista);
		plik.close();
	}
	// złapanie wyjątku
	catch (const exception &e)
    {
		plik.close();
        QMessageBox::critical(nullptr, "BazyDancyh", (string("Dostep do bazy zabroniony\n") + e.what()).c_str());
	}
}
