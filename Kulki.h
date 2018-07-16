#pragma once
#include <string>
#include "Plansza.h"
using namespace std;

class Kulki {
public:
	Kulki() {};
	bool zacznijgre();
private:
	enum Typ_Gracza {
		Terminal = 1,
		KomputerTerminal = 2,
	};
	struct Gracz
	{
		Typ_Gracza typ;
		string imie;
	};
	Plansza plan;
	Gracz A;
	Gracz B;
	bool utwurzgraczy();
	Plansza::polozenie jaki_ruch(Gracz, Plansza::pionek);
	Plansza::polozenie terminal(Gracz);
	Plansza::polozenie komputer(Gracz, Plansza::pionek, int);
	int komputer_punkt(Plansza::polozenie,Plansza::pionek,Plansza, int);
};
