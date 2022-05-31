#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include<iomanip>
int Number_of_Symbol(char symbol) {
    if (symbol > 'Z') {
        return 26 + (symbol - 'a');
    }
    return (symbol - 'A');
}
void lsd_string_radix(char** array, int array_size, int iteration, int M)
{
   
    char** temp = new char*[array_size];

    for (int i = M - 1; i >= M-iteration; i--)
    {
        int count[256] = { 0 };

        
        for (int j = 0; j < array_size; j++)
        {
            count[Number_of_Symbol(array[j][i]) + 1]++;
        }

        for (int j = 2; j < 256; j++)
            count[j] += count[j - 1];

       
        for (int j = 0; j < array_size; j++)
        {
            temp[count[Number_of_Symbol(array[j][i])]++] = array[j];
        }

        for (int j = 0; j < array_size; j++)
            array[j] = temp[j];
    }
    delete[] temp;
}

int main(int argc, char* argv[]){
  if (argc<3) {
    return -1;
  }

  std::ifstream inFile(argv[1]);
  if (!inFile){
    return -2;
  }
  
  std::ofstream outFile(argv[2]);
  if (!outFile){
    return -3;
  }
  
  int N=0,M=0,K=0;
    inFile >> N >> M >> K;
    char** array = new char* [N]; 
    for (int count = 0; count < N; ++count)
        array[count] = new char[M]; 
    for (int count = 0; count < M; ++count)
    {
        for (int count2 = 0; count2 < N; ++count2)
            inFile >> array[count2][count];
    }
    std::map <char*, int> mp;
    for (int count = 1; count <= N; ++count)
        mp.insert(std::make_pair(array[count - 1], count));

    lsd_string_radix(array, N, K, M);

    for (int count = 0; count < N-1; ++count)
        outFile << mp.find(array[count])->second << " ";
    outFile << mp.find(array[N - 1])->second;

    delete[] array;
  
  inFile.close();
  outFile.close();
  return 0;
}
