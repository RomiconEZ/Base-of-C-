#include <iostream>
#include <fstream>
#include "function.h"

int menu() {
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "1.sortirovka po alfavitu" << std::endl;
	std::cout << "2.base64_encode " << std::endl;
	std::cout << "3.base64_decode  " << std::endl;
	std::cout << "4.izmeneniye_simvola_na_kolichestvo_povtoreniy" << std::endl;
	std::cout << "5.sort " << std::endl;
	std::cout << "6.integral " << std::endl;
	std::cout << "7.differentiation  " << std::endl;
	std::cout << "8.nayti koren" << std::endl;
	std::cout << "9.normirovaniye funktsii " << std::endl;
	std::cout << "0. Exit" << std::endl;
	int action;
	std::cin >> action;
	std::cin.ignore();
	return action;
}

int main() {
	/*setlocale(LC_ALL, "Russian");*/
	int action;
	
	char buf[32];
	do {
		action = menu();
		try {
			switch (action) {
			case 1: 
			{std::cout << "file" << std::endl;
			std::string data; std::cin >> data;
			std::cout << "Введите имя записываемого файла" << std::endl;
			std::string zap;std::cin >> zap;
			std::cout << "Введите количество элементов" << std::endl;
			int kolvo;std::cin >> kolvo;
			sortirovka_po_alfavitu(data, zap, kolvo);
			break;}
			
			case 2: 
			{
				char in[128];
				std::cout << "Введите кодируемую строку" << std::endl;
				std::cin >> in;
				char out[128];
				int s = base64encode(in, strlen(in), out);
				out[s] = '\0';
				std::cout << out << std::endl;
				break;
			}
			case 3:
			{
				char in[128];
				std::cout << "Введите декодируемую строку" << std::endl;
				std::cin >> in;
				char out[128];
				int s = base64decode(in, strlen(in), out);
				out[s] = '\0';
				std::cout << out << std::endl;
				break;
			}
			case 4:
			{std::string nameoffile;
			std::cout << "Введите имя файла" << std::endl;
			std::cin >> nameoffile;
			izmeneniye_simvola_na_kolichestvo_povtoreniy(nameoffile);
			break;
			}
			case 5:
			{
				size_t n;
				std::cout << "input size  "; std::cin >> n;
				int* A = new int[n];
				Random(A, n);
				print(A, n);
				Bubble(A, n);
				print(A, n);
				std::cout << std::endl;

				Random(A, n);
				print(A, n);
				ChooseSort(A, n);
				print(A, n);

				std::cout << std::endl;
				Random(A, n);
				print(A, n);
				InsertSort(A, n);
				print(A, n);

				std::cout << std::endl;

				Random(A, n);
				print(A, n);
				QuicksortRec(A, n);
				print(A, n);

				std::cout << std::endl;

				Random(A, n);
				print(A, n);
				MergeSort(A, n);
				print(A, n);

				std::cout << std::endl;
				
				Random(A, n);
				print(A, n);
				Heapsort(A, n);
				print(A, n);

				std::cout << std::endl;

				Random(A, n);
				print(A, n);
				RadixSort(A, n);
				print(A, n);

				std::cout << std::endl;
				break;}
			case 6:
			{
				/*std::cout << "Введите имя файла" << std::endl;
				std::string data; std::cin >> data;
					std::fstream file;
					file.open(data);

					if (!file) {
						std::cout << "no data" << std::endl;
				long double ll, rl;
				std::cout << "Введите границы интегрирования" << std::endl;
				std::cin >> ll >> rl;
				long double dr = (rl - ll) / 1000.;
				long double S = RRect_Solve(ll, rl, dr);
				std::cout << "== rightRect ==" << std::endl << S << std::endl;

				S = lRect_Solve(ll, rl, dr);
				std::cout << "== leftRect ==" << std::endl << S << std::endl;


				S = Trap_Solve(ll, rl, dr);
				std::cout << "== Trap ==" << std::endl << S << std::endl;

				S = Monte_Solve(ll, rl, dr);
				std::cout << "== Monte-Carlo ==" << std::endl << S << std::endl;*/

				std::cout << "file" << std::endl;
				std::string data;
				std::cin >> data;
				std::cout << "Введите границы интегрирования" << std::endl;
				long double ll, rl;
				std::cin >> ll >> rl;
				integral(data, ll, rl);

				break;}
				
			case 7:
			{
				std::cout << "file" << std::endl;
			std::string data;
			std::cin >> data;
			std::cout << "Введите значение переменной" << std::endl;
			long double x;
			std::cin >> x;
			differentiation(data,x);
				break;
			}
			case 8:
			{
				std::cout << "file" << std::endl;
			std::string data;
			std::cin >> data;
			std::cout << "Введите границы отрезка" << std::endl;
			long double ll, rl;
			std::cin >> ll >> rl;
			nayti_koren(data, ll, rl);

				break;
			}
			case 9:
			{
				std::cout << "file" << std::endl;
				std::string data;
				std::cin >> data;
				std::cout << "Введите границы интегрирования" << std::endl;
				long double ll, rl;
				std::cin >> ll >> rl;
				Normirovanie(data, ll, rl);

				break;
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
