//Kitabxanalar ----------------------------------------------------------------------
#include<Windows.h>      // Windowsda ekrana silib yazmaq ucun - CMD de
#include<iostream>       // Giris -cixis ucun
#include<conio.h>        // Klavyatura girisi almaq ucun 
#include <random>        // <random> kitabxanasi (C++11 ve sonrasi)
#include<cmath>          // Riyazi hesablamalar ucun 
#include <vector>        // vector tipi üçün

using namespace std;     // :: yazmamaq ucun meselen std::cout<<"Hello world";

// Deyisenler ------------------------------------------------------------------------
const int Xuz = 20;  // matris ucun sabit deyisen olmalidi ona gore const
const int Yuz = 10;
int Ekran[Yuz][Xuz];

int ilanX = Xuz / 2;//Ekranin ortasi
int ilanY = Yuz / 2;

int almaX;
int almaY;

char yon = 'd'; // başlanğıc istiqamət sağ teref gedir

vector<pair<int, int>> beden;  // Bedenin kordinantlarini almaq ucun x y 
int skor = 0;


//Random reqem almaq ucun C++ 11 sonrasi------------------------------------------------
random_device random;                          // real random mənbə
mt19937 generator(random());                   // generator
uniform_int_distribution<> randomX(1, Xuz - 2);  // 1–Xuz-2 arasi 
uniform_int_distribution<> randomY(1, Yuz - 2);  // 1–Uuz-2 arasi

// ==================== Funksiyalar ====================
void EkranHesap();
void EkranYaz();
void IlanPortal();
void AlmaYarat();
void KlavGiris();
// -----------------------------------------------------------------------------



int main()
{
	almaX = randomX(generator);  //Random ededi Alma deyisenine veririk 
	almaY = randomY(generator);

	beden.push_back({ ilanX, ilanY });        //quyruq 1
	//beden.push_back({ ilanX - 1, ilanY });    //quyruq 2  Eger baslangica 2 beden isteyirsensa aktiv ele bu en sade usuldu


	while (true)
	{
		system("cls"); //Ekrani silmek ucun 
		cout << "Skor: " << skor << endl;


		beden.insert(beden.begin(), { ilanX, ilanY });// Yeni başı əlavə et

		beden.pop_back();// Son hissəni sil (əgər alma yeyilməyibsə)

		//Funksiyalari isletmek ucun 
		KlavGiris();
		EkranHesap();
		EkranYaz();
		IlanPortal();
		AlmaYarat();

		Sleep(100);
	}
}


//Esas Hesablarin getdiyi yer Map-in qurulusu burda duzelir 
void EkranHesap()
{
	for (int y = 0; y < Yuz; y++) {
		for (int x = 0; x < Xuz; x++)
		{
			//Ekran[y][x] = (x == 0 || x == Xuz-1 || y == 0 || y == Yuz-1) ? 1:0 ;

			if (x == 0 || x == Xuz - 1 || y == 0 || y == Yuz - 1)
				Ekran[y][x] = 1;                 // divar üstte
			else if (x == ilanX && y == ilanY)
				Ekran[y][x] = 2;                 // ilan

			else if (x == almaX && y == almaY)
				Ekran[y][x] = 4;                 // alma
			else
				Ekran[y][x] = 0;                 // boşluq

		}
	}
	// bədəni cızmaq
	for (auto& par : beden)
	{
		Ekran[par.second][par.first] = 3; // bədən hissəsi  3 yeni --> o
	}

}

// Ekrana yazdirma ucun Esas cap olunma yeri
void EkranYaz()
{
	for (int y = 0; y < Yuz; y++)
	{
		for (int x = 0; x < Xuz; x++)
		{
			switch (Ekran[y][x])
			{
			case 1: cout << "#"; break; // Divar
			case 2: cout << "O"; break; // Ilanin basi 
			case 3: cout << "o"; break; // ilanin bedeni
			case 4: cout << "@"; break; // Alma
			default:cout << " ";        // Bosluq

			}
		}
		cout << endl;
	}
}

//Ilanin divarlar arasinda kecidi ucun 
void IlanPortal()
{
	if (ilanX <= 0) ilanX = Xuz - 2;     //Ilan solda duvara gire onun kordinastini saga atir 
	else if (ilanX >= Xuz - 1) ilanX = 1;

	if (ilanY <= 0) ilanY = Yuz - 2;
	else if (ilanY >= Yuz - 1) ilanY = 1;

}

// ==================== Alma Yarat ====================
void AlmaYarat()//Alma yeyilenden sonra rondom olusma ve sadece bos yerlerde cixmasi ucun
{
	if (ilanX == almaX && ilanY == almaY)//Ilan almanin kordinantina girse yenisi yarat
	{
		almaX = randomX(generator);
		almaY = randomY(generator);

		beden.push_back(beden.back()); // yeni hissə əlavə et
		skor += 10;

		do
		{
			almaX = randomX(generator);
			almaY = randomY(generator);

		} while (Ekran[almaY][almaX] != 0);

	}
}

// ==================== KlavGiris ====================

void KlavGiris()
{


	if (_kbhit())
	{
		char h = _getch();

		if ((h == 'a' && yon != 'd') || 
			(h == 'd' && yon != 'a') ||
			(h == 'w' && yon != 's') ||
			(h == 's' && yon != 'w'))
			yon = h;
	}


	switch (yon)
	{
		case 'a': ilanX--; break;
		case 'd': ilanX++; break;
		case 'w': ilanY--; break;
		case 's': ilanY++; break;
	}
}
