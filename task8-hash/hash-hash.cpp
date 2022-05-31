#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <list>
#include <algorithm>
#include <iterator>


unsigned long checkPrime(unsigned long n) // Проверка,что число простое
{
	unsigned long i;
	if (n == 1 || n == 0)
	{
		return 0;
	}
	for (i = 2; i < n / 2; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

unsigned long getPrime(unsigned long n) // Получение простого число
{
	if (n % 2 == 0)
	{
		n++;
	}
	while (!checkPrime(n))
	{
		n += 2;
	}
	return n;
}

template<class ElementType>
class HashTable;

template <typename ElementType>
class TableEntry
{
	
	public:
	unsigned long h_key;
	ElementType h_value;
	TableEntry(unsigned long h_key, ElementType h_value)
	{
				this->h_key = h_key; // Хэш значения
				this->h_value = h_value; // значение
	}
	friend class HashTable<ElementType>;
	TableEntry()
	{
		this->h_key = 0;
		this->h_value = 0;
	}
};

template <typename ElementType>
class HashTable
{
	unsigned long capacity;
	std::list< TableEntry <ElementType> >* table;

public:
	
	HashTable(unsigned long V);
	~HashTable()
	{
		if (capacity != 0) {
			for (int i = 0; i < capacity; i++)
			{
				if (!table[i].empty())
					table[i].clear();
			}
			capacity = 0;
			delete[] table;
		}
	}	
	void insertItem(ElementType data);
	void deleteItem(ElementType data);
	unsigned long getHashCode(ElementType key); // Функция для получения хеша от значения ( для устранения коллизии )
	unsigned long getHashCodeTable(ElementType key); // Функция для получения хеша от значения ( определение индекса в массиве )
	bool SearchHashTable(ElementType key);
	unsigned long getCapacity()
	{
		return capacity;
	}
	
};


template <typename ElementType>
HashTable<ElementType>::HashTable(unsigned long c)
{
	unsigned long size = getPrime(c);
	this->capacity = size; // мощность множества это первое простое число большее входного
	table = new std::list< TableEntry <ElementType>>[capacity]; // массив списков

}

template <typename ElementType>
void HashTable<ElementType>::insertItem(ElementType data)
{

	unsigned long hc = getHashCodeTable(data); // инициализируем начальный хэш, чтобы знать место в массиве элементов с таким хэшем
	TableEntry<ElementType> Node(getHashCode(data), data);
	table[hc].push_back(Node);
	
}

template <typename ElementType>
bool HashTable<ElementType>::SearchHashTable(ElementType data) {
	unsigned long hc = getHashCodeTable(data);
	unsigned long hc_data = getHashCode(data);

	typename std::list<TableEntry <ElementType>>::iterator i;
	for (i = table[hc].begin(); i != table[hc].end(); i++)
	{
		if (i->h_key == hc_data)
		{
			return 1;
		}
	}
	return 0;

}

template <typename ElementType>
void HashTable<ElementType>::deleteItem(ElementType data)
{
	unsigned long hc = getHashCodeTable(data);
	unsigned long hc_data = getHashCode(data);

	typename std::list<TableEntry <ElementType>>::iterator i;
	for (i = table[hc].begin(); i != table[hc].end(); i++) // пробегаемся по списку, расположенному в ячейке массива, и находим элемент с таким же хешем(HashCode)
	{
		if (i->h_key == hc_data)
		{
			table[hc].erase(i);
			break;
		}
	}

}

template <typename ElementType>
unsigned long HashTable<ElementType>::getHashCodeTable(ElementType a)
{
	//hash function
	double n;
	unsigned long h1 = floor(capacity * modf(a * 0.5, &n));
	unsigned long h2 = ((h1 + abs(a)) % 967);
	return (h1 + h2)%capacity;
	
}

template <typename ElementType>
unsigned long HashTable<ElementType>::getHashCode(ElementType a)
{
	//hash function 
	double n;
	unsigned long h1 = floor(capacity * modf(a * 0.2, &n));
	unsigned long h2 = a % 947;
	return (h1 + h2) % capacity;

}



typedef HashTable<long> Container;
void WorkMultiplicity(const char* fname, const char* outfname, Container* Multiplicity)
{
	std::ifstream inFile(fname);
	std::ofstream outFile(outfname);
	unsigned long deg;
	inFile >> deg;
	std::string operation;
	long number;
	while (deg-->0)
	{
		inFile >> operation;
		inFile >> number;
		
		
		if (operation == "+")
		{
			(* Multiplicity).insertItem(number);
		}
		else
		{
			if (operation == "-")
			{
				(*Multiplicity).deleteItem(number);
				
			}
			else
			{
				if (operation == "?")
				{
					
					if ((*Multiplicity).SearchHashTable(number))
						outFile << "true" << std::endl;
					else
						outFile << "false" << std::endl;
				}
			}
		}


	}
	inFile.close();
	outFile.close();
	
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
  
 unsigned long deg;
inFile >> deg;
HashTable<long> HashTable(deg);
inFile.close();
outFile.close();
  WorkMultiplicity(argv[1], argv[2], &HashTable);
  return 0;
}
