#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cctype> 
#include "time.h"
#include <cmath>
#include <stack>
#include <map>
#include <algorithm>
#include <sstream>

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void sortirovka_po_alfavitu(const std::string& data, const std::string& zap, int& kolvo)
{
	try {
		std::ifstream infile;
		infile.open(data);

		if (!infile) {
			
			throw 1;
		}

		std::ofstream out;
		out.open(zap);
		if (!out) {
			
			throw 2;
		}

		int* v = new int[kolvo];//создаю маасив для чисел, каждое из которых составляется из кодов первых трех букв каждой строки

		for (int i = 0;i < kolvo;++i) { v[i] = 0; }
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

	}
		catch (int a)
		{
			if (a==1) std::cout << "can not open infile" << std::endl;
			if (a==2) std::cout << "can not open outfile" << std::endl;
		}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

char base64char(unsigned char b)
{
	b = b & 0x3F;
	if (b < 26) return'A' + b;
	if (b < 52) return 'a' + (b - 26);
	if (b < 62) return '0' + (b - 52);
	if (b == 62) return '+';
	return '/';
}

static const std::string base64_char =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

int base64encode(char* instr, int len, char* outstr)
{
	int i = 0;
	int j = 0;
	unsigned char a1, a2, a3;
	unsigned char b1, b2, b3, b4;
	for (int i = 0; i < len; i += 3)
	{
		a1 = a2 = a3 = 0;
		a1 = instr[i];
		if (i + 1 < len) a2 = instr[i + 1];
		if (i + 2 < len) a3 = instr[i + 2];

		b1 = a1 >> 2;
		b2 = ((a1 & 0x3) << 4) | (a2 >> 4);
		b3 = ((a2 & 0xf) << 2) | (a3 >> 6);
		b4 = a3 & 0x3f;

		outstr[j++] = base64char(b1);
		outstr[j++] = base64char(b2);
		outstr[j++] = (i + 1 < len) ? base64char(b3) : '=';
		outstr[j++] = (i + 2 < len) ? base64char(b4) : '=';
	}
	return j;

}

int base64decode(char* instr, int len, char* outstr)
{
	int i = 0;
	int j = 0;
	unsigned char a1, a2, a3, a4;
	unsigned char b1, b2, b3;
	int l = len;
	static const std::string base64_char =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	while (l-- && (instr[i] != '=') &&
		(isalnum(instr[i])||(instr[i] == '+')||(instr[i] == '/')))//isalnum - "1" если элемента буква или цифра
	{
		a1 = a2 = a3 = a4 = 0;
		a1 = instr[i];
		if (i + 1 < len) a2 = instr[i + 1];
		if (i + 2 < len) a3 = instr[i + 2];
		if (i + 3 < len) a4 = instr[i + 3];

		a1 = base64_char.find(a1);// возвращает индекс элемента в строке, который нашелся первым
		a2 = base64_char.find(a2);
		a3 = base64_char.find(a3);
		a4 = base64_char.find(a4);

		b1 = (a1 << 2) | ((a2 & 0x30) >> 4);
		b2 = ((a2 & 0xf) << 4) | ((a3 & 0x3c) >> 2);
		b3 = ((a3 & 0x3) << 6) | a4;

		outstr[j++] = b1;
		outstr[j++] = b2;
		outstr[j++] = b3;
		i += 4;
		
	}
	return j;

}
//int main()
//{
//	
//	char in2[] = "bGtna2Zqc2xmYWJjdg==";
//	char out[128];
//	
//	std::cout << in2 << std::endl;
//	int s = base64decode(in2, strlen(in2), out);
//	
//	std::cout << out << std::endl;
//	return 0;
//
//}
void izmeneniye_simvola_na_kolichestvo_povtoreniy(const std::string& file ) {
	std::fstream inFile;
	inFile.open("text.txt", std::ios::in | std::ios::out);
	int ch;
	unsigned int A[255] = { 0, };
	while (inFile.peek() != EOF) {
		ch = inFile.get();
		A[int(ch)]++;
		//  std::cout << A[ch];
		inFile.seekg(-1, std::ios::cur);
		inFile << A[int(ch)];
		inFile.seekp(inFile.tellg(), std::ios::beg);
		// inFile.seekg(+1, ios::cur);
	}
	inFile.close();
	system("pause");
}
//#include <iostream>
//#include <fstream>
//using namespace std;
//
//int main(int argc, char* argv[]) {
//	fstream inFile;
//	inFile.open("text.txt", std::ios::in | std::ios::out);
//	int ch;
//	unsigned int A[255] = { 0, };
//	while (inFile.peek() != EOF) {
//		ch = inFile.get();
//		A[int(ch)]++;
//		//  std::cout << A[ch];
//		inFile.seekg(-1, ios::cur);
//		inFile << A[int(ch)];
//		inFile.seekp(inFile.tellg(), ios::beg);
//		// inFile.seekg(+1, ios::cur);
//	}
//	inFile.close();
//	system("pause");
//	return 0;
//}



void print(int A[], size_t n) {
	for (int i = 0; i < n; i++) {
		std::cout << A[i] << "  ";
	}
	std::cout << std::endl;
}

void Random(int A[], size_t n) {
	srand(unsigned(time(NULL)));
	for (int i = 0; i < n; i++) {
		A[i] = rand() % 90 + 10;
	}
}

template <typename T>
void Bubble(T* M, size_t n)
{
	/*Random(M, n);
	print(M, n);*/
	for (size_t j = 0; j < n - 1; ++j)
	{
		for (size_t i = n - 1;i > j;--i)
		{
			if (M[i] < M[i - 1]) std::swap(M[i], M[i - 1]);
		}
	}
	/*print(M, n);*/
}

template <typename T>
void ChooseSort(T* M, size_t n)
{
	/*Random(M, n);
	print(M, n);*/
	for (size_t j = 0; j < n - 1; ++j)
	{
		size_t k = j;
		for (size_t i = k + 1;i < n;++i)
			if (M[i] < M[k]) k = i;
		if (k != j) std::swap(M[k], M[j]);
	}
	/*print(M, n);*/
}
template <typename T>
void InsertSort(T* M, size_t n)
{
	/*Random(M, n);
	print(M, n);*/
	T tmp;
	for (size_t j = 1; j < n;++j)
	{
		int left = 0, right = j;
	    int mid;
		do
		{
			mid = left + (right - left) / 2;
			if (M[mid] > M[j])right = mid - 1;else left = mid + 1;
		} while (left < right);
		if (right >= 0)
		{
			if (M[j] < M[right])--right;
		}
		if (j != right)
		{
			tmp = M[j];
			for (int i = j;i > right + 1;--i)
				M[i] = M[i - 1];
			M[right + 1] = tmp;
		}
	}
	/*print(M, n);*/
}
template <typename T>
void QuicksortRec(T* M, size_t n)
{

	int left = 0;
	int right = n - 1;
	int pindex = left+(right - left) / 2;
	T p = M[pindex];
	int i = left, j = right;
	while (i < j) 
	{
		while (M[i] < p)++i;
		while (M[j] > p)--j;
		if (i<j)
		{
			std::swap(M[i], M[j]);++i; --j;
		}
		else if (i == j) { ++i;--j; }
	}
	if (pindex < i)
	{
		if (i < right) { QuicksortRec(M + i, n - i); }
		if (j>left){ QuicksortRec(M, j+1); }
	}
	else
	
	{
		if (j > left) { QuicksortRec(M, j + 1); }
		if (i < right) { QuicksortRec(M + i, n - i); }
	}
	
}
template <typename T>
void MergeSort(T* M, size_t n)
{
	/*Random(M, n);
	print(M, n);*/
	T* tmp = new T[n];
	T* from = M;
	T* to = tmp;
	for (int step = 1;step < n;step *= 2)
	{
		int start1, end1, start2, end2;
		int ind = 0;
		for (int start = 0;start < n;start += 2 * step)
		{
			start1 = start;end1 = start1 + step;end1 = (end1 < n) ? end1 : n;
			start2 = end1;end2 = start2 + step;end2 = (end2 < n) ? end2 : n;
			while (start1 < end1 && start2 < end2)
			{
				to[ind++] = (from[start1] < from[start2]) ? from[start1++] : from[start2++];
			}
			while (start1 < end1) { to[ind++] = from[start1++]; }//перекидываем оставшиеся элементы
			while (start2 < end2) { to[ind++] = from[start2++]; }
		}
		std::swap(from, to);
	}
	if (from != M)//перекидываем отсортированную последовательность в исходный файл
	{
		int i = 0;
		while (i < n) { M[i] = tmp[i];++i; }
	}
	delete[]tmp;
	/*print(M, n);*/
}
template <typename T>
void Heapsort(T* M, size_t n)
{
	/*Random(M, n);
	print(M, n);*/
	for (size_t i = 1;i < n;++i) //делаем кучу
	{
		size_t pos = i;
		while (pos != 0)
		{
			size_t parent = (pos - 1) / 2;
			if (M[parent] < M[pos])
			{
				std::swap(M[parent], M[pos]);
				pos = parent;
			}
			else break;
		}
	}
	size_t size = n;
	for (size_t i = 1;i < n;++i)//разбираем кучу
	{
		if (M[size - 1] < M[0])
		{
			std::swap(M[0], M[size - 1]);
		}
		--size;
		size_t pos = 0;

		while (2 * pos + 1 < size)//пока есть хоят бы один потомок
		{
			size_t posmaxchild = 2 * pos + 1;
			if (posmaxchild + 1 < size) { if (M[posmaxchild] < M[posmaxchild + 1]) ++posmaxchild; }//есть ли потомок справа
			if (M[pos] < M[posmaxchild])
			{
				std::swap(M[pos], M[posmaxchild]);
				pos = posmaxchild;
			}
			else break;
		}
		/*print(M, n);*/
	}
}

template <typename T>
void RadixSort(T* M, size_t n)
{
	/*Random(M, n);
	print(M, n);*/
	if (n < 2) return;
	unsigned int* tmp = new unsigned int[n];
	unsigned int mask = 1;
	while (mask)
	{
		int cnt1 = 0;
		cnt1 = (M[0] & mask) ? 0 : 1;
		for (int j = 1;j < n;++j)
		{
			if (!(M[j] & mask))
			{
				if (j > cnt1)
				{
					unsigned int tmp = M[j];//записываем в tmp то число, которое мы двигаем
					for (int k = j;k > cnt1;--k)M[k] = M[k - 1];
					M[cnt1] = tmp;
				}
				++cnt1;//если элемент оказался нулевым
			}
		}
		mask <<= 1;
	}
	/*print(M, n);*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//integral

//#include <cmath>
//#include <iostream>




//void integral(std::string data, long double ll, long double rl)
//{
//
//
//std::ifstream file;
//file.open(data);
//if (!file) {
//	std::cout << "no data" << std::endl;
//}
//	/*std::string str;
//	std::getline(file, str);*/
//	std::string* str = new std::string;
//	std::getline(file, *str);
//	
//
//	long double dr = (rl - ll) / 1000.;
//	long double S = RRect_Solve(ll, rl, dr,str);
//	std::cout << "== rightRect ==" << std::endl << S << std::endl;
//
//	S = lRect_Solve(ll, rl, dr,str);
//	std::cout << "== leftRect ==" << std::endl << S << std::endl;
//
//
//	S = Trap_Solve(ll, rl, dr,str);
//	std::cout << "== Trap ==" << std::endl << S << std::endl;
//
//	S = Monte_Solve(ll, rl, dr,str);
//	std::cout << "== Monte-Carlo ==" << std::endl << S << std::endl;
//	file.close();
//}




//long double func_y(long double  x, std::string* str)
//{
//	std::string strcopy = *str;
//	std::string per;
//	std::string per(long double x);
//	strcopy.replace(strcopy.find("x"), 1, per);
//
//	std::string srpn = RPN(strcopy);
//	RPNSolver a;
//	
//	return(a.solve(srpn));
//}


//-------------------------------------------------------------------------------------------------------------------------------------------------------
std::string RPN(std::string str)// создаёт ОПЗ из строки
{
	std::string srpn;

	std::string::size_type ind;
	while ((ind = str.find(' ')) != std::string::npos) // удаление пробелов из входной строки
	{
		str.erase(ind, 1);
	}

	for (int i = 0; i < str.size(); ++i) // учёт отрицательных чисел
	{
		if ((str[i] == '+' || str[i] == '-') && (0 == i || (!isalnum(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != ')')))
		{
			auto it = std::find_if(str.begin() + i + 1, str.end(), [](char const c) {return !isalnum(c);});
			str.insert(it, ')');
			str.insert(i, "(0");
			int nnn = 0;
		}
	}

	/*std::cout << str << std::endl;*/

	std::map<char, size_t> map; // карта весов символов

	map.insert(std::make_pair('c', 4));
	map.insert(std::make_pair('l', 4));
	map.insert(std::make_pair('^', 4));
	map.insert(std::make_pair('s', 4));
	map.insert(std::make_pair('*', 3));
	map.insert(std::make_pair('/', 3));
	map.insert(std::make_pair('+', 2));
	map.insert(std::make_pair('-', 2));
	map.insert(std::make_pair('(', 1));
	std::stack<char> stack;
	for (auto c : str) // формировка результирующей строки в ОПЗ
	{
		if ((!isalnum(c) || c=='c' || c == 'l' || c == '^' || c == 's') && ('.' != c))
		{
			srpn += ' ';
			if (')' == c)
			{
				while (stack.top() != '(')
				{
					srpn += stack.top();
					stack.pop();
					srpn += ' ';
				}
				stack.pop();
			}
			else if ('(' == c)
			{
				stack.push(c);
			}
			else if (stack.empty() || (map[stack.top()] < map[c]))
			{
				stack.push(c);
			}
			else
			{
				do
				{
					
					srpn += stack.top();
					srpn += ' ';
					stack.pop();
				} while (!(stack.empty() || (map[stack.top()] < map[c])));
				stack.push(c);
			}
		}
		else
		{
			srpn += c;
		}
	}
	while (!stack.empty())// остаток из стека добавляется в результ. строку
	{
		srpn += ' ';//!
		srpn += stack.top();
		/*srpn += ' ';*/
		stack.pop();
	}
	/*std::cout << srpn << std::endl; */// результирующая строка в ОПЗ

	return srpn;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------
class RPNSolver
{
public:
	RPNSolver() {}

	  double solve(const std::string& expr)
	{
		std::stack< double > stk; // values stack
		int pos = 0; // first symbol's position of current expression (they are divided by whitespace)
		std::string curVal;
		int sz = expr.size();
		while (pos != sz)
		{
			curVal = this->getNextValue(expr, pos);
			if (/*isNum(curVal)*/(curVal != "l") && (curVal != "s") && (curVal != "c") && (curVal != "^") && (curVal != "+") && (curVal != "-") && (curVal != "*") && (curVal != "/") && (curVal != "(") && (curVal != ")") && (curVal != " ") && (curVal != ""))
			{
				double value = atof(curVal.c_str());
				/*std::cout << value;*/
				stk.push(value);
				
			}
			else
				if ((curVal != " ") && (curVal != "")) {
					stk.push(this->calculate(stk, curVal));
				}
		}
		/*std::cout <<" "<< stk.top()<<std::endl;*/
		return stk.top();
	}

	std::string getNextValue(const std::string& expr, int& pos)
	{
		int posStart = pos;
		int sz = expr.size();
		while ((expr[pos++] != ' ') && (pos != expr.size()))
		{
		}

		int count = (pos != sz) ? pos - posStart - 1 : pos - posStart;
		return expr.substr(posStart, count);
	}

	bool isNum(const std::string& value)
	{
		return value[0] >= 48 && value[0] <= 57; // ascii(48) = '0', ascii(57) = '0'
	}

	double calculate(std::stack< double >& stk, const std::string& oper)
	{
		double res = stk.top();
		stk.pop();

		/*while (!stk.empty())
		{*/
			if (oper[0] == '+') {
				/*std::cout << res << " ";
				std::cout << stk.top() << " ";*/
				res = res + stk.top();
				/*std::cout << res << " ";*/
			}//!
			else if (oper[0] == '-') 
			{
				res = stk.top()-res;
				/*std::cout << res << " ";*/
			}
			else if (oper[0] == '*')
				res *= stk.top();
			else if (oper[0] == '/')
			{
				res = double(stk.top())/double(res) ;
				/*std::cout << res << " ";*/
			}
			else if (oper[0] == '^')
				res = pow(stk.top(),res );
			else if (oper[0] == 'l')
				res = log(stk.top())/log(res);
			else if (oper[0] == 's')
			{
				/*std::cout << res << " ";
				std::cout << stk.top() << " ";*/
				res = pow(sin(res), stk.top());//!
				/*std::cout << res << " ";*/
			}
			else if (oper[0] == 'c') {
				res = pow(cos(res), stk.top());
				/*std::cout << res << " ";*/
			}
			else
				return 0;

			stk.pop();
		/*}*/

		return res;
	}
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------
std::string LDToStr(long double one)
{
	std::stringstream ss;
	ss << one;
	return ss.str();
}

long double func_y(long double  x, std::string* str)
{
	std::string strcopy = *str;
	int kolper=0;
	for (int i = 0; i<strcopy.length();++i)
	{
		if (strcopy[i] == 'x') ++kolper;
	}
	for (int i = 1;i <= kolper;++i) 
	{
		strcopy.replace(strcopy.find("x"), 1, LDToStr(x));
	}

	std::string srpn = RPN(strcopy);
	RPNSolver a;

	return(a.solve(srpn));
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------

long double RRect_Solve(long double a, long double b, long double dx, std::string* str)
{
	if (a > b)
	{
		return 0;
	}
	long double x = a;
	long double S = 0.0;
	/*while (x+dx <= b)*/for (int i = 0;i < 1000;++i)
	{

		/* S = S+ (dx * (func_y(x + dx)));*/
		S = S + func_y(x + dx,str);

		/*std::cout << func_y(x + dx, str);*/

		x = dx + x;

	}
	S = S * dx;
	return S;
}
long double lRect_Solve(long double a, long double b, long double dx, std::string* str)
{
	if (a > b)
	{
		return 0;
	}
	long double x = a;
	long double S = 0.0;
	/*while (x <= b)*/for (int i = 0;i < 1000;++i)
	{
		S = S + func_y(x,str);
		x = x + dx;
	}
	S = S * dx;
	return S;
}

long double Trap_Solve(long double a, long double b, long double dx, std::string* str)
{
	if (a > b)
	{
		return 0;
	}
	long double x = a;
	long double S = 0.0;
	/*while (x + dx <b)*/for (int i = 0;i < 1000;++i)
	{
		S = S + (func_y(x,str) + func_y(x + dx,str)) / 2.;
		x += dx;
	}
	S = S * dx;
	return S;
}
long double Monte_Solve(long double a, long double b, long double dx, std::string* str)
{
	if (a > b)
	{
		return 0;
	}
	long double x = a;
	long double max = abs(func_y(x,str));
	for (int i = 0;i < 1000;++i)
	{
		x += dx;
		if (abs(func_y(x,str)) > max) { max = abs(func_y(x,str)); }

	}
	long double ot = 0., npt = 0.;
	long double nott = 0.;
	long double s;
	long double dy;
	x = a;
	for (int i = 0;i < 1000;++i)
	{
		dy = 0.;
		while (dy <= max)
		{
			if (dy <= abs(func_y(x,str))) { if (func_y(x,str) > 0) { ++npt; } else { ++nott; }++ot; }
			else { ++ot; }
			dy += max / 100;
		}
		x += dx;
	}
	s = (npt / ot) * ((b - a) * max) - (nott / ot) * ((b - a) * max);
	return s;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
long double Right_difference(long double x, std::string* str)
{
	long double S = (func_y(x+0.0001, str)- func_y(x, str))/0.0001;
	return (S);

}
long double Left_difference(long double x, std::string* str)
{
	long double S = (func_y(x, str) - func_y(x - 0.0001, str)) / 0.0001;
	return (S);

}
long double Central_difference(long double x, std::string* str)
{
	long double S = (func_y(x+0.0001, str) - func_y(x - 0.0001, str)) / 0.0002;
	return (S);

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------
long double Vilka_kor(long double a, long double b, std::string* str)
{
	long double x=(a+b)/2.;
	while (((func_y(x, str)) > 0.001)||((func_y(x, str)) <- 0.001))
	{
		if (func_y(x, str) <= 0) a = x;
		else b = x;
		x = (a + b) / 2.;
		if (((func_y(a, str)) < 0.0001) && ((func_y(a, str)) > -0.0001)) return a;
		if (((func_y(b, str)) < 0.0001) && ((func_y(b, str)) > -0.0001)) return b;
	}
	return x;
}
long double Horda_kor(long double a, long double b, std::string* str)
{
	long double x = (a*func_y(b,str) - b*func_y(a,str))/(func_y(b, str)- func_y(a, str));
	while (((func_y(x, str)) > 0.001) || ((func_y(x, str)) < -0.001))
	{
		if (func_y(x, str) <= 0) a = x;
		else b = x;
		x = (a * func_y(b, str) - b * func_y(a, str)) / (func_y(b, str) - func_y(a, str));
		if (((func_y(a, str)) < 0.0001) && ((func_y(a, str)) > -0.0001)) return a;
		if (((func_y(b, str)) < 0.0001) && ((func_y(b, str)) > -0.0001)) return b;
	}
	return x;
}
long double Newton_kor(long double a, long double b, std::string* str)
{
	long double x = (a * func_y(b, str) - b * func_y(a, str)) / (func_y(b, str) - func_y(a, str));
	while (((a-b) > 0.001) || ((a - b) < -0.001))
	{
		if (func_y(x, str) <= 0) a = x;
		else b = x;
		x = (a * func_y(b, str) - b * func_y(a, str)) / (func_y(b, str) - func_y(a, str));
		if (((func_y(a, str)) < 0.0001) && ((func_y(a, str)) > -0.0001)) return a;
		if (((func_y(b, str)) < 0.0001) && ((func_y(b, str)) > -0.0001)) return b;
	}
	x = a + (b - a) / 2;
	while (((func_y(x, str)) > 0.001) || ((func_y(x, str)) < -0.001))
	{
		long double pr = Right_difference(x, str);
		x = x - (func_y(x, str) / pr);
	}
	return x;


}

//-------------------------------------------------------------------------------------------------------------------------------------------------------
void Norm_func(long double a, long double b, long double dx, std::string* str)
{
	long double Int = RRect_Solve(a, b, dx, str);
	std::cout << "1/" << Int << " * (" << *str << ")" << std::endl;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------

void integral(std::string data, long double ll, long double rl)
{


	std::ifstream file;
	file.open(data);
	if (!file) {
		std::cout << "no data" << std::endl;
	}
	/*std::string str;
	std::getline(file, str);*/
	std::string* str = new std::string;
	std::getline(file, *str);


	long double dr = (rl - ll) / 1000.;
	long double S = RRect_Solve(ll, rl, dr, str);
	std::cout << "== rightRect ==" << std::endl << S << std::endl;

	S = lRect_Solve(ll, rl, dr, str);
	std::cout << "== leftRect ==" << std::endl << S << std::endl;


	S = Trap_Solve(ll, rl, dr, str);
	std::cout << "== Trap ==" << std::endl << S << std::endl;

	S = Monte_Solve(ll, rl, dr, str);
	std::cout << "== Monte-Carlo ==" << std::endl << S << std::endl;
	file.close();
}




void differentiation(std::string data, long double x)
{

	std::ifstream file;
	file.open(data);
	if (!file) {
		std::cout << "no data" << std::endl;
	}
	
	std::string* str = new std::string;
	std::getline(file, *str);

	long double Proizvod = Right_difference(x,str);
	std::cout << "== Right_difference ==" << std::endl << Proizvod << std::endl;
	Proizvod = Left_difference(x, str);
	std::cout << "== Left_difference ==" << std::endl << Proizvod << std::endl;
	Proizvod = Central_difference(x, str);
	std::cout << "== Central_difference ==" << std::endl << Proizvod << std::endl;
	file.close();
}

void nayti_koren(std::string data, long double ll, long double rl)
{

	std::ifstream file;
	file.open(data);
	if (!file) {
		std::cout << "no data" << std::endl;
	}

	std::string* str = new std::string;
	std::getline(file, *str);
	long double ZnachKoren = Vilka_kor(ll,rl,str);
	std::cout << "== Vilka_kor ==" << std::endl << ZnachKoren << std::endl;
	ZnachKoren = Horda_kor(ll, rl, str);
	std::cout << "== Horda_kor ==" << std::endl << ZnachKoren << std::endl;
	ZnachKoren = Newton_kor(ll, rl, str);
	std::cout << "== Newton_kor ==" << std::endl << ZnachKoren << std::endl;
	file.close();
}


void Normirovanie(std::string data, long double ll, long double rl)
{
	std::ifstream file;
	file.open(data);
	if (!file) {
		std::cout << "no data" << std::endl;
	}

	std::string* str = new std::string;
	std::getline(file, *str);


	long double dr = (rl - ll) / 1000.;
	Norm_func(ll, rl, dr, str);
	file.close();
}














//int main()
//{
//	long double ll, rl;
//	std::cin >> ll >> rl;
//	long double dr = (rl - ll) / 1000.;
//	long double S = RRect_Solve(ll, rl, dr);
//	std::cout << "== rightRect ==" << std::endl << S << std::endl;
//
//	S = lRect_Solve(ll, rl, dr);
//	std::cout << "== leftRect ==" << std::endl << S << std::endl;
//
//
//	S = Trap_Solve(ll, rl, dr);
//	std::cout << "== Trap ==" << std::endl << S << std::endl;
//
//	S = Monte_Solve(ll, rl, dr);
//	std::cout << "== Monte-Carlo ==" << std::endl << S << std::endl;
//
//	/* for (int i = 0;i < 50;++i) {
//		 cout << func_y(i)<<"   ";
//	 }*/
//
//	return 0;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//sortyrovka po vozrusty
//int main()
//{
//	std::ifstream infile;
//	infile.open("d.txt");
//	if (!infile) {
//		std::cout << "can not open infile" << std::endl;
//		return 1;
//	}
//	std::ofstream out;
//	out.open("z.txt");
//	if (!out) {
//		std::cout << "can not open outfile" << std::endl;
//		return 1;
//	}
//	std::string name[100];
//	int v[100];
//	for (int j = 0;j < 100;++j) { v[j] = 10000000;name[j] = "-"; }
//	std::string str;
//	int i = 0;
//	while (!infile.eof())
//
//	{
//		name[i] = "";
//		str = "";
//		infile >> str;
//		name[i] += str;
//		name[i] += "  ";
//		infile >> str;
//		name[i] += str;
//		infile >> str;
//		for (int j = 0;j < str.length();++j)
//		{
//			if (str[j] == '.') str.erase(j, 1);
//			if (str[j] == '\n') str.erase(j, 1);
//
//		}
//		v[i] = stoi(str);
//		int y = v[i] % 10000;
//		int m = ((v[i] - y) % 1000000) / 10000;
//		int d = ((v[i] - y - m) % 100000000) / 1000000;
//		v[i] = 367 * 2020 - ((7 * (2020 + (11 + 9) / 12)) / 4) + (275 * 11) / 9 + 24 - 730530;
//		v[i] = v[i] - (367 * y - ((7 * (y + (m + 9) / 12)) / 4) + (275 * m) / 9 + d - 730530);
//		++i;
//	}
//	int min = v[0];
//	int nom = 0;
//	for (int j = 0; j < i; ++j)
//	{
//		if (v[i] < min)
//		{
//			nom = i;
//		}
//	}
//	out << "возраст = " << v[nom] << " дней" << ' ' << "(=" << v[nom] / 365 << " год)" << "  " << name[nom] << '\n';
//	v[nom] = 1000000;
//
//	for (int j = 1; j < i; ++j) {
//		min = 1000000;
//		for (int k = 0; k < i; ++k)
//		{
//			if (v[k] < min)
//			{
//				nom = k;min = v[k];
//			}
//		}out << "возраст = " << v[nom] << " дней" << ' ' << "(=" << v[nom] / 365 << " год)" << "  " << name[nom] << '\n';
//		v[nom] = 10000000;
//	}
//
//
//	out.close();
//	infile.close();
//
//	return 0;
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		









	