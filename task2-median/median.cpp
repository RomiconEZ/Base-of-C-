#include <fstream>
#include <iostream>

template <typename ElementType>
class student 
{
    ElementType id;
    float grade;
public:
    student(ElementType id_, float grade_)
    {
        id = id_;
        grade = grade_;
    }
    student()
    {
        id = 0;
        grade = 0;
    }
    void set_index(ElementType i) { id = i; }
    void set_value(float v) { grade = v; }
    ElementType get_index() const { return id; }
    float get_value() const { return grade; }
    
};

// Partition using Lomuto partition scheme
template <typename ElementType>
ElementType partition(student<ElementType> a[], ElementType left, ElementType right, ElementType pIndex)
{
    // pick `pIndex` as a pivot from the array
    float pivot = a[pIndex].get_value();

    // Move pivot to end
    std::swap(a[pIndex], a[right]);

    // elements less than the pivot will be pushed to the left of `pIndex`;
    // elements more than the pivot will be pushed to the right of `pIndex`;
    // equal elements can go either way
    
    pIndex = left;

    // each time we find an element less than or equal to the pivot, `pIndex`
    // is incremented, and that element would be placed before the pivot.
    for (int i = left; i < right; i++)
    {
        if (a[i].get_value() <= pivot)
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
ElementType quickselect_for_student(student<ElementType> M[], ElementType left, ElementType right, ElementType k)
{
    // Если массив содержит только один элемент
    if (left == right) 
    {
        return M[left].get_index();
    }

    // Случайно выбираем pIndex
    ElementType pIndex = left + rand() % (right - left + 1);

    pIndex = partition(M, left, right, pIndex);

    // Индекс относительно которого мы разбивали оказался k-от порядковой статистикой
    if (k == pIndex) {
        return M[k].get_index();
    }

    // if `k` is less than the pivot index
    else if (k < pIndex) 
    
    {
        return quickselect_for_student<ElementType>(M, left, pIndex - 1, k);
    }

    // if `k` is more than the pivot index
    else 
    {
        return quickselect_for_student<ElementType>(M, pIndex + 1, right, k);
    }
}


int main(int argc, char* argv[]){
  if (argc<2) {
    return 1;
  }
  std::ifstream inFile(argv[1]);
  if (!inFile){
    return 2;
  }
  unsigned int N = 0;
    inFile >> N;
    student<unsigned int>* M = new student<unsigned int>[N];

    float grade;
    unsigned int id_max=0, id_min=0;
    
    for (unsigned int i = 1; i <= N; ++i) 
    {
        inFile >> grade;
        if (grade < M[id_min].get_value()) {
            id_min = i-1;
        }
        if (grade > M[id_max].get_value()) {
            id_max = i-1;
        }
        M[i-1] = student<unsigned int>(i, grade);
    }
    unsigned int pos_med= (N + 1) / 2 - 1;
    
    std::cout << id_min + 1 << ' ';
    std::cout << quickselect_for_student<unsigned int>(M, 0, N-1, pos_med) << ' ';
    std::cout << id_max + 1 << ' ';
    inFile.close();
    return 0;
	
}
