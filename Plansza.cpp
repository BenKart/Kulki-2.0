#include <iostream>
#include "Plansza.h"

using namespace std;

	Plansza::Plansza() {
		tabela = new pionek*[12];
		for (int i = 0; i < 12; i++) {
			tabela[i] = new pionek[12];
			for (int j = 0; j < 12; j++) {
				tabela[i][j] = brak;
			}
		}
	}
	Plansza::Plansza(Plansza & p)
	{
		tabela = new pionek*[12];
		for (int i = 0; i < 12; i++) {
			tabela[i] = new pionek[12];
			for (int j = 0; j < 12; j++) {
				tabela[i][j] = p.colezy({i,j});
			}
		}
	}
	Plansza::~Plansza() {
		for (int j = 0; j < 12; j++) {
			delete tabela[j];
		}
		delete tabela;
	}
	bool Plansza::czyzajety(polozenie p) {
		if (0 > p.x || p.x > 11 || 0 > p.y || p.y > 11)return false;
		if (tabela[p.x][p.y] == brak)return false;
		else return true;
	}
	bool Plansza::poloz(polozenie p,pionek nowy) {
		if (0 > p.x || p.x > 11 || 0 > p.y || p.y > 11)return false;
		//if (czyzajety(p))return false;
		else tabela[p.x][p.y] = nowy;
		return true;
	}
	Plansza::pionek Plansza::colezy(polozenie p) {
		if (0 > p.x || p.x > 11 || 0 > p.y || p.y > 11)return brak;
		return tabela[p.x][p.y];
	}

	void Plansza::rysuj() {
		cout << "00";
		for (int i = 0; i < 12; i++)cout << char('A'+i);
		cout << endl;
		for (int i = 0; i < 12; i++) {
			if (i < 9)cout << "0";
			cout << i+1;
			for (int j = 0; j < 12; j++) {
				switch (tabela[j][i])
				{
				case 0:
					cout << static_cast < char >(176);
					break;
				case 1:
					cout << "o";
					break;
				case 2:
					cout << "x";
					break;
				}
			}
			cout << endl;
		}
	}

	bool Plansza::czy_wlasciwepole(polozenie p, pionek nowy) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (poprawna_sciezka(i, j, p, nowy)) return true;
			}
		}
		return false;
	}

	bool Plansza::poprawna_sciezka(int i , int j, polozenie p, pionek nowy) {
		if (czyzajety(p)||i>1||i<-1||j>1||j<-1)return false;
		if (i == 0 && j == 0)return false;
		p.x = p.x + i;
		p.y = p.y + j;
		if (colezy(p) != odwrotny(nowy))return false;
		while (true)
		{
			p.x = p.x + i;
			p.y = p.y + j;
			if (colezy(p) == odwrotny(nowy))continue;
			if (colezy(p) == nowy)return true;
			else return false;
		}
	}

	Plansza::pionek Plansza::odwrotny(pionek nowy) {
		if (nowy == bialy)return czarny;
		else return bialy;
	}

	void Plansza::ustaw() {
		Plansza();
		poloz({ 5,5 }, pionek::bialy);
		poloz({ 6,6 }, pionek::bialy);
		poloz({ 5,6 }, pionek::czarny);
		poloz({ 6,5 }, pionek::czarny);
	}

	bool Plansza::wstaw_pionek(polozenie p, pionek nowy) {
		if (!czy_wlasciwepole(p, nowy)) return false;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (poprawna_sciezka(i, j, p, nowy)) {
					polozenie pk = p;
					pk.x = p.x + i;
					pk.y = p.y + j;
					do {
						poloz(pk, nowy);
						pk.x = pk.x + i;
						pk.y = pk.y + j;
					} while (colezy(pk) == odwrotny(nowy));
				}
			}
		}
		poloz(p, nowy); 
		return true;
	}

	int Plansza::ile(pionek pi) {
		int n = 0;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if (tabela[i][j] == pi)n++;
			}
		}
		return n;
	}

	bool Plansza::mozna_wstawic(pionek pi) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if (!czyzajety({i,j}) && czy_wlasciwepole({ i,j }, pi))return true;
			}
		}
		return false;
	}