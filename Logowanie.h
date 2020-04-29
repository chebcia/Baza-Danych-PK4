#pragma once
#include "Windows.h"
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;
class Logowanie
{
public:
    static bool sprawdzDane(string login, string haslo);
    static string zalogujSie(string login, string haslo);
};
