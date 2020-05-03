#include "Manager.h"

void Manager::dodajLek(const string& name, const string& type)
{
	Magazyn magazyn = Magazyn();
    magazyn.dodajlek(name, type);
}

void Manager::usunLek(const string& name, const string& type)
{
	Magazyn magazyn = Magazyn();
    magazyn.usunlek<string>(name, type);
}

void Manager::uzupelnijLek(const string& name, const string& type, int count)
{
    Magazyn magazyn = Magazyn();
    magazyn.uzupelnijlek(name, type, count);
}
