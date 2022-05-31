#include <iostream>

unsigned long long partition(unsigned int n, unsigned int k)
{
    // Два массива, которые содержат две строки в таблице раложений произвольного числа на произвольное число слагаемых
    unsigned long long* prev = new unsigned long long [n + 1];
    unsigned long long* current = new unsigned long long [n + 1];

    for (unsigned int i = 0; i <= n; ++i)
    {
        prev[i] = 0;
        current[i] = 0;
    }

    prev[0] = 1; // Разложение числа 0 на k слагаемых
    // Массивы - это последовательности количества разбиений чисел от 0 до n на k и k-1 слагаемых ( k определяется итерацией )
    // Формула: P(n,k)=P(n-k,k) + P(n,k-1) 
    for (unsigned int i = 1; i <= k; ++i)
    {
        for (unsigned int j = 1; j <= n; ++j)
        {
            current[j] = (j > i ? current[j - i] : 0) + prev[j - 1];
        }
        std::swap(current, prev);
        prev[0] = 0;
    }

    unsigned long long result = prev[n]; // в конце поменяли местами current и prev массивы
    delete[] current;
    delete[] prev;
    return result;
}

int main() 
{
    unsigned int n, k;
    std::cin >> n >> k;
    std::cout << partition(n, k);
}
