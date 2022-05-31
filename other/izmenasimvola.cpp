#include <iostream>
#include <fstream>
#include <string>


//int main(int argc, char* argv[]) {
//    fstream inFile;
//    inFile.open("text.txt", std::ios::in | std::ios::out);
//    int ch;
//    unsigned int A[255] = { 0, };
//    while (inFile.peek() != EOF) {
//        ch = inFile.get();
//        A[int(ch)]++;
//        //  std::cout << A[ch];
//        inFile.seekg(-1, ios::cur);
//        inFile << A[int(ch)];
//        inFile.seekp(inFile.tellg(), ios::beg);
//        // inFile.seekg(+1, ios::cur);
//    }
//    inFile.close();
//    system("pause");
//    return 0;
//}
int main(int argc, char* argv[3]) 
{
	std::fstream inFile;
	std::ifstream infile;
	infile.open(argv[1]);
	std::ofstream outfile;
	outfile.open(argv[2]);
	std::string a, b;
	char* c = new char[1024];
	a = "";
	b = "";
	for (int i = 0;i <= 1023;++i)c[i] = '0';
	std::getline(infile, a);
	std::getline(infile, b);
	int lena = a.length();
	int lenb = b.length();
	
	int i = lena-1, j = lenb-1;
	int ost = 0;
	int ai;
		int bi;
		int ci;
		int k = 0;
	while ((i >= 0) && (j >= 0))
	{
		ai = a[i] - '0';
		bi = b[j] - '0';
		ci = ai + bi + ost;
		ost = ci / 10;
		ci = ci % 10;
		c[k]=(ci+'0');
	  
		--i;--j;++k;
	}
	
	while (i >= 0)
	{
		ai = a[i--] - '0';
		ci = ai + ost;
		ost = ci / 10;
		ci = ci % 10;
		c[k] = (ci + '0');
		++k;
	
		
	}
	while (j >= 0)
	{
		bi = b[j--] - '0';
		ci = bi + ost;
		ost = ci / 10;
		ci = ci % 10;
		c[k] = (ci + '0');
		++k;
	}
	if (ost != 0)
	{
		c[k] = (ost + '0');
		
	}
	for(i=k-1;i>=0;--i)
	{
		outfile << c[i];
	}

	infile.close();
	outfile.close();
	delete[]c;
	return 0;
}

//#include <iostream>
//#include <fstream>
//#include "string.h"
//int main(int argc, char* argv[]) {
//	std::fstream inFile;
//	inFile.open(argv[1]);
//	char ch;
//	std::string s1, s2;
//	getline(inFile, s1);
//	getline(inFile, s2);
//	int i = 1;
//	int j = 0;
//	int k1 = s1.length() - 1;
//	int k2 = s2.length() - 1;
//	int k;
//	if (k1 > k2) k = k1;
//	else k = k2;
//	int a1 = 0, a2 = 0;
//	for (k1; k1 >= 0; k1--) {
//		if (s1[k1] == '1') {
//			a1 += 1 * i;
//		}
//		i *= 2;
//	}
//	// std::cout « k1 «" ";
//	i = 1;
//	for (k2 - 1; k2 >= 0; k2--) {
//		if (s2[k2] == '1') {
//			a2 += 1 * i;
//		}
//		i *= 2;
//	}
//
//	std::string s = "";
//	int sum = (a1 + a2);
//	inFile.seekg(0, std::ios::end);
//	inFile « '\n';
//	while (sum) {
//		;
//		if ((sum % 2) == 1) s += '1';
//		else s += '0';
//		sum = sum / 2;
//	}
//	std::string s_r = "";
//	for (int i = 1; i <= s.length(); i++) {
//		inFile « s[s.length() - i];
//
//	}
//	inFile « s_r;
//	inFile.close();
//	return 0;
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <iostream>
//using namespace std;
//
//union bytecode
//{
//	unsigned char X;
//	struct {
//		unsigned char a0 : 1;
//		unsigned char a1 : 1;
//		unsigned char a2 : 1;
//		unsigned char a3 : 1;
//		unsigned char a4 : 1;
//		unsigned char a5 : 1;
//		unsigned char a6 : 1;
//		unsigned char a7 : 1;
//	} byte;
//};
//
//union ipAddr
//{
//	unsigned int ip;
//	unsigned char bytes[4];
//	bytecode oneByte[4];
//};
//
//
//int main() {
//	ipAddr Myaddr;
//	Myaddr.bytes[0] = 192;
//	Myaddr.bytes[1] = 168;
//	Myaddr.bytes[2] = 0;
//	Myaddr.bytes[3] = 64;
//	for (size_t i = 0; i < 4; i++)
//	{
//		cout << (int)Myaddr.bytes[i] << " | ";
//	}
//	cout << endl;
//	for (int i = 0; i < 4; ++i) {
//		cout << (int)Myaddr.oneByte[i].byte.a0;
//		cout << (int)Myaddr.oneByte[i].byte.a1;
//		cout << (int)Myaddr.oneByte[i].byte.a2;
//		cout << (int)Myaddr.oneByte[i].byte.a3;
//		cout << (int)Myaddr.oneByte[i].byte.a4;
//		cout << (int)Myaddr.oneByte[i].byte.a5;
//		cout << (int)Myaddr.oneByte[i].byte.a6;
//		cout << (int)Myaddr.oneByte[i].byte.a7;
//		cout << " | ";
//	}
//
//
//	return 0;
//}