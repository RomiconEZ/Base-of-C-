// zadacha 7.3(pary iz dva n chisel).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <utility>
#include <string>
#include <iostream>
#include <fstream>




template<typename T>
void choicesort(T a[], size_t n)
{
	
	for (size_t j = 0;j < n - 1;++j)
	{
		size_t k = j;//индекс мин эл
		for (size_t i = k + 1;i < n;++i)
		{
			if ((n / 2) % 2 == 0) {
				if (j < ((n - 1) / 2) + 1) {
					if ((abs(a[i]) < abs(a[k])) || ((abs(a[i]) == abs(a[k])) && (a[i] < a[k])))  k = i;
				}
				else {
					if ((abs(a[i]) < abs(a[k])) || ((abs(a[i]) == abs(a[k])) && (a[i] > a[k])))  k = i;
				}
			}else{ if ((abs(a[i]) < abs(a[k])) || ((abs(a[i]) == abs(a[k])) && (a[i] < a[k])))  k = i;
			}
		}
		if (k != j) { std::swap(a[k], a[j]); }
		
	}
}

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
	std::string str;
	int a[20];
	for (int i = 0;i < 20;++i) { a[i] = 0; }
	int n = 0;
	while (!infile.eof())

	{
		str = "";
		infile >> str;
		bool sign = 0;
		if (str[0] == '-')
		{
			sign = 1;
			str.erase(0, 1);

		}
		if (str != "\n") {
			a[n] = stoi(str);
		}
		if (sign == 1) { a[n] =-a[n]; }
		++n;
	}
	
	choicesort(a, n);
	for (int k = 0;k < n;++k) { std::cout << a[k] << ' '; }
	std::cout << std::endl;
	int s = n / 2;
	for (int i = 0;i <= s-1;++i) { out << '(' << a[i] << ';' << a[n-1-i] << ')'<< std::endl;; }
	out.close();
	infile.close();
	return 0;
}