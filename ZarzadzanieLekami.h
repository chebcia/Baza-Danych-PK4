#pragma once
#include "ListaLekow.h"
#include <string>
#include <iostream>
class ZarzadzanieLekami {

public:
	Listalekow* znajdzLekarstwa(Lek lekarstwo, bool czySzukacPoRefundacji)
	{
		string nazwaKategorii;
		cout << "podaj kategorie leku (nic by nie korzystac z pola): ";
		getline(cin, nazwaKategorii);
		vector<string> listaKategorii;
		Listalekow* listaZnalezionychLekow = NULL;

		if (nazwaKategorii.compare("") != 0)
		{
			listaKategorii.push_back(nazwaKategorii);
		}
		else

		{
			fstream plik;
			// sprawdzenie fragmentu instrukcją try
			try
			{
				plik.open("Kategorie.txt", std::ios::in);
				if (!plik.good())
				{
					throw std::exception("Nie ");
				}
				while (!plik.eof())
				{
					string napis;


					getline(plik, napis);
					listaKategorii.push_back(napis);

				}
			}
			catch (const std::exception &e)
			{
				std::cout << std::endl << e.what() << std::endl;
				plik.close();
			}
		}



		std::vector<std::thread> watki(listaKategorii.size());
		for (int a = 0; a < listaKategorii.size(); a++)
		{
			string tmp = listaKategorii[a];
			watki[a] = std::thread(szukajPoKategorii, lekarstwo, tmp, std::ref(listaZnalezionychLekow), czySzukacPoRefundacji);
		}
		for (int a = 0; a < listaKategorii.size(); ++a)
		{
			watki[a].join();
		}
		return listaZnalezionychLekow;
	}
	Listalekow* znajdzLekarstwa();


};
