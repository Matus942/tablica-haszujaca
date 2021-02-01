#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>
#include <cstdlib>

using namespace std;

struct Object
{
public:
	long k;
	string s;

public:
	Object();
	Object(long, string);
	~Object();
};


class HashTable : public Object
{
public:
	long size_ = 11;
	string tekst;
	string tekst_1;
	string size_2;
	string delete_2;
	long liczba;
	Object *TabHT = new Object[size_];
	vector<string> dane;
	string imie[256];
	string znak[256];
	HashTable();
	~HashTable();

	void Add(long, string);
	void Delete(long);
	long hash_(long);
	void wczytaj();
	void wpisanie();
	void ShowT();



};

int main()
{
	HashTable hash;

	hash.wczytaj();
	hash.wpisanie();


	
	return 0;
}

Object::Object()
	:
	k(0)
	, s("pusto")
{
}

Object::Object(long key, std::string t)
	:
	k(key)
	, s(t)
{
}

Object::~Object()
{
}

HashTable::HashTable()
{
}
HashTable::~HashTable()
{
}

void HashTable::Add(long liczba, string tekst)
{

	Object temp(liczba, tekst);
	liczba = hash_(liczba);
	std::string temp1 = TabHT[liczba].s;
	if (temp1 == "pusto")
	{
		TabHT[liczba] = temp;
	}
	else
	{
		for (int i = liczba; i<size_; i++)
		{
			if (TabHT[i].s == "pusto")
			{
				TabHT[i] = temp;
				break;
			}
			if (i >= size_)
			{
				liczba = 0;
			}
		}


	}
}

void HashTable::Delete(long k)
{

	long i = hash_(k);
	while (TabHT[i].k != k && i < size_ && TabHT[i].k != 0)
		i++;

	if (i >= size_)
		return;


	long p = i;
	long o = i;
	while (TabHT[p].k != 0 && p < size_)
	{
		if (hash_(TabHT[++p].k) == hash_(k))
			o = p;
	}


	TabHT[i] = TabHT[o];
	TabHT[o++] = Object();


	while (TabHT[o].k != 0)
	{
		Add(TabHT[o].k, TabHT[o].s);
		TabHT[o] = Object();
		o++;
	}
	TabHT[--o] = Object();
}

long HashTable::hash_(long m)
{
	return m%size_;
}
void HashTable::wczytaj()
{

	//ifstream plik("skrypt.txt");
	//if (!plik) cout << "Brak pliku 'Data.txt' w katalogu z programem. Sproboj ponownie\n";
	string x;
	while (cin >> x)
		dane.push_back(x);

	tekst = imie[0];
	tekst_1 = znak[0];


}
void HashTable::wpisanie()
{
	int j = 0;
	for (int i = 0; i<dane.size(); i++)
	{                                      ///wyswietlanie
		if (dane[i] == "add")
		{
			znak[j] = dane[i + 1];
			imie[j] = dane[i + 2];
			tekst_1 = znak[j];
			tekst = imie[j];
			string str(tekst_1);
			long liczba;
			liczba = strtol(str.c_str(), NULL, 10);
			Add(liczba, tekst);
		}
		j++;
		if(dane[i]=="size")
		{
			size_2 = dane[i+1];
			string str(size_2);
			long liczba1;
			liczba1 = strtol(str.c_str(), NULL, 10);
			size_ = liczba1;

		}
		if (dane[i] == "delete")
		{
			delete_2 = dane[i + 1];
			string str(delete_2);
			long liczba2;
			liczba2 = strtol(str.c_str(), NULL, 10);
			Delete(liczba2);

		}
		if (dane[i] == "print")
		{
			ShowT();
		}
		if(dane[i] == "stop")
		{
			break;
		}

	}

}

void HashTable::ShowT()
{
	for (int i = 0; i<size_; i++)
	{
		if (TabHT[i].k != 0)
		{
			cout << i << " " << TabHT[i].k;
			cout << " " << TabHT[i].s << endl;
		}
	}
	cout << "\n";
}