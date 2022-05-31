#include <string>
#include <iostream>
#include <fstream>
int main()
{
	std::ifstream infile;
	infile.open("slovar ang-chi.txt");
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

	int* v = new int[19500];//создаю маасив для чисел, каждое из которых составляется из кодов первых трех букв каждой строки

	for (int i = 0;i < 19500;++i) { v[i] = 0; }
	std::string str;
	int i = 0;
	while (!infile.eof())

	{
		str = "";
		std::getline(infile, str);
		int k = 0;
		int kol = 0;
		while (kol < 3) {//строю число, с помощью присоединения к числу справа кода следующей буквы
			if (str[k] != ' ') {
				v[i] = int(str[k]) + v[i] * 1000;
				++kol;
			}++k;
		}
		++i;
	}

	infile.clear();
	infile.seekg(0);
	long int min;
	long int nom = 0;
	int por = 0;


	for (int j = 0; j < i; ++j) {//нахожу минимальное число в массиве чисел и вывожу строку с таким же номером из исходного файла в выходной файл, затем меняю это число на большое число
		min = 999999999;
		for (int k = 0; k < i; ++k)
		{
			if (v[k] < min)
			{
				nom = k;min = v[k];
			}
		}
		por = 0;
		while (getline(infile, str))// читаю из файла строку до тех пор, пока не прочитаетcя строка нужного номера
		{
			if (por == nom)
			{
				out << str << std::endl;
				break;
			}
			por++;
		}
		infile.clear();
		infile.seekg(0);

		v[nom] = 999999999;
	}


	out.close();
	infile.close();
	delete[] v;
	return 0;
}