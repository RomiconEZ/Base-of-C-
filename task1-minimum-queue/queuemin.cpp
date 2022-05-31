#include <fstream>
#include <iostream>
#include <stack>


typedef std::stack<std::pair<long, long>> Stack;
typedef std::pair< std::stack<std::pair<long, long>>, std::stack<std::pair<long, long>>> TwoStacks;
TwoStacks Queue_with_minimum(const char* fname, const char* outfname)
{
    // Модифицированный стек:
    // Будем хранить в стеке не сами элементы, а пары: элемент и минимум в стеке, начиная с этого элемента и ниже. Иными словами, если представить стек как массив пар, то
    // Понятно, что тогда нахождение минимума во всём стеке будет заключаться просто во взятии значения stack.top().second.
    // Также очевидно, что при добавлении нового элемента в стек величина second будет равна min(stack.top().second, new_element).
    // Удаление элемента из стека ничем не отличается от удаления из обычного стека, поскольку удаляемый элемент никак не мог повлиять на значения second для оставшихся элементов.
    
    // Алгоритм с нахождением элемента за O(1);

   /* Заведём два стека,модифицированных для нахождения минимума за O(1) : s1 и s2.
   *  Добваление:
      Добавлять новые элементы будем всегда в стек s1.

      Извлечение:
      Извлекать элементы - только из стека s2.
      При этом, если при попытке извлечения элемента из стека s2 он оказался пустым, просто перенесём все элементы из стека s1 в стек s2
      (при этом элементы в стеке s2 получатся уже в обратном порядке, что нам и нужно для извлечения элементов; стек s1 же станет пустым).

      Нахождение:
      Нахождение минимума в очереди будет заключаться в нахождении минимума из минимума в стеке s1 и минимума в стеке s2.

      Выполняем все операции за O(1) 
      (Т.к. каждый элемент в худшем случае 1 раз добавляется в стек s1, 1 раз переносится в стек s2 и 1 раз извлекается из стека s2).*/




    std::ifstream inFile(fname);
    std::ofstream outFile(outfname);
    unsigned long deg;
    inFile >> deg;
    Stack s1, s2;
    std::string operation;
    long number;
    long current_minimum;
    long minima;
    long result;
    long element;
    while (deg-- > 0)
    {
        inFile >> operation;
        

        if (operation == "+") // добавление элемента
        {
            inFile >> number;
            minima = s1.empty() ? number : std::min(number, s1.top().second);
            s1.push(std::make_pair(number, minima));
        }
        else
        {
            if (operation == "-") // изъятие элемента
            {
                if (s2.empty())
                    while (!s1.empty()) {
                        element = s1.top().first;
                        s1.pop();
                        minima = s2.empty() ? element : std::min(element, s2.top().second);
                        s2.push(std::make_pair(element, minima));
                    }
                result = s2.top().first;
                s2.pop();

            }
            else
            {
                if (operation == "?") // поиск минимального
                {
                    if (s1.empty() || s2.empty())
                        current_minimum = s1.empty() ? s2.top().second : s1.top().second;
                    else
                        current_minimum = std::min(s1.top().second, s2.top().second);
                    
                    outFile << current_minimum << std::endl;
                }
            }
        }


    }
    inFile.close();
    outFile.close();
    return make_pair(s1, s2);
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
  inFile.close();
  outFile.close();
  
  Queue_with_minimum(argv[1], argv[2]);
 
  return 0;
}
