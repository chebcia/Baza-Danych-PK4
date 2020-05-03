#include "Sprzedawca.h"
#include <QMessageBox>

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
            QMessageBox::information(nullptr, "BazyDanych", (string("Nazwa: ") + znalezionylek->getNazwaleku() +
                                     string("\nOgraniczenia: ") + to_string(znalezionylek->getOgraniczenia()) +
                                     string("\nCena: ") + to_string(znalezionylek->getCena()) +
                                     string("PLN\nRefundacja: ") + string(znalezionylek->getRefundacja() ? "Tak" : "Nie") +
                                     string("\nIlosc: ") + to_string(znalezionylek->getIloscsztuk()) +
                                     string("\nSeria: ") + znalezionylek->getNumerserii()).c_str());
			nowyPhead = nowyPhead->pNext;
		}
	}
    else
        QMessageBox::warning(nullptr, "BazyDanych", "Nie znaleziono lekarstw");
}

void Sprzedawca::znajdzlek(const string& name, const string& type)
{
	Magazyn magazyn = Magazyn();
    Lek * znalezionylek = magazyn.znajdzlek(name, type);
	if (znalezionylek != nullptr)
	{
        QMessageBox::information(nullptr, "BazyDanych", (string("Ograniczenia: ") + to_string(znalezionylek->getOgraniczenia()) +
                                 string("\nCena: ") + to_string(znalezionylek->getCena()) +
                                 string("PLN\nRefundacja: ") + string(znalezionylek->getRefundacja() ? "Tak" : "Nie") +
                                 string("\nIlosc: ") + to_string(znalezionylek->getIloscsztuk()) +
                                 string("\nSeria: ") + znalezionylek->getNumerserii()).c_str());
    }
}

void Sprzedawca::sprzedajLek(const string& name, const string& type)
{
	Magazyn magazyn = Magazyn();
    magazyn.zmniejszilosclekowojeden(name, type);
}

void Sprzedawca::znajdzZamiennik(const string& sickness)
{
    Magazyn magazyn = Magazyn();
    magazyn.znajdzzamiennik(sickness);
}
