#include <fstream>
#include <iostream>
#include <string>


long long  Merge(long long * M, long long  first, long long  middle, long long  last)
{
	long long  inv = 0;
	long long  size = last - first + 1;
	long long * tmp = new long long [size];
	long long  start1 = first, end1 = middle, start2 = middle + 1, end2 = last;
	long long  ind = 0;
	
	while (start1 <= end1 && start2 <= end2)
	{
		if (M[start1] <= M[start2])
		{
			tmp[ind++] = M[start1++];
			
		}
		else
		{
			tmp[ind++] = M[start2++];
			inv += (middle - start1) + 1;
		}
	}
	while (start1 <= end1) tmp[ind++] = M[start1++];
	while (start2 <= end2) tmp[ind++] = M[start2++];
	
	/*ind = 0;
	while (first <= last)
		M[first++] = tmp[ind++];*/
	for (ind = 0; ind < size; ind++) M[first + ind] = tmp[ind];
	delete[] tmp;
	return inv;
}
long long  Split(long long * M, long long  first, long long  last)
{
	long long  inv = 0;
	if (first < last)
	{
		long long  middle = first + (last - first) / 2;
		inv += Split(M, first, middle);
		inv += Split(M, middle + 1, last);
		inv += Merge(M, first, middle, last);
	}
	return inv;
}
long long  KolvoInversiy(const char fname[])
{
	std::ifstream inFile(fname);
	std::string strochka;
	if (inFile)
	{
		std::getline(inFile, strochka);
		long long  n = std::stoi(strochka.c_str());
		long long * mas = new long long [n]();
		long long  k = 0;
		while ((inFile.peek() != EOF) && (k < n))
		{
			inFile >> strochka;
			mas[k] = std::stoll(strochka.c_str());
			++k;
		}
		inFile.close();
		return Split(mas, 0, n - 1);
	}
	return -1;
	
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        return 2;
    }
    std::ofstream outFile(argv[2]);
    if (!outFile) {
        return 3;
    }
    inFile.close();
	outFile << KolvoInversiy(argv[1]);
	outFile.close();
    
    return 0;
}
