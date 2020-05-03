#pragma once
#include "Sprzedawca.h"

class Manager : public Sprzedawca
{
public:
    static void dodajLek(const string& name, const string& type);
    static void usunLek(const string& name, const string& type);
    static void uzupelnijLek(const string& name, const string& type, int count);
};
