#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
#include <Windows.h>
#include <stdio.h>
#include <locale>  

wchar_t Bukva[33]{ L'а',L'б', L'в', L'г', L'д', L'е', L'ж', L'з', L'и', L'й', L'к', L'л', L'м', L'н', L'о', L'п', L'р', L'с', L'т', L'у', L'ф', L'х', L'ц', L'ч', L'ш', L'щ', L'ъ', L'ы', L'ь', L'э',L'ю',L'я',L'*' };
int Value[33]{ 1,3,2,3,2,1,5,5,1,2,2,2,2,1,1,2,2,2,2,3,10,5,10,5,10,10,10,5,5,10,10,3,0 };

class clovo {
	wchar_t* _word;
	int _length;
public:
	clovo(wchar_t const* word = L"", int length = 0)
	{

		size_t Len = wcslen(word) + 1;
		_word = new wchar_t[Len];
		/*wcsncpy(_word, word, Len);*/
		wcsncpy_s(_word, Len, word, Len);
		_length = Len;
	}

	clovo(const clovo& X) {

		size_t Len = wcslen(X._word) + 1;
		_word = new wchar_t[Len];

		wcsncpy_s(_word, Len, X._word, Len);
		_length = X._length;
	}

	~clovo() {
		if (_word) delete[] _word;
		_word = nullptr;
		_length = 0;
	}

	const wchar_t* getWord() const { return _word; }
	const int getLength() const { return _length; }


	clovo& operator= (const clovo& X) {
		if (this != &X) {

			delete[] _word;

			size_t Len = wcslen(X._word) + 1;
			_word = new wchar_t[Len];
			wcsncpy_s(_word, Len, X._word, Len);

			_length = X._length;
		}
		return *this;
	}

};

std::wostream& operator<< (std::wostream& out, const clovo& X) {
	out << " Слово: " << X.getWord() << " Цена: " << X.getLength();
	return out;
}



std::wofstream& operator<< (std::wofstream& out, clovo& X) {

	out << X.getWord() << std::endl;
	out << X.getLength() << std::endl;

	return out;
}

std::wifstream& operator >> (std::wifstream& in, clovo& X) {
	std::wstring str;
	wchar_t tmpW[40];

	in.getline(tmpW,40);

	X = clovo(tmpW);
	return in;
}



//template <typename T>
//void MergeSortA(T* M, size_t n) {
//
//
//	T* tmp = new T[n];
//	T* from = M, * to = tmp;
//	for (int step = 1; step < n; step *= 2) {
//		int start1, end1, start2, end2;
//		int ind = 0; 
//
//		for (int start = 0; start < n; start += 2 * step) {
//			start1 = start; end1 = start1 + step; end1 = (end1 < n) ? end1 : n;
//			start2 = end1;  end2 = start2 + step; end2 = (end2 < n) ? end2 : n;
//			while (start1 < end1 && start2 < end2) {
//				to[ind++] = (from[start1].getValue() < from[start2].getValue()) ? from[start1++] : from[start2++];
//
//			}
//			while (start1 < end1) { to[ind++] = from[start1++]; }
//			while (start2 < end2) { to[ind++] = from[start2++]; }
//		}
//
//		std::swap(from, to);
//	}
//
//	if (from != M) {
//		
//		int i = 0;
//		while (i < n) {
//			M[i] = tmp[i];
//			++i;
//		}
//
//	}
//	delete[] tmp;
//
//}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


int main()

