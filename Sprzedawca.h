#pragma once
#include "Pracownik.h"

class Sprzedawca : public Pracownik
{
public:
    static void znajdzlekarstwa();
    static void znajdzlek(const string& name, const string& type);
    static void sprzedajLek(const string& name, const string& type);
    static void znajdzZamiennik(const string& sickness);
};
