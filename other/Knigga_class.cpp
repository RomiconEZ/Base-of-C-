#include <iostream>
#include <fstream>
#include <string>

#include <Windows.h>


class knigga {
protected:
	char* _name;
	char* _avtor;
	char* _izda;
	char* _dataexit;
	char* _kolvostr;
public:
	knigga(const char* name = "", const char* avtor = "", const char* izda = "", const char* dataexit = "", const char* kolvostr = "") {
		size_t Len = strlen(name) + 1;
		_name = new char[Len];
		strcpy_s(_name, Len, name);

		size_t Len1 = strlen(avtor) + 1;
		_avtor = new char[Len1];
		strcpy_s(_avtor, Len1, avtor);

		size_t Len2 = strlen(izda) + 1;
		_izda = new char[Len2];
		strcpy_s(_izda, Len2, izda);

		size_t Len3 = strlen(dataexit) + 1;
		_dataexit = new char[Len3];
		strcpy_s(_dataexit, Len3, dataexit);

		size_t Len4 = strlen(kolvostr) + 1;
		_kolvostr = new char[Len4];
		strcpy_s(_kolvostr, Len4, kolvostr);

	}

	knigga(const knigga& X) {
		size_t Len = strlen(X._name) + 1;
		_name = new char[Len];
		strcpy_s(_name, Len, X._name);

		size_t Len1 = strlen(X._avtor) + 1;
		_avtor = new char[Len1];
		strcpy_s(_avtor, Len1, X._avtor);

		size_t Len2 = strlen(X._izda) + 1;
		_izda = new char[Len2];
		strcpy_s(_izda, Len2, X._izda);

		size_t Len3 = strlen(X._dataexit) + 1;
		_dataexit = new char[Len3];
		strcpy_s(_dataexit, Len3, X._dataexit);

		size_t Len4 = strlen(X._kolvostr) + 1;
		_kolvostr = new char[Len4];
		strcpy_s(_kolvostr, Len4, X._kolvostr);
	}

	~knigga() {
		if (_name) delete[] _name;
		_name = nullptr;
		if (_avtor) delete[] _avtor;
		_avtor = nullptr;
		if (_izda) delete[] _izda;
		_izda = nullptr;
		if (_dataexit) delete[] _dataexit;
		_dataexit = nullptr;
		if (_kolvostr) delete[] _kolvostr;
		_kolvostr = nullptr;
	}
	
	const char* getName() const { return _name; }
	const char* getAvtor() const { return _avtor; }
	const char* getIzda() const { return _izda; }
	const char* getDataexit() const { return _dataexit; }
	const char* getKolvostr() const { return _kolvostr; }
	
	knigga& operator= (const knigga& X) {
		if (this != &X) {

	
			delete[] _name;
			delete[] _avtor;
			delete[] _izda;
			delete[] _dataexit;
			delete[] _kolvostr;

			size_t Len = strlen(X._name) + 1;
			_name = new char[Len];
			strcpy_s(_name, Len, X._name);
			size_t Len1 = strlen(X._avtor) + 1;
			_avtor = new char[Len1];
			strcpy_s(_avtor, Len1, X._avtor);

			size_t Len2 = strlen(X._izda) + 1;
			_izda = new char[Len2];
			strcpy_s(_izda, Len2, X._izda);

			size_t Len3 = strlen(X._dataexit) + 1;
			_dataexit = new char[Len3];
			strcpy_s(_dataexit, Len3, X._dataexit);

			size_t Len4 = strlen(X._kolvostr) + 1;
			_kolvostr = new char[Len4];
			strcpy_s(_kolvostr, Len4, X._kolvostr);
		}
		return *this;
	}




};

int menu() {
	std::cout << "--------Класс: книги--------" << std::endl;
	std::cout << "1.вывод книги по автору" << std::endl;
	std::cout << "2.вывод книги по названию " << std::endl;
	std::cout << "3.вывод книги по дате выхода" << std::endl;
	std::cout << "4.вывод книги по интервалу дат выхода" << std::endl;
	std::cout << "5.записать книгу" << std::endl;
	std::cout << "6.вывести список книг" << std::endl;
	std::cout << "0. Exit" << std::endl;
	int action;
	std::cin >> action;
	std::cin.ignore();
	return action;
}



std::ostream& operator<< (std::ostream& out, const knigga& X) {
	out << X.getName() << " Автор: " << X.getAvtor() << " Издательство: " << X.getIzda() << " Дата выхода: " << X.getDataexit() << " Количество страниц: " << X.getKolvostr();
	return out;
}



std::ofstream& operator<< (std::ofstream& out, knigga& X) {
	
	out << X.getName() << std::endl;
	out << X.getAvtor() << std::endl;
	out << X.getIzda() << std::endl;
	out << X.getDataexit() << std::endl;
	out << X.getKolvostr() << std::endl;

	return out;
}




std::ifstream& operator >> (std::ifstream& in, knigga& X) {
	char tmpN[30];
	char tmpA[30];
	char tmpI[30];
	char tmpD[10];
	char tmpK[5];
	in.getline(tmpN, 30);
	in.getline(tmpA, 30);
	in.getline(tmpI, 30);
	in.getline(tmpD, 10);
	in.getline(tmpK, 5);
	X = knigga(tmpN,tmpA,tmpI,tmpD,tmpK);
	return in;
}

int main()

{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
const char fname[] = "knigga.dat.txt";
const int N = 50;
knigga Kniggas[N];
std::ifstream inFile(fname);
int begofwrit=0;
if (inFile) {
	int i = 0;
	while ((inFile.peek() != EOF) && (i < N)) {
		inFile >> Kniggas[i];
		++i;
	}
	begofwrit = i;
	/*for (int k = i;k < 50;++k) { Kniggas[k] = ("", "", "", "", ""); }*/
	
	inFile.close();
}



for (int i = 0; i < begofwrit; ++i)
{
	if (*(Kniggas[i].getName()) != '\0') { std::cout << i + 1 << ". " << Kniggas[i] << std::endl; }
}


std::ofstream outFile(fname);
for (int i = 0; i < begofwrit; ++i)
	outFile << Kniggas[i];
outFile.close();

int action;

do {
	action = menu();
	try {
		switch (action) 
		{
		case 1:
		{ std::cout << "введите автора книги" << std::endl;
		std::string myavtor;
		getline(std::cin, myavtor);
		int j = 0;
		while (*(Kniggas[j].getAvtor()) != '\0')
		{
			if (std::string(Kniggas[j].getAvtor()) == myavtor) { std::cout << Kniggas[j] << std::endl; }
			else
			{
				std::string s = std::string(Kniggas[j].getAvtor());
				size_t pos = s.find(myavtor);
				
				//std::cout << std::string(Kniggas[j].getAvtor()) << myavtor << std::endl;//!

				if (pos != std::string::npos) { std::cout << Kniggas[j] << std::endl; }
			}
			++j;
		}
		break;
		}
		case 2:
		{std::cout << "введите название книги" << std::endl;
		std::string myname;
		getline(std::cin, myname);
		int j = 0;
		while (*(Kniggas[j].getName()) != '\0')
		{
			if (std::string(Kniggas[j].getName()) == myname) { std::cout << Kniggas[j] << std::endl; }
			else {
				std::string s = std::string(Kniggas[j].getName());
				size_t pos = s.find(myname);
				if (pos != std::string::npos) { std::cout << Kniggas[j] << std::endl; }
			}
			++j;
		}
		break;
		}
		case 3:
		{
			std::cout << "введите дату выхода" << std::endl;
			std::string mydate;
			getline(std::cin, mydate);
			int j = 0;
			while (*(Kniggas[j].getDataexit()) != '\0')
			{
				if (std::string(Kniggas[j].getDataexit()) == mydate) { std::cout << Kniggas[j] << std::endl; }
				else
				{
					std::string s = std::string(Kniggas[j].getDataexit());
					size_t pos = s.find(mydate);
					if (pos != std::string::npos) { std::cout << Kniggas[j] << std::endl; }
				}
				++j;
				
			}
			break;
		}
		case 4:
		{
			std::cout << "введите левую границу даты выхода" << std::endl;
			std::string mydate1;
			getline(std::cin, mydate1);
			std::cout << "введите правую границу даты выхода" << std::endl;
			std::string mydate2;
			getline(std::cin, mydate2);

			for (int j = 0;j < mydate1.length();++j)
			{
				if (mydate1[j] == '.') mydate1.erase(j, 1);
				if (mydate1[j] == '\n') mydate1.erase(j, 1);

			}
			int mydate1n = std::stoi(mydate1);
			int y = mydate1n % 10000;
			int m = ((mydate1n - y) % 1000000) / 10000;
			if (m < 1) m = 1;
			int d = ((mydate1n - y - m) % 100000000) / 1000000;
			if (d < 1) d = 1;
			/*mydate1n = 367 * 2020 - ((7 * (2020 + (11 + 9) / 12)) / 4) + (275 * 11) / 9 + 24 - 730530;*/
			mydate1n = 367 * y - ((7 * (y + (m + 9) / 12)) / 4) + (275 * m) / 9 + d - 730530;

			//std::cout << mydate1n << std::endl;//!

			for (int j = 0;j < mydate2.length();++j)
			{
				if (mydate2[j] == '.') mydate2.erase(j, 1);
				if (mydate2[j] == '\n') mydate2.erase(j, 1);

			}
			int mydate2n = std::stoi(mydate2);
			 y = mydate2n % 10000;
			 m = ((mydate2n - y) % 1000000) / 10000;
			if (m < 1) m = 1;
			 d = ((mydate2n - y - m) % 100000000) / 1000000;
			if (d < 1) d = 1;
			mydate2n = 367 * y - ((7 * (y + (m + 9) / 12)) / 4) + (275 * m) / 9 + d - 730530;

			//std::cout << mydate2n << std::endl;//!

			int j = 0;
			while (*(Kniggas[j].getDataexit()) != '\0')
			{
				std::string s = std::string(Kniggas[j].getDataexit());

				for (int j = 0;j < s.length();++j)
				{
					if (s[j] == '.') s.erase(j, 1);
					if (s[j] == '\n') s.erase(j, 1);

				}
				int sn = std::stoi(s);
				 y = sn % 10000;
				 m = ((sn - y) % 1000000) / 10000;
				if (m < 1) m = 1;
				 d = ((sn - y - m) % 100000000) / 1000000;
				if (d < 1) d = 1;
				sn = 367 * y - ((7 * (y + (m + 9) / 12)) / 4) + (275 * m) / 9 + d - 730530;
				//std::cout << sn << std::endl;//!
				if ((mydate2n > sn) && (mydate1n < sn)) { std::cout << Kniggas[j] << std::endl; }
				++j;
			}
				break;
			}
		
		case 5:
		{
			std::ofstream outfile;
		outfile.open("knigga.dat.txt", std::ios::app);
		
		std::string name;
		std::string avtor;
		std::string izda;
		std::string date;
		std::string kolvostr;
		std::cout << "введите название книги"<<std::endl;
		getline(std::cin, name);
		const char* n = name.c_str();
		std::cout << "введите имя автора" << std::endl;
		getline(std::cin, avtor);
		const char* a = avtor.c_str();
		std::cout << "введите название издательства" << std::endl;
		getline(std::cin, izda);
		const char* i = izda.c_str();
		std::cout << "введите дату выхода" << std::endl;
		getline(std::cin, date);
		const char* d = date.c_str();
		std::cout << "введите количество страниц" << std::endl;
		getline(std::cin, kolvostr);
		const char* k = kolvostr.c_str();
		
		Kniggas[begofwrit] = knigga(n, a, i, d, k);;
		outfile << Kniggas[begofwrit];
		outfile.close();
		++begofwrit;

        break;
		}
		case 6:
		{
		for (int i = 0; i < begofwrit; ++i)
		{
			if (*(Kniggas[i].getName()) != '\0') { std::cout << i + 1 << ". " << Kniggas[i] << std::endl; }
		}
			break;
		}
		case 0:
		{
			return 0;
		}
		}
	}
	catch (const char* error) {
		std::cerr << "ERROR: " << error << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
} while (action > 0);

}


class student_book : public knigga
{
	char* _predmet;
	char* _№class;
public:
	student_book(const char* name = "", const char* avtor = "", const char* izda = "", const char* dataexit = "", const char* kolvostr = "", const char* predmet = "", const char* №class = "") {
		size_t Len = strlen(name) + 1;
		_name = new char[Len];
		strcpy_s(_name, Len, name);

		size_t Len1 = strlen(avtor) + 1;
		_avtor = new char[Len1];
		strcpy_s(_avtor, Len1, avtor);

		size_t Len2 = strlen(izda) + 1;
		_izda = new char[Len2];
		strcpy_s(_izda, Len2, izda);

		size_t Len3 = strlen(dataexit) + 1;
		_dataexit = new char[Len3];
		strcpy_s(_dataexit, Len3, dataexit);

		size_t Len4 = strlen(kolvostr) + 1;
		_kolvostr = new char[Len4];
		strcpy_s(_kolvostr, Len4, kolvostr);

		size_t Len5 = strlen(predmet) + 1;
		_predmet = new char[Len5];
		strcpy_s(_predmet, Len5, predmet);

		size_t Len6 = strlen(№class) + 1;
		_№class = new char[Len6];
		strcpy_s(_№class, Len6, №class);

	}


	student_book(const student_book& X) {
		size_t Len = strlen(X._name) + 1;
		_name = new char[Len];
		strcpy_s(_name, Len, X._name);

		size_t Len1 = strlen(X._avtor) + 1;
		_avtor = new char[Len1];
		strcpy_s(_avtor, Len1, X._avtor);

		size_t Len2 = strlen(X._izda) + 1;
		_izda = new char[Len2];
		strcpy_s(_izda, Len2, X._izda);

		size_t Len3 = strlen(X._dataexit) + 1;
		_dataexit = new char[Len3];
		strcpy_s(_dataexit, Len3, X._dataexit);

		size_t Len4 = strlen(X._kolvostr) + 1;
		_kolvostr = new char[Len4];
		strcpy_s(_kolvostr, Len4, X._kolvostr);

		size_t Len5 = strlen(X._predmet) + 1;
		_predmet = new char[Len5];
		strcpy_s(_predmet, Len5, X._predmet);

		size_t Len6 = strlen(X._№class) + 1;
		_№class = new char[Len6];
		strcpy_s(_№class, Len6, X._№class);
	}

	~student_book() {
		if (_name) delete[] _name;
		_name = nullptr;
		if (_avtor) delete[] _avtor;
		_avtor = nullptr;
		if (_izda) delete[] _izda;
		_izda = nullptr;
		if (_dataexit) delete[] _dataexit;
		_dataexit = nullptr;
		if (_predmet) delete[] _predmet;
		_predmet = nullptr;
		if (_№class) delete[] _№class;
		_№class = nullptr;
	}
};
