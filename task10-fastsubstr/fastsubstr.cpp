#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
int mystrlen (const char* t) {
	return (strchr(t, 0) - t) / sizeof(char);
}
class stroka {
	char* data;
	unsigned int count;
public:
	stroka(const char* str = "");
	stroka(unsigned int);
	stroka(const stroka&);
	int length() const { return mystrlen(data); }
	unsigned int size()const { return count + 1; }
	const char* str() const { return data; }

	char operator[](int i) const {
		if (i<0 || i>count) throw "Out of string limits.";
		return data[i];
	}
	stroka operator+(const stroka&)const;
	stroka& operator=(const stroka&);

	//bool operator== (const stroka& X) const { return strcmp(data, X.data) == 0; }
	//bool operator!= (const stroka& X) const { return strcmp(data, X.data) != 0; }
	//bool operator< (const stroka& X) const { return strcmp(data, X.data) < 0; }

	~stroka() {
		if (data) delete[] data;
		data = nullptr;
	}
};
//--------------------------------------------------------
stroka::stroka(const char* str) {
	count = mystrlen(str);
	data = new char[count + 1];
	memcpy(data, str, count + 1);
}
//--------------------------------------------------------
stroka::stroka(unsigned int N) {
	count = N;
	data = new char[N + 1];
	data[0] = '\0';
}
//--------------------------------------------------------
stroka::stroka(const stroka& X) {
	count = X.count;
	data = new char[count + 1];
	memcpy(data, X.data, count + 1);
}
//--------------------------------------------------------
stroka& stroka::operator=(const stroka& X) {
	if (this != &X) {
		delete[] data;
		count = X.count;
		data = new char[count + 1];
		memcpy(data, X.data, count + 1);
	}
	return *this;
}
//--------------------------------------------------------
stroka stroka::operator+(const stroka& X)const {
	unsigned int count1 = mystrlen(data);
	stroka C(count1 + X.count);
	memcpy(C.data, data, count1);
	memcpy(C.data + count1, X.data, X.count + 1);
	return C;
}

//--------------------------------------------------------
std::ostream& operator<< (std::ostream& out, const stroka& X) { // переопределение оператора вывода
	out << X.str();
	return out;
}
//--------------------------------------------------------
template <typename ElementType>
void ExpandArray(ElementType * &array, unsigned int old_size, unsigned int new_size) // Функция расширения массива
{
	if (old_size < new_size)
	{
		ElementType* new_array = new ElementType[new_size];
		memcpy(new_array, array, old_size * sizeof(ElementType));
		/*for (unsigned int i = 0; i < old_size; i++)
		{
			new_array[i] = array[i];
		}*/

		delete[] array;
		array = new_array;
	}
}

void computePiArray(stroka substring, int* Pi) 
//самый длинный соответствующий префикс, который также является суффиксом для подстроки длины i, начиная с начала
{
	int j = 0; //длина предыдущего самого длинного суффикса префикса
	int M = substring.length();
	Pi[0] = 0; // Pi[0] всегда 0

	// вычисляем Pi[i] для i от 1 до M-1
	int i = 1;
	while (i < M) {
		if (substring[i] == substring[j]) {
			j++;
			Pi[i] = j;
			i++;
		}
		else // substring[i] не совпадает с substring[j]
		{
			
			if (j > 0) { // учитываем ранее найденную информацию
				j = Pi[j - 1];
			}
			else // if (j == 0) // j указывает на первый элемент
			{
				Pi[i] = 0;
				i++;
			}
		}
	}
}


void SubstringSearck(const char* fname, const char* outfname)
{
	std::ifstream inFile(fname);
	std::ofstream outFile(outfname);
	//-------------------------------------------------------------------------------
	// Посимвольное считывание строчек в динамические массивы char-ов.Первая строка до '\n', вторая до eof. При надобности расширяем массивы.
	char* INstring = new char[150];
	char* INsubstring = new char[15];

	unsigned int capacity_of_INstring = 150;
	unsigned int capacity_of_INsubstring = 15;

	char sym = '\n'; // первая строка оканчивается символом \n
	unsigned int counter = 0; // число элементов в строчке
	
	char ch = inFile.get();
	do
	{
		if (counter == capacity_of_INsubstring)
		{
			ExpandArray(INsubstring, capacity_of_INsubstring, capacity_of_INsubstring << 1);
			capacity_of_INsubstring = capacity_of_INsubstring << 1;
		}
		INsubstring[counter++] = ch;
		ch = inFile.get();
	} while (ch != sym && !inFile.eof());
	INsubstring[counter] = '\0'; // массив оканчивается символом \0 для удобного преобразования в stroka
	
	counter = 0;
	ch = inFile.get();
	do
	{
		if (counter == capacity_of_INstring)
		{
			ExpandArray(INstring, capacity_of_INstring, capacity_of_INstring << 1);
			capacity_of_INstring = capacity_of_INstring << 1;
		}


		INstring[counter++] = ch;
		ch = inFile.get();
	} while (ch != sym && !inFile.eof());
	INstring[counter] = '\0';
	//--------------------------------------------------------------------------------------
	//Преобразуем массивы char в stroka
	stroka string(INstring);
	stroka substring(INsubstring);
	//---------------------------------
	int* begins_of_substring = new int[10];// массив индексов начал вхождений подстрок
	int capacity_of_begins_of_substring = 10; //вместимость массива для отслеживания полного заполнения
	int amount_of_begins_of_substring = 0; // количество записей в массиве
	//---------------------------KMP алгоритм------------------------------
	
	int M = substring.length();
	int N = string.length();

	// создадим Pi[], который будет хранить самый длинный префикс-суффикс для подстроки
	
	int* Pi = new int[M];

	// Вычисляем Pi
	computePiArray(substring, Pi);
	//Для каждого подшаблона [0. i] где i = 0 to m - 1, Pi[i] сохраняет длину максимально подходящего префикса, 
	//который также является суффиксом подшаблона[0..i].
	/*Мы начинаем сравнение substring[j] с j = 0 с символами string.
	Мы продолжаем подбирать символы string[i] и substring[j] и продолжаем увеличивать i и j, 
	в то время как string[i] и substring[j] продолжают соответствовать.
	Когда мы видим несоответствие:
	Мы знаем, что символы substring[0..j - 1] соответствуют string[i - j... i - 1]
	Мы также знаем, что Pi[j - 1] - это число символов string[0...j - 1],
	которые являются как правильным префиксом, так и суффиксом.
	Мы можем заключить, что нам не нужно соответствовать этим Pi[j - 1] символов 
	с string[i - j... i - 1] потому что мы знаем,что эти символы в любом случае совпадут.*/
	int i = 0; // индекс для string
	int j = 0; // индекс для substring
	while (i < N) {
		if (substring[j] == string[i]) {
			j++;
			i++;
		}

		if (j == M) { // совпадение всей подстроки
			
			begins_of_substring[amount_of_begins_of_substring++] = i - j + 1;
			if (amount_of_begins_of_substring == capacity_of_begins_of_substring) // расширение массива при заполнении
			{
				ExpandArray(begins_of_substring, capacity_of_begins_of_substring, capacity_of_begins_of_substring << 1);
				capacity_of_begins_of_substring = capacity_of_begins_of_substring << 1;
			}
			j = Pi[j - 1];
		}
		//после несовпадения символа мы сдвигаемся на длину префикса-суффикса части строки до
		// несовпадающего символа, так как мы значем что префикс подстроки совпадет частью
		// строки, которую мы уже рассмотрели
		
		// несовпадение после j совпадений
		else if (i < N && substring[j] != string[i]) {
			// Не проверяем свопадение Pi[0..Pi[j-1]] символов,так как они все равно совпадут
			if (j != 0)
				j = Pi[j - 1];
			else
				i = i + 1;
		}
	}
//--------------------------------------------------------------------------
	// Вывод результатов
	outFile << amount_of_begins_of_substring << '\n';
	for (int i = 0; i < amount_of_begins_of_substring-1; ++i)
		outFile << begins_of_substring[i] << " ";
	outFile << begins_of_substring[amount_of_begins_of_substring-1];
	
//--------------------------------------------------------------------------
	inFile.close();
	outFile.close();
	delete[] Pi;
	delete[] begins_of_substring;
	delete[] INstring;
	delete[] INsubstring;
}

int main(int argc, char* argv[]){
  if (argc<3) {
    return 1;
  }
  std::ifstream inFile(argv[1]);
  if (!inFile){
    return 2;
  }
  std::ofstream outFile(argv[2]);
  if (!outFile){
    return 3;
  }
  
  inFile.close();
	outFile.close();
	SubstringSearck(argv[1], argv[2]);
  return 0;
}
