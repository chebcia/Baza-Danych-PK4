#pragma once
#include "ListaLekow.h"
#include <string>

class ZarzadzanieLekami
{
public:
	Listalekow* znajdzLekarstwa(Lek lekarstwo, bool czySzukacPoRefundacji);
	Listalekow* znajdzLekarstwa();
};
