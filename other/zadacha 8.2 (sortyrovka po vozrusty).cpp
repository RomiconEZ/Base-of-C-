// zadacha 8.2 (sortyrovka po vozrusty).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
	std::string name[100];
	int v[100];
	for (int j = 0;j < 100;++j) { v[j] = 10000000;name[j] = "-"; }
	std::string str;
	int i = 0;
	while (!infile.eof())

	{
		name[i] = "";
		str = "";
		infile >> str;
		name[i] += str;
		name[i] += "  ";
		infile >> str;
		name[i] += str;
		infile >> str;
		for (int j = 0;j < str.length();++j)
		{
			if (str[j] == '.') str.erase(j, 1);
			if (str[j] == '\n') str.erase(j, 1);

		}
		v[i] = stoi(str);
		int y = v[i]%10000;
			int m = ((v[i]-y)%1000000)/10000;
			int d = ((v[i] - y-m) % 100000000)/1000000;
			v[i]= 367 * 2020 - ((7 * (2020 + (11 + 9) / 12)) / 4) + (275 * 11) / 9 + 24 - 730530;
			v[i] =v[i]-( 367 * y - ((7 * (y + (m + 9) / 12)) / 4) + (275 * m) / 9 + d - 730530);
			++i;
	}
	int min = v[0];
	int nom = 0;
	for (int j = 0; j <i; ++j)
	{
		if (v[i] < min)
		{
			nom = i;
		}
	}
	out << "возраст = " << v[nom] << " дней" << ' ' << "(=" << v[nom] / 365 << " год)" << "  " << name[nom] << '\n';
	v[nom] = 1000000;
	
	for (int j = 1; j < i; ++j) {
		min = 1000000;
		for (int k = 0; k < i; ++k)
		{
			if (v[k] < min)
			{
				nom = k;min = v[k];
			}
		}out <<"возраст = "<< v[nom] <<" дней" << ' ' << "(=" << v[nom] / 365 << " год)" << "  " << name[nom] << '\n';
		v[nom] = 10000000;
	}


		out.close();
		infile.close();

		return 0;
	}