{
	std::locale loc("Russian");
	std::locale::global(loc);


	const char fname[] = "russian.txt";
	/*const char foname[] = "russian+value.txt";*/
	const int N = 1532630;
	srand(static_cast<unsigned int>(time(0)));
	clovo* Clovar = new clovo[N];
	std::wifstream inFile(fname);

	if (inFile) {
		int i = 0;
		while ((inFile.peek() != EOF) && (i < N)) {
			inFile >> Clovar[i];
			++i;
		}
		inFile.close();
	}
	int Game[8];
	int fishka[8];// массив номеров выпавших фишек
	int prov = 0;
	char r;
	std::cout << "Play game?..." << std::endl;
	std::cin >> r;
	while ((r == 'y') || (r == 'Y'))
	{
		for (int i = 0;i < 8;++i)
		{
			Game[i] = (getRandomNumber(1, 131));
			fishka[i] = Game[i];
			do {
				prov = 1;
				for (int k = 0;k < i;++k) {
					if (fishka[i] == fishka[k]) {
						Game[i] = (getRandomNumber(1, 131));prov = 0;fishka[i] = Game[i];
					}
				}
			} while (prov == 0);
			if (Game[i] <= 10) Game[i] = 0;
			else if (Game[i] <= 13) Game[i] = 1;
			else if (Game[i] <= 18) Game[i] = 2;
			else if (Game[i] <= 21) Game[i] = 3;
			else if (Game[i] <= 26) Game[i] = 4;
			else if (Game[i] <= 35) Game[i] = 5;
			else if (Game[i] <= 37) Game[i] = 6;
			else if (Game[i] <= 39) Game[i] = 7;
			else if (Game[i] <= 47) Game[i] = 8;
			else if (Game[i] <= 51) Game[i] = 9;
			else if (Game[i] <= 57) Game[i] = 10;
			else if (Game[i] <= 61) Game[i] = 11;
			else if (Game[i] <= 66) Game[i] = 12;
			else if (Game[i] <= 74) Game[i] = 13;
			else if (Game[i] <= 84) Game[i] = 14;
			else if (Game[i] <= 90) Game[i] = 15;
			else if (Game[i] <= 96) Game[i] = 16;
			else if (Game[i] <= 102) Game[i] = 17;
			else if (Game[i] <= 107) Game[i] = 18;
			else if (Game[i] <= 110) Game[i] = 19;
			else if (Game[i] <= 111) Game[i] = 20;
			else if (Game[i] <= 113) Game[i] = 21;
			else if (Game[i] <= 114) Game[i] = 22;
			else if (Game[i] <= 116) Game[i] = 23;
			else if (Game[i] <= 117) Game[i] = 24;
			else if (Game[i] <= 118) Game[i] = 25;
			else if (Game[i] <= 119) Game[i] = 26;
			else if (Game[i] <= 121) Game[i] = 27;
			else if (Game[i] <= 123) Game[i] = 28;
			else if (Game[i] <= 124) Game[i] = 29;
			else if (Game[i] <= 125) Game[i] = 30;
			else if (Game[i] <= 128) Game[i] = 31;
			else if (Game[i] <= 131) Game[i] = 32;
			if (i != 7)
			{
				std::cout << "Вам выпала фишка с буквой/символом \"";
				std::wcout << Bukva[Game[i]];
				std::cout << "\" !!!" << std::endl;
			}
			if (i == 7)
			{
				while (Bukva[Game[7]] == L'*')
				{
					Game[7] = (rand() % 131 + 1);
					if (Game[i] <= 10) Game[i] = 0;
					else if (Game[i] <= 13) Game[i] = 1;
					else if (Game[i] <= 18) Game[i] = 2;
					else if (Game[i] <= 21) Game[i] = 3;
					else if (Game[i] <= 26) Game[i] = 4;
					else if (Game[i] <= 35) Game[i] = 5;
					else if (Game[i] <= 37) Game[i] = 6;
					else if (Game[i] <= 39) Game[i] = 7;
					else if (Game[i] <= 47) Game[i] = 8;
					else if (Game[i] <= 51) Game[i] = 9;
					else if (Game[i] <= 57) Game[i] = 10;
					else if (Game[i] <= 61) Game[i] = 11;
					else if (Game[i] <= 66) Game[i] = 12;
					else if (Game[i] <= 74) Game[i] = 13;
					else if (Game[i] <= 84) Game[i] = 14;
					else if (Game[i] <= 90) Game[i] = 15;
					else if (Game[i] <= 96) Game[i] = 16;
					else if (Game[i] <= 102) Game[i] = 17;
					else if (Game[i] <= 107) Game[i] = 18;
					else if (Game[i] <= 110) Game[i] = 19;
					else if (Game[i] <= 111) Game[i] = 20;
					else if (Game[i] <= 113) Game[i] = 21;
					else if (Game[i] <= 114) Game[i] = 22;
					else if (Game[i] <= 116) Game[i] = 23;
					else if (Game[i] <= 117) Game[i] = 24;
					else if (Game[i] <= 118) Game[i] = 25;
					else if (Game[i] <= 119) Game[i] = 26;
					else if (Game[i] <= 121) Game[i] = 27;
					else if (Game[i] <= 123) Game[i] = 28;
					else if (Game[i] <= 124) Game[i] = 29;
					else if (Game[i] <= 125) Game[i] = 30;
					else if (Game[i] <= 128) Game[i] = 31;
					else if (Game[i] <= 131) Game[i] = 32;
				}
			};
			if (i == 7)
			{
				std::cout << "Вам выпала фишка с буквой/символом \"";
				std::wcout << Bukva[Game[7]];
				std::cout << "\" !!!" << std::endl;
			}
		}
		int j;
		int t = 1;//показатель наличия в слове только допустимых букв
		bool slout = 0;//показатель, что слово найдено
		int t8b = 0;//показатель наличия 8 буквы
		wchar_t rb;
		clovo result;
		int realvalue = 0;//стоимость рассматриваемого слова
		int resultvalue = 0;//наибольшая стоимость слова

		for (int i = 0;i < N;++i)
		{
			wchar_t* biw;//массив букв, содержащихся в слове
			biw = new wchar_t[8];
			for (int i = 0;i < 8;++i)
			{
				biw[i] = Bukva[Game[i]];
			}
			j = 0;

			while (Clovar[i].getWord()[j] != L'\0')//проверка, что каждая буква в слове выпала на фишке
			{
				rb = Clovar[i].getWord()[j];
				if ((rb == biw[1]) || (biw[1]=='*'))
				{
					biw[1] = L'#';
				}
				else if ((rb == biw[2]) || (biw[2] == '*'))
				{
					biw[2] = L'#';
				}
				else if ((rb == biw[3]) || (biw[3] == '*'))
				{
					biw[3] = L'#';
				}
				else if ((rb == biw[4]) || (biw[4] == '*'))
				{
					biw[4] = L'#';
				}
				else if ((rb == biw[5]) || (biw[5] == '*'))
				{
					biw[5] = L'#';
				}
				else if ((rb == biw[6]) || (biw[6] == '*'))
				{
					biw[6] = L'#';
				}
				else if ((rb == biw[7]) || (biw[7] == '*'))
				{
					biw[7] = L'#';
					t8b = 1;
				}
				
				else 
				{
					t = 0;break;
				}
				

				++j;
				
			}
			
			if ((t == 1) && (t8b == 1))//в слове нет других кроме выпавших и присутствут обязательная буква
			{
				j = 0;
				realvalue = 0;
				while (Clovar[i].getWord()[j] != L'\0')
				{

					rb = Clovar[i].getWord()[j];
					if (rb == Bukva[Game[0]]) realvalue += Value[Game[0]];
					else if (rb == Bukva[Game[1]]) realvalue += Value[Game[1]];
					else if (rb == Bukva[Game[2]]) realvalue += Value[Game[2]];
					else if (rb == Bukva[Game[3]]) realvalue += Value[Game[3]];
					else if (rb == Bukva[Game[4]]) realvalue += Value[Game[4]];
					else if (rb == Bukva[Game[5]]) realvalue += Value[Game[5]];
					else if (rb == Bukva[Game[6]]) realvalue += Value[Game[6]];
					else if (rb == Bukva[Game[7]]) realvalue += Value[Game[7]];
					++j;
				}
				j = 0;
				if (realvalue > resultvalue)
				{
					result = Clovar[i];
					resultvalue = realvalue;
				}
				slout = 1;
				realvalue = 0;
			}
			t = 1;
			t8b = 0;
			delete[]biw;
		}
		if (slout == 1)
		{
			std::cout << "Ваше слово: ";
			std::wcout << result.getWord() << std::endl;
		}
		if (slout == 0) std::cout << "Слова, составленного из данных букв, не существует(" << std::endl;
		std::cout << "Play game again?..." << std::endl;
		std::cin >> r;
	}
	delete[] Clovar;
}