#include "SH.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

void SH::cls()			//	Metoda, która "czyœci" ekran.
{
	system("CLS");
}

						//	Metoda oczekuj¹ca klawisza z klawiatury.
void SH::done()			//	G³ównie wykorzystywana do "pokazania", ¿e operacja zosta³a wykonana.
{
	cout << "Operacja wykonana.\n"
		"Nacisnij Enter, zeby kontynuwac...\n";
	getchar();
	getchar();
	system("CLS");
}

void SH::noOption()		//	Metoda mówi¹ca u¿ytkownikowi, ¿e wybra³ nieistniej¹c¹ opcjê.
{
	cout << "Nie ma takiej opcji...\n"
		"Prosze wybrac cos innego...\n";
	getchar();
	getchar();
}

void SH::opened()		//	Metoda daj¹ca komunikat, ¿e plik zosta³ otwarty poyœlnie.
{
	cout << "Plik pomyslnie otwarto...\n";
	getchar();
	getchar();
}

void SH::noFile()		//	Metoda daj¹ca komunikat, ¿e plik nie zosta³ otwarty poyœlnie.
{
	cout << "Nie udalo sie otworzyc pliku...\n";
	getchar();
	getchar();
	system("CLS");
}