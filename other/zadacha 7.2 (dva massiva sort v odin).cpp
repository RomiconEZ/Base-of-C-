// zadacha 7.2 (dva massiva sort v odin).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <utility>
#include <string>
#include <iostream>
#include <fstream>
int main()
{

	std::ifstream infile;
	infile.open("d.txt");
	if (!infile) {
		std::cout << "can not open infile" << std::endl;
		return 1;
	}
	std::ofstream out;
	out.open("z.txt");

	if (!out) {
		std::cout << "can not open outfile" << std::endl;
		return 1;
	}
	
	std::string a[100];
	std::string b[100];
	int ai[100];
	int bi[100];
	for (int i = 0; i < 100; ++i) {
	ai[i] = 0;
	bi[i] = 0;
	}
	int na = 0;
	int nb = 0;
	bool prov = 0;
	char ch;
	while ((ch = infile.get()) != EOF) {
		if (ch == '\n') {
			prov = 1;++na;
		}
		if (ch != '\n') {
			if ((prov == 0) && (ch == ' ')) ++na;
			if ((prov == 1) && (ch == ' ')) ++nb;
			if ((prov == 0) && (ch != ' '))
			{
				a[na] += ch;

			}
			else {
				if ((prov == 1) && (ch != ' '))
					b[nb] += ch;

			}
		}
	}
	
		for (int i = 0; i < na; ++i) {
			ai[i] = stoi(a[i]); }
		for (int i = 0; i < nb; ++i) {
			bi[i] = stoi(b[i]);
		}
		int i = 0;
		int j = 0;
		while ((i != na-1) && (j != nb-1))
		{
			if (ai[i] >= bi[j]) 
			{ out << bi[j]<<' ';++j; }
			else 
			{ out << ai[i]<<' ';++i; }
	}
		if (i == na-1 ) {
			for (int k = j; k < nb; ++k) { out << bi[k] << ' '; }
		}
		else { if (j == nb - 1) { for (int k = i; k < na; ++k) { out << ai[k] << ' '; } } }

	out.close();
	infile.close();
	return 1;
}