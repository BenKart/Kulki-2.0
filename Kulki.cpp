#include <iostream>
#include <string>
#include "Kulki.h"
#include "Terminalowy.h"

using namespace std;

bool Kulki::zacznijgre() {
	cout << "Witaj w grze Kulki!" << endl;
	utwurzgraczy();
	Plansza::polozenie a;
	Plansza::polozenie b;
	plan.ustaw();
	plan.rysuj();
	for (int i = 0; i < 70;i++) {
		while(true){
			a = jaki_ruch(A, Plansza::bialy);
			//a = komputer(A, Plansza::bialy, 0);
			if (plan.wstaw_pionek(a,Plansza::bialy))break;
			if(plan.mozna_wstawic(Plansza::bialy))cout << "PODAJ POPRAWNE WSPOLRZEDNE!" << endl;
			else {
				cout << "NIE MASZ RUCHU!" << endl;
				i--;
				if (!plan.mozna_wstawic(Plansza::czarny))i = 200;
				break;
			}
		}
		plan.rysuj();
		while(true){
			b = jaki_ruch(B, Plansza::czarny);
			//b = komputer(B, Plansza::czarny, 2);
			if (plan.wstaw_pionek(b, Plansza::czarny))break;
			if(plan.mozna_wstawic(Plansza::czarny))cout << "PODAJ POPRAWNE WSPOLRZEDNE!" << endl;
			else {
				cout << "NIE MASZ RUCHU!" << endl;
				i--;
				if (!plan.mozna_wstawic(Plansza::bialy))i = 200;
				break;
			}
		}
		plan.rysuj();
	}
	cout << "Biale: " << plan.ile(Plansza::bialy) << "! Czarne: " << plan.ile(Plansza::czarny) << "!" << endl;
	return true;
}

bool Kulki::utwurzgraczy() {
	int x, y;
	cout << "Jakich graczy wybierasz?" << endl << "Gracz Bia³y: 1 to Terminal, 2 to Komputer? ";
	cin >> x;
	if(x==1)A.typ = Terminal;
	else A.typ = KomputerTerminal;
	cout << "Gracz Czarny: 1 to Terminal, 2 to Komputer? ";
	cin >> y;
	if (y == 1)B.typ = Terminal;
	else B.typ = KomputerTerminal;
	string s;
	cout << "Podaj imie gracza nr 1: ";
	cin >> s;
	A.imie =s;
	cout << "Podaj imie gracza nr 2: ";
	cin >> s;
	B.imie =s;
	return true;
}

Plansza::polozenie Kulki::terminal(Gracz g) {
	Plansza::polozenie p;
	cout << g.imie << " Podaj wspolrzedne:" << endl << "x = ";
	char pom;
	while (true) {
		cin.clear();
		cin >> pom;
		p.x = (int)pom;
		if (p.x >= 'A'&&p.x <= 'L')break;
		cout << "PODAJ POPRAWNE DANE!" << endl;
	}
	cout << "y = ";
	while (true) {
		cin.clear();
		cin >> p.y;
		if (p.y >= 1 && p.y <= 12)break;
		cout << "PODAJ POPRAWNE DANE!" << endl;
	}
	p.x = p.x%'A' + 1;
	p.x -= 1;
	p.y -= 1;
	return p;
}

Plansza::polozenie Kulki::jaki_ruch(Gracz g, Plansza::pionek nowy) {
	switch (g.typ)
	{
	case Terminal:
		return terminal(g);
	case KomputerTerminal:
		return  komputer(g,nowy,2);
	}
}

Plansza::polozenie Kulki::komputer(Gracz g,Plansza::pionek nowy, int k = 0) {
	Plansza::polozenie p = { 0,0 };
	int Max = 0;
	int pom;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (plan.czy_wlasciwepole({ i,j }, nowy)) {
				pom = komputer_punkt({ i,j }, nowy, plan, k);
				if (pom >= Max) {
					Max = pom;
					p = { i,j };
				}
			}
		}
	}
	return p;
}


int Kulki::komputer_punkt(Plansza::polozenie p, Plansza::pionek nowy,Plansza podstawa, int k = 0) {
	podstawa.wstaw_pionek(p, nowy);
	if (k == 0) {
		return podstawa.ile(nowy);
	}
	else {
		int Max = 0;
		int pom;
		for (int n = 0; n < 12; n++) {
			for (int l = 0; l < 12; l++) {
				if (podstawa.czy_wlasciwepole({ n,l }, podstawa.odwrotny(nowy))) {
					pom = komputer_punkt({ n,l }, podstawa.odwrotny(nowy), podstawa, 0);
					if (pom > Max) {
						Max = pom;
						p = { n,l };
					}
				}
			}
		}
		podstawa.wstaw_pionek(p, podstawa.odwrotny(nowy));
		Max = 0;
		for (int n = 0; n < 12; n++) {
			for (int l = 0; l < 12; l++) {
				if (podstawa.czy_wlasciwepole({ n,l }, nowy)) {
					pom = komputer_punkt({ n,l }, nowy, podstawa, k-1);
					if (pom > Max) Max=pom;
				}
			}
		}
		return Max;
	}
}