#include <iostream>
#include <fstream>
#include <algorithm>


template <typename T>
void InsertSort(T* M,  int n)
{

    T tmp;
    for (int j = 1; j < n; ++j)
    {
       int left = 0, right = j;
       int mid;
        do
        {
            mid = left + (right - left) / 2;
            if (M[mid] > M[j])right = mid - 1; else left = mid + 1;
        } while (left < right);
        if (right >= 0)
        {
            if (M[j] < M[right])--right;
        }
        if (j != right)
        {
            tmp = M[j];
            for (int i = j; i > right + 1; --i)
                M[i] = M[i - 1];
            M[right + 1] = tmp;
        }
    }

}
template <typename ElementType>
ElementType partition(ElementType a[],  int left,  int right,  int pIndex)
{
    // pick `pIndex` as a pivot from the array
    ElementType pivot = a[pIndex];

    // Move pivot to end
    std::swap(a[pIndex], a[right]);

    pIndex = left;

    for ( int i = left; i < right; i++)
    {
        if (a[i] < pivot)// ! <=
        {
            std::swap(a[i], a[pIndex]);
            pIndex++;
        }
    }

    // move pivot to its final place
    std::swap(a[pIndex], a[right]);

    // return `pIndex` (index of the pivot element)
    return pIndex;
}

// Возвращает k-ый наименьший элемент
// Меняется зона для разбиения на два подмассива с каждым рекурсивным вызовом
template <typename ElementType>
ElementType quickselect(ElementType nums[],  int left,  int right,  int k)
{
    // Если массив содержит только один элемент
    if (left == right) 
    {
        return nums[left];
    }

    // Случайно выбираем pIndex
     int pIndex = left + rand() % (right - left + 1);



    pIndex = partition(nums, left, right, pIndex);

    if (std::is_sorted(&nums[left], &nums[right+1])) // проверяем, что часть массива отсортирована
    {
        return nums[k]; // если получили, что часть массива, в которой мы ищем k-ую статистику, отсортирована, то эта часть соответствует части полностью отсортированного массива
    }

    // Индекс относительно которого мы разбивали оказался k-от порядковой статистикой
    if (k == pIndex)
    {
        return nums[k];
    }

    // if `k` is less than the pivot index
    else if (k < pIndex)
    {
        return quickselect<ElementType>(nums, left, pIndex - 1, k);
    }

    // if `k` is more than the pivot index
    else
    {
        return quickselect<ElementType>(nums, pIndex + 1, right, k);
    }
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
  int size;
     int k1, k2;
    int A, B, C;
    inFile >> size >> k1 >> k2 >> A >> B >> C;
    int* array = new int[size];
    inFile >> array[0] >> array[1];
    for ( int i = 2; i < size; i++)
    {
        array[i] = A * array[i - 2] + B * array[i - 1] + C;
    }
    int* k1_k2 = new int[k2 - k1 + 1]; // массив элементов от k1 до k2 статистики


     int j = 0;
    int k1_value = quickselect<int>(array, 0, size - 1, k1 - 1);
    int k2_value = quickselect<int>(array, 0, size - 1, k2 - 1);
    for ( int i = 0; i < size; i++)
        // ищу в массиве элементы, которые по значению лежат между значением k1 и k2 статистик
    {
        if ((k2_value >= array[i]) && (array[i] >= k1_value))
        {
            k1_k2[j] = array[i];
            ++j;
        }
        if (j == k2 - k1 + 1)
            break;
    }

    InsertSort(k1_k2, k2 - k1+1);
    for ( int i = 0; i < k2 - k1; ++i)
        outFile << k1_k2[i] << " ";

    outFile << k1_k2[k2 - k1];

 delete[] array;
 delete[] k1_k2;
  inFile.close();
  outFile.close();
  return 0;
}
