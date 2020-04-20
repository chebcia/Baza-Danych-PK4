#include "Sprzedawca.h"

Sprzedawca::Sprzedawca()
{
	this->rola = "sprzedawca";
}

void Sprzedawca::znajdzlekarstwa()
{
	Magazyn magazyn = Magazyn();
	Listalekow *znalezioneLekarstwa = magazyn.znajdzLeki();
	if (znalezioneLekarstwa != NULL)
	{
		Listalekow * nowyPhead = znalezioneLekarstwa;
		while (nowyPhead!= NULL)
		{

			Lek *znalezionylek = nowyPhead->lek;
			cout << "Nazwa leku to: " << znalezionylek->getNazwaleku() << endl;
			cout << "Ograniczenia znalezionego leku to: " << znalezionylek->getOgraniczenia() << "lat" << endl;
			cout << "Cena znalezionego leku to: " << znalezionylek->getCena() << "PLN" << endl;
			cout << "Refundacja leku: " << znalezionylek->getRefundacja()  << endl;
			cout << "Ilosc sztuk znalezionego leku to: " << znalezionylek->getIloscsztuk() << endl;
			cout << "Numer serii znalezionego leku to: " << znalezionylek->getNumerserii() << endl<<endl;
			nowyPhead = nowyPhead->pNext;
		}

	}
	else
	{
		cout << "Nie znaleziono lekarstw" << endl;
	}

}

void Sprzedawca::znajdzlek()
{
	Lek lek = podajNazweIRodzaj();
	Magazyn magazyn = Magazyn();
	Lek * znalezionylek = magazyn.znajdzlek(lek.getNazwaleku(), lek.getRodzajleku());
	if (znalezionylek != nullptr)
	{
		cout << "Ograniczenia znalezionego leku to: " << znalezionylek->getOgraniczenia() << "lat" << endl;
		cout << "Cena znalezionego leku to: " << znalezionylek->getCena() << "PLN"  << endl;
		cout << "Refundacja leku: " << znalezionylek->getRefundacja() << endl;
		cout << "Ilosc sztuk znalezionego leku to: " << znalezionylek->getIloscsztuk() << endl;
		cout << "Numer serii znalezionego leku to: " << znalezionylek->getNumerserii() << endl;
	
	}
	else
	{

	}

}

void Sprzedawca::menu()
{

	int opcja = 1;
	while (opcja != 0)
	{
		cout << "1.Sprzedaj lek" << endl;
		cout << "2.Znajdz zamiennik" << endl;
		cout << "3.Znajdz lek" << endl;
		cout << "4.Znajdz lekarstwa" << endl;
		cout << "0.Wyjdz" << endl;

		cin >> opcja;

		switch (opcja)
		{
		case 1:
			sprzedajLek();
			break;
		case 2:
			znajdzZamiennik();
			break;
		case 3:
			znajdzlek();
			break;
		case 4:
			znajdzlekarstwa();
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Bledna opcja";
		}
	}
}

void Sprzedawca::sprzedajLek()
{
	Lek lek = podajNazweIRodzaj();
	Magazyn magazyn = Magazyn();

	magazyn.zmniejszilosclekowojeden(lek.getNazwaleku(), lek.getRodzajleku());


}

void Sprzedawca::znajdzZamiennik()
{
	Lek lek = Lek();
	Magazyn magazyn = Magazyn();
	string choroba;
	cout << "Podaj chorobe dla ktorej szukasz lekow " << endl;
	cin >> choroba;
	magazyn.znajdzzamiennik(choroba);
}
