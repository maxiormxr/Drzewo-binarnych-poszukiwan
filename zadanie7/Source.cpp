#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

int max = 100000;
int i = 1;
int poszukiwany;
int ilosc;
int root;
int wybor;
int *rodzic;
int *klucz;
int *lewo;
int *prawo;
int *stosUsunietych;
int wskStosuUsunietych = 0;
bool stosUsunietychPusty = true;

void bst_inorder(int r)
{
	int *stos = new int[i + 1];
	int wsk_stosu = 0;
	int wskazywany = root;
	bool gotowe = 0;
	bool stos_pusty = true;

	while (gotowe ==0)
	{
		if (wskazywany > 0)
		{
			wsk_stosu++;
			stos[wsk_stosu] = wskazywany;
			wskazywany = lewo[wskazywany];
			if (stos_pusty == true) stos_pusty = false;
		}
		else
		{
			if (stos_pusty == false)
			{
				cout << klucz[stos[wsk_stosu]] << " ";
				wskazywany = prawo[stos[wsk_stosu]];
				wsk_stosu--;
				if (wsk_stosu == 0) stos_pusty = true;
			}
			else
				gotowe = 1;
		}
	}
	delete[] stos;
}

void bst_insert(int z) 
{
	int x = root;
	int y = NULL;
	int k = klucz[z];
	while (x != NULL)
	{
		y = x;
		if (k < klucz[y]) x = lewo[y];
		else 
			x = prawo[y];
	}
	rodzic[z] = y;
	if (y == NULL)
	{
		root = z;
	}
	else
	{
		if (k < klucz[y]) lewo[y] = z;
		else
			prawo[y] = z;
	}
};
int bst_member(int *w, int *s, int *l, int *p, int k)
{
	int x = root;
	while ((x != NULL) && (k != klucz[x]))
	{
		if (k < klucz[x]) x = lewo[x];
		else
			x = prawo[x];
	}
	return x;
};
int bst_max(int r) 
{
	if (i > 1 && r <= i && r >=0)
	{
		while (prawo[r] != NULL) r = prawo[r];
		return r;
	}
	else 
	{
		cout << "KLUCZ O TAKIM INDEKSIE NIE ISTNIEJE W DRZEWIE";
	}
};
int bst_min(int r) 
{
	if (i > 1 && r <= i && r >= 0)
	{
		while (lewo[r] != NULL) r = lewo[r];
		return r;
	}
	else 
	{
		cout << "KLUCZ O TAKIM INDEKSIE NIE ISTNIEJE W DRZEWIE";
	}
	
};
int bst_successor(int x)
{
	int y;
	if (x <= i-1 && x != 0)
	{
		if (prawo[x] != NULL) y = bst_min(prawo[x]);
		else
		{
			y = rodzic[x];
			while (y != NULL && x == prawo[y])
			{
				x = y;
				y = rodzic[x];
			}
		}
		return y;
	}
	else
	{
		cout << "KLUCZ O TAKIM INDEKSIE NIE ISTNIEJE W DRZEWIE";
		return -1;
	}
};
int bst_delete(int usuwany)
{
	int x, y; 

	if (lewo[usuwany] == NULL || prawo[usuwany] == NULL) y = usuwany; // jesli na lewo lub prawo od z nie ma nic, wtedy y = z;
	else y = bst_successor(usuwany); // y = nastepnik(z), w przeciwnym wypadku
	x = lewo[y]; // x = to co jest na lewo od y
	if (x == NULL) x = prawo[y]; 	// jesli na lewo nie ma nic, wtedy x = to co na prawo od y
	if (x != NULL) rodzic[x] = rodzic[y];//jesli x nie jest pusty (czyli istnieje mniejszy lub wiekszy element od y
	//wtedy rodzic x przyjmuje wartosc rodzica y
	if (rodzic[y] == NULL) root = x;// jesli rodzic y jest pusty, wtedy korzen przyjmuje wartosc x
	else
	{
		if (y == lewo[rodzic[y]]) lewo[rodzic[y]] = x;		// jesli y = to co jest na lewo od rodzica y, wtedy to co na lewo od rodzica y przyjmuje wartosc x
		else prawo[rodzic[y]] = x;		// w przeciwnym wypadku wartosc x zostaje przypisana do tego co na prawo od rodzica y
	}
	if (y != usuwany) 	// jesli y nie rowna sie z
	{
			// przypisujemy wartosc klucza y do klucza z
		klucz[usuwany] = klucz[y];
	}
	return y;	// zwracamy y, czyli rodzic (indeks w tablicy) do usunietego elementu
}
void menu()
{
	cout << "===========================" << endl;
	cout << "DRZEWO BINARNYCH POSZUKIWAN" << endl;
	cout << "===========================" << endl;
	cout << "1. WSTAW KLUCZ DO DRZEWA ==" << endl;
	cout << "2. PRZEGLADAJ INORDER =====" << endl;
	cout << "3. OBECNOSC KLUCZA MEMBER =" << endl;
	cout << "4. NAJMNIEJSZY KLUCZ ======" << endl;
	cout << "5. NAJWIEKSZY KLUCZ =======" << endl;
	cout << "6. WYGENERUJ KLUCZE =======" << endl;
	cout << "7. NASTEPNIK ==============" << endl;
	cout << "8. USUWANIE KLUCZA ========" << endl;
	cout << "0. WYJSCIE Z PROGRAMU =====" << endl;
	cout << "===========================" << endl;

	if (i > 1)
	{ 
		cout << "==========INDEKS===========: ";
		for (int j = 1; j < i; j++) cout << j << " ";
		cout << endl;
		cout << endl;
		cout << "======================KLUCZ: ";
		for (int j = 1; j < i; j++) cout << klucz[j] << " "; 
		cout << endl;
		cout << endl;
		cout << "=====================RODZIC: ";
		for (int j = 1; j < i; j++) cout << rodzic[j] << " ";
		cout << endl;
		cout << "==LEWO OD KLUCZA (WSKAZNIK): ";
		for (int j = 1; j < i; j++) cout << lewo[j] << " ";
		cout << endl;
		cout << "=PRAWO OD KLUCZA (WSKAZNIK): ";
		for (int j = 1; j < i; j++) cout << prawo[j] << " ";
	}
	cout << endl;

}
int main()
{
	srand(time(NULL));
	rodzic = new int[max + 1];
	klucz = new int[max + 1];
	lewo = new int[max + 1];
	prawo = new int[max + 1];
	stosUsunietych = new int[max + 1];
	do
	{
		system("CLS");
		menu();
		cin >> wybor;
		switch (wybor) 
		{
		case 1:
			cout << i << " LICZBA: ";
			if (stosUsunietychPusty == false)
			{
				lewo[stosUsunietych[wskStosuUsunietych - 1]] = 0;
				prawo[stosUsunietych[wskStosuUsunietych - 1]] = 0;
				cin >> klucz[stosUsunietych[wskStosuUsunietych - 1]];
				bst_insert(stosUsunietych[wskStosuUsunietych - 1]);
				wskStosuUsunietych--;
				if (wskStosuUsunietych == 0) stosUsunietychPusty = true;
			}
			else
			{
				lewo[i] = 0;
				prawo[i] = 0;
				cin >> klucz[i];
				bst_insert(i);
				i++;
			}
			
			break;
		case 2:
			if (i == 1) cout << "BRAK KLUCZY W DRZEWIE" << endl;
			else
			{
				cout << "ELEMENTY WYSWIETLONE \"INORDER\"" << endl;
				bst_inorder(root);
			}
			getch();
			break;
		case 3:
			if (i == 1) cout << "BRAK KLUCZY W DRZEWIE" << endl;
			else
			{
				cout << "PODAJ SZUKANY KLUCZ: ";
				cin >> poszukiwany;
				if (poszukiwany == klucz[bst_member(rodzic, klucz, lewo, prawo, poszukiwany)]) cout << "KLUCZ JEST W DRZEWIE" << endl;
				else cout << "BRAK KLUCZA W DRZEWIE" << endl;
			}
			getch();
			break;
		case 4:
			if (i == 1) cout << "BRAK KLUCZY W DRZEWIE" << endl;
			else
			{
				cout << "NAJMNIEJSZY KLUCZ TO: " << klucz[bst_min(root)];
			}
			getch();
			break;
		case 5:
			if (i == 1) cout << "BRAK KLUCZY W DRZEWIE" << endl;
			else
			{
				cout << "NAJWIEKSZY KLUCZ TO: " << klucz[bst_max(root)];
			}
			getch();
			break;
		case 6:

			int il_kl_losowych;
			int kl_losowy;
			cout << "ILE KLUCZY WYGENEROWAC? ";
			cin >> il_kl_losowych;
			for (i; i <= il_kl_losowych; i++)
			{
				kl_losowy = rand();
				lewo[i] = 0;
				prawo[i] = 0;
				klucz[i] = kl_losowy;
				bst_insert(i);
			}
			break;
		case 7:
			if (i == 1) cout << "BRAK KLUCZY W DRZEWIE" << endl;
			else
			{
				int nast, zwroc_nast;
				cout << "PODAJ WSKAZNIK (INDEKS) KLUCZA, KTOREMU CHCESZ SPRAWDZIC NASTEPNIK: ";
				cin >> nast;
				zwroc_nast = bst_successor(nast);
				if (zwroc_nast == 0) cout << "PODANY KLUCZ NIE POSIADA NASTEPNIKA" << endl;
				else if (zwroc_nast != -1) cout << "NASTEPNIK TO: " << klucz[zwroc_nast];
			}
			getch();
			break;
		case 8:
			if (i == 1) 
			{ 
				cout << "BRAK KLUCZY W DRZEWIE" << endl; 
				getch();
			}
			else
			{
				int usuw;
				cout << "KTORY KLUCZ USUNAC: " << endl;
				cin >> usuw;
				stosUsunietych[wskStosuUsunietych] = bst_delete(usuw);
				wskStosuUsunietych++;
				stosUsunietychPusty = false;
			}
			break;
		}
	} while (wybor != 0);
	delete[] rodzic;
	delete[] klucz;
	delete[] lewo;
	delete[] prawo;
	return 0;
}