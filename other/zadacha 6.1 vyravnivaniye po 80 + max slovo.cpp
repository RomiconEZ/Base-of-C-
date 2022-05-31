#include <string>
#include <iostream>
#include <fstream>

//#include <Windows.h>

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



	int dl;
	int maxdl = 0;
	int dlstr;
	std::string str;
	std::string maxsl;
	std::string strp = "";
	dlstr = 0;
	int pr;
	int kol = 0;
	int nom = 0;
	while (!infile.eof())

	{
		str = "";
		infile >> str;
		dl = str.length();
		int pl = 2;
		if (dlstr + dl <= 79) {

			strp += str;
			strp += ' ';
			/*out << str << ' ';*/
			dlstr = dl + dlstr + 1;
		}
		else {
			for (int i = dlstr - 1;i > 0;--i) { if (strp[i] == ' ') { strp.erase(i, 1); break; } }
			--dlstr;
			pl = 2;
			for (int i = 0;i <= (79 - dlstr - 1);++i) {
				for (int j = nom;j < strp.length();++j)
				{
					if (strp[j] == ' ') {
						strp.insert(j, " ");
						nom = j + pl;
						break;
					}
					if (j >= strp.length() - 2)
					{
						nom = 0; ++pl;
					}


				}
			}
			if (strp.length() < 79) {
				for (int j = 0;j < strp.length();++j) {
					if (strp[j] == ' ') { strp.insert(j, " "); break; }
				}
			}
			nom = 0;
			out << strp << '\n';
			strp = "";
			strp += str;
			strp += ' ';
			dlstr = dl + 1;
		}

		for (int i = 0;i <= dl;++i) {
			if ((str[i] == ' ') || (str[i] == '.') || (str[i] == ',') || (str[i] == '"') || (str[i] == '?') || (str[i] == '!') || (str[i] == '\n')) {
				--dl;
				str.erase(i, 1);
			}
		}
		if (dl > maxdl) {
			//for (int i = 0;i <= dl;++i)
			//{

			maxsl = str;
			maxdl = dl;
			//}
			kol = 0;

		}
		pr = 1;
		for (int i = 0;i < dl;++i)
		{
			if (str[i] != maxsl[i]) {
				pr = 0;
			}
		}
		if (pr == 1) {
			++kol;
		}

	}
	out << std::endl << maxsl << std::endl << maxdl << std::endl << kol;

	out.close();
	infile.close();

	return 0;
}

