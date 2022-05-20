#include "SH.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

void SH::cls()			//	Metoda, kt�ra "czy�ci" ekran.
{
	system("CLS");
}

						//	Metoda oczekuj�ca klawisza z klawiatury.
void SH::done()			//	G��wnie wykorzystywana do "pokazania", �e operacja zosta�a wykonana.
{
	cout << "Operacja wykonana.\n"
		"Nacisnij Enter, zeby kontynuwac...\n";
	getchar();
	getchar();
	system("CLS");
}

void SH::noOption()		//	Metoda m�wi�ca u�ytkownikowi, �e wybra� nieistniej�c� opcj�.
{
	cout << "Nie ma takiej opcji...\n"
		"Prosze wybrac cos innego...\n";
	getchar();
	getchar();
}

void SH::opened()		//	Metoda daj�ca komunikat, �e plik zosta� otwarty poy�lnie.
{
	cout << "Plik pomyslnie otwarto...\n";
	getchar();
	getchar();
}

void SH::noFile()		//	Metoda daj�ca komunikat, �e plik nie zosta� otwarty poy�lnie.
{
	cout << "Nie udalo sie otworzyc pliku...\n";
	getchar();
	getchar();
	system("CLS");
}