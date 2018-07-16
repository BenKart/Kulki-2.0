#pragma once
#include <iostream>

class Plansza {
public:
	Plansza();
	Plansza(Plansza&);
	enum pionek {
		bialy = 1,
		czarny = 2,
		brak = 0,
	}; 

	struct polozenie{
		int x;
		int y;
	};

	void rysuj();
	
	bool wstaw_pionek(polozenie, pionek);

	void ustaw();
	
	bool mozna_wstawic(pionek);
	bool czyzajety(polozenie);
	pionek colezy(polozenie);
	bool czy_wlasciwepole(polozenie p, pionek nowy);
	bool poprawna_sciezka(int, int, polozenie,pionek);
	pionek odwrotny(pionek);
	int ile(pionek);
	~Plansza();

private:
	bool poloz(polozenie, pionek);
	pionek** tabela;
};