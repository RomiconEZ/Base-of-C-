#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <list>
#include <algorithm>
#include <iterator>




template<class ElementType>
class QueueWithPriority;

template <typename ElementType>
class Node
{
	unsigned long PositionINPUT;
	ElementType Data;
public:
	
	Node(unsigned long PosotionINPUT_, ElementType Data_)
	{
		this->PositionINPUT = PosotionINPUT_; // храним номер строки во входном файле, в которой элемент был добавлен
		this->Data = Data_; // значение
	}
	friend class QueueWithPriority<ElementType>;
	Node()
	{
		this->PositionINPUT = 0;
		this->Data = 0;
	}
	
};


template <typename ElementType>
class QueueWithPriority // Очередь с приоритетом на двухсвязном списке, где приоритет будет определяться позицией элемента в списке.
{
	std::list< Node <ElementType>> Queue;

public:

	QueueWithPriority();
	void push(ElementType Data_, unsigned long PosotionINPUT_);
	std::pair<ElementType, bool> extract_min();
	void decrease_key(unsigned long number_of_string, ElementType ChangeValueTo);

};
template <typename ElementType>
QueueWithPriority<ElementType>::QueueWithPriority()
{
	Queue = {};
}

template <typename ElementType>
void QueueWithPriority<ElementType>::push(ElementType Data_, unsigned long PosotionINPUT_)
{
	if (Queue.empty())
	{
		Queue.push_back(Node<ElementType>(PosotionINPUT_, Data_));
	}
	else
	{
		typename std::list<Node <ElementType>>::iterator it = Queue.begin();
		while (it->Data > Data_)
		{
			
			it++;
			if(it == Queue.end())
				break;

		}
		if (it != Queue.end())
		{
			Queue.insert(it, Node<ElementType>(PosotionINPUT_, Data_));
		}
		else
		{
			Queue.push_back(Node<ElementType>(PosotionINPUT_, Data_));
		}
	}
}

template <typename ElementType>
std::pair<ElementType,bool> QueueWithPriority<ElementType>::extract_min() 
{
	if (!Queue.empty())
	{
		
		ElementType data = Queue.back().Data;
		Queue.pop_back();
		return std::pair < ElementType, bool > (data, true);
	}
	return std::pair< ElementType, bool >(0, false);
}

template <typename ElementType>
void QueueWithPriority<ElementType>::decrease_key(unsigned long number_of_string, ElementType ChangeValueTo)
{
	if (!Queue.empty())
	{
		typename std::list<Node <ElementType> >::iterator it = Queue.begin();
		typename std::list<Node <ElementType> >::iterator it_next;
		typename std::list<Node <ElementType> >::iterator it_prev;
		while (it->PositionINPUT != number_of_string)
			it++;
		
		if (ChangeValueTo < it->Data)
		{
			it->Data = ChangeValueTo;
			if (it != --Queue.end())
			{
				it_next = std::next(it, 1);
				while (it->Data < (it_next)->Data) 
				{
				
					it_next = std::next(it_next, 1);
					if (it_next == Queue.end())
					{
						break;
					}
				
				}
				Queue.insert(it_next, *it);
				Queue.erase(it);
			}
		}
		else
		{
			it->Data = ChangeValueTo;
			if (it != Queue.begin())
			{
				it_prev = std::prev(it, 1);
				while (it->Data > (it_prev)->Data)
				{
					it_prev = std::prev(it_prev, 1);
					if (it == Queue.begin())
						break;
					
				}
				Queue.insert(it_prev, *it);
				Queue.erase(it);
			}
		}
	}
}


typedef QueueWithPriority<long> TypeofData;
TypeofData WorkQueue(const char* fname, const char* outfname)
{
	std::ifstream inFile(fname);
	std::ofstream outFile(outfname);
	TypeofData Queue;
	std::string operation;
	long number1;
	long number2;
	long number_of_string_of_InputFile=0;
	while (inFile.peek() != EOF)
	{
		inFile >> operation;
		number_of_string_of_InputFile++;

		if (operation == "push")
		{
			inFile >> number1;
			Queue.push(number1, number_of_string_of_InputFile);
		}
		else
		{
			if (operation == "extract-min")
			{
				std::pair<long, bool> ans = Queue.extract_min();
				if (ans.second==true)
					outFile << ans.first << std::endl;
				else
					outFile << "*" << std::endl;
			}
			else
			{
				if (operation == "decrease-key")
				{
					inFile >> number1;
					inFile >> number2;
					Queue.decrease_key(number1, number2);
					
				}
			}
		}

		operation = "";
	}
	inFile.close();
	outFile.close();
	return Queue;
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
  
  inFile.close();
	outFile.close();
	WorkQueue(argv[1], argv[2]);
  return 0;
}
