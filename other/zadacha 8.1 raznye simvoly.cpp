
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
	char s[100];
	int ps[100];
	int k = -1;
	for (int i = 0;i < 100;++i)
	{
		s[i] = '@'; ps[i] = 1;
	}
	char ch;
	bool prov;
	bool nal;
	std::string str="";
	std::string rezstr = "";
	int maxdl=0;
	int nom;
	while ((ch = infile.get()) != EOF) {
		nal = 1;
		for (int i = 0;i < str.length();++i) {
			if (ch == str[i]) { nal = 0;nom = i; }
		}
		if (nal == 1)
		{
			str += ch;
		}
		else
		{
			if (str.length() > maxdl)
			{
				maxdl = str.length();
				rezstr = str;
			}
			str += ch;
			str.erase(0, k+1);
		}
		prov = 1;
		for (int i = 0;i < 100;++i)
		{
			if (s[i] == ch) {
				prov = 0;
				++ps[i];
			}
		}
		if (prov == 1)
		{
			 k = -1;
			for (int i = 0;i < 100;++i)
			{
				if (s[i] == '@') {
					k = i;
					break;
				}
			}
			s[k] = ch;
		}
	}
	for (int i = 0;i < 100;++i)
	{
		if (s[i] == '@') {
			k = i;
			break;
		}
	}
	for (int i = 0;i < k;++i)
	{
		std::cout << s[i] << ' '<<ps[i]<< std::endl;
		
	}
	std::cout << rezstr;
	out.close();
	infile.close();
	return 1;
}
				
