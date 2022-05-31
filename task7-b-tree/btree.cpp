#include <iostream>
#include <fstream>
#include <string>
template<class ElementType>
class BTree;

template <typename ElementType>
class Node
{
	ElementType* keys; // массив значения(ключей)
	Node** C; // массив дочерних указателей
	long n; //текущее количество ключей
	long t; //текущий параметр дерева
	bool leaf_node; // 1 - лист, 0 - не лист
public:
	void traverse();
	Node( long t_, bool leaf_node_);
	~Node();
	void splitChild( long i, Node* y);
	void remove_leaf_node( long idx);
	void remove_nonleaf_node( long idx);
	ElementType get_pre( long idx);
	ElementType get_suc( long idx);
	void borrow_prev( long idx);
	void borrow_next( long idx);
	void merge( long idx);
	long fill( long idx);
	 long findKey(ElementType k);
	void Deletenode(ElementType k);
	void Insert_Nonfull(ElementType k);
	// B tree node
	
	friend class BTree<ElementType>;
};
template <typename ElementType>
class BTree
{
	Node<ElementType>* root;
	long t; // число элементов в узле
public:
	
	BTree( long t_) 
	{ 
		t = t_; root = nullptr; 
	}
	~BTree();
	void traverse() 
	{
		if (root != nullptr)
			root->traverse();
	}

	void insertion(ElementType k);

	void Deletenode(ElementType k);
	
	bool ExistElement(ElementType k);

	std::pair<ElementType*, long> Get_info_about_root();
};
// B tree node
template <typename ElementType>
Node<ElementType>::Node( long t_, bool leaf_node_)
{
	t = t_;
	leaf_node = leaf_node_;

	keys = new ElementType[2 * t - 1];
	C = new Node * [2 * t];

	n = 0;
}
template <typename ElementType>
BTree<ElementType>::~BTree()
{
	if (root != nullptr)
	{
		root->~Node();
		t = 0;
		root = nullptr;
	}
}
template <typename ElementType>
Node<ElementType>::~Node()
{
	for (int i = 0; i < n; i++)
	{
		C[i]->~Node();
		C[i] = nullptr;
	}
	delete[] C;
	delete[] keys;
}
// Find the key
template <typename ElementType>
long Node<ElementType>::findKey(ElementType k) { // нахождения ключа среди значения узла или возврат последнего
	long idx = 0;
	while (idx < n && keys[idx] < k)
		++idx;
	return idx;
}
// Deletenode operation
template <typename ElementType>
void Node<ElementType>::Deletenode(ElementType k) {
	long idx = findKey(k);

	if (idx < n && keys[idx] == k) // проверка что найден нужный ключ и что узео листовой
	{
		if (leaf_node)
			remove_leaf_node(idx);
		else
			remove_nonleaf_node(idx);
	}
	else {
		if (leaf_node) // дошли до листа и не нашли ключ
		{
			return;
		}

		bool flag = ((idx == n) ? true : false);
		long index = idx;
		if (C[idx]->n < t)
			index = fill(idx); 
		// Проверка, что произошло слияние последнего узла с предпоследнем, тогда индекс сдвигаем на 1 влево
		// Также fill возвращает индекс, чтобв понять с каким узлом происходило слияние, если оно было
		if (flag && idx > n)
			C[idx - 1]->Deletenode(k);
		else
			C[index]->Deletenode(k);
	}
	return;
}
// Remove from the leaf_node
template <typename ElementType>
void Node<ElementType>::remove_leaf_node( long idx) {
	for ( long i = idx + 1; i < n; ++i)
		keys[i - 1] = keys[i];
	n--;
	return;
}
//Delete from non leaf_node node
template <typename ElementType>
void Node<ElementType>::remove_nonleaf_node( long idx) {
	
	
	ElementType k = keys[idx];
	 
	if (C[idx]->n >= t) // Забираем ключ у левого поддерева, если возможно
	{
		ElementType pred = get_pre(idx);
		keys[idx] = pred;
		C[idx]->Deletenode(pred);
	}

	else if (C[idx + 1]->n >= t) // Нет возможности у левого, тогда у правого
	{
		ElementType succ = get_suc(idx);
		keys[idx] = succ;
		C[idx + 1]->Deletenode(succ);
	}

	else // У обоих поддеревьев ключей по t-1, тогда сливаем
	{
		merge(idx);
		C[idx]->Deletenode(k);

	}
	return;
}





template <typename ElementType>
ElementType Node<ElementType>::get_pre(long idx) { 
	//берем самый правый элемент(максимальный в левом поддереве) от левого указателя, относительно рассматриваемого элемента
	Node* cur = C[idx];
	while (!cur->leaf_node)
		cur = cur->C[cur->n];

	return cur->keys[cur->n - 1];
}
template <typename ElementType>
ElementType Node<ElementType>::get_suc( long idx) { 
	//берем самый левый элемент(минимальный в правом поддререве) от правого указателя, относительно рассматриваемого элемента
	Node* cur = C[idx + 1];
	while (!cur->leaf_node)
		cur = cur->C[0];

	return cur->keys[0];
}

template <typename ElementType>
long Node<ElementType>::fill(long idx) 
{
	// Заполняем потомка, если у него недостаточно элементов.
	// Забираем у левого сиблинга, если у него достаточно элементов и его длина больше или равна длине правого,
	// иначе у правого. Если недостаточно элементов у правого, делаем слияние с левым(преимущественно).
	// Но если индекс равен 0, то нет левого сиблинга, поэтому сливаемся с правым.
	
	if (idx != 0 && idx != n)
	{
		if (C[idx - 1]->n >= C[idx + 1]->n && C[idx - 1]->n >= t)
		{
			borrow_prev(idx);
			return idx;
		}
		else
		{
			if (C[idx + 1]->n >= t)
			{
				borrow_next(idx);
				return idx;
			}
		}

		if (C[idx - 1]->n == t-1)
		{
			merge(idx - 1);
			return (idx - 1);
		}
		else 
			if (C[idx + 1]->n == t - 1)
			{
				merge(idx);
				return (idx);
			}
	}
	else
	{
		if (idx == n)
		{
			if (C[idx - 1]->n >= t)
			{
				borrow_prev(idx);
				return idx;
			}
			else
			{
				merge(idx - 1);
				return (idx - 1);
			}
			
		}
		else // idx==0
		{
			if (C[idx + 1]->n >= t)
			{
				borrow_next(idx);
				return idx;
			}
			else
			{
				merge(idx);
				return idx;
			}
		}
	}
	return 0;
// Объединяем с правым сиблингом, если указатель не крайний справа и длина правого сиблинга строго больше левого или если указатель крайний слева
}
//Borrow from previous
// i-е ключевое слово x передается левому дочернему узлу
template <typename ElementType>
void Node<ElementType>::borrow_prev( long idx) { 
	//из родителя перемещаем элемент в ребенка, а из левого сиблинга в родителя (заимствование у левого брата)
	Node* child = C[idx];
	Node* sibling = C[idx - 1];
	// перемещаем элементы ребенка на один шаг вправо
	for (int i = child->n - 1; i >= 0;--i)
		child->keys[i + 1] = child->keys[i];
	// перемещаем указатели ребенка на один шаг вправо
	if (!child->leaf_node) {
		for (int i = child->n; i >= 0; --i) 
			child->C[i + 1] = child->C[i];
	}
	// отдаем ключа родителя
	child->keys[0] = keys[idx - 1];

	// отдаем поддерево, которое стояло справо от наибольшего элемента сиблинга, в ребенка на 0-ую позицию
	if (!child->leaf_node)
	{
		child->C[0] = sibling->C[sibling->n];
		sibling->C[sibling->n] = nullptr;
	}

	keys[idx - 1] = sibling->keys[sibling->n - 1];

	child->n += 1;
	sibling->n -= 1;

	return;
}

// Borrow from the next
// i-е ключевое слово x передается правому дочернему узлу
template <typename ElementType>
void Node<ElementType>::borrow_next( long idx) { 
	//из родителя перемещаем элемент в ребенка, а из правого сиблинга в родителя (заимствование у правого брата)
	Node* child = C[idx];
	Node* sibling = C[idx + 1];

	child->keys[(child->n)] = keys[idx];

	if (!(child->leaf_node))
	{
		child->C[(child->n) + 1] = sibling->C[0];
	}

	keys[idx] = sibling->keys[0];

	for (int i = 1; i < sibling->n; ++i)
		sibling->keys[i - 1] = sibling->keys[i];

	if (!sibling->leaf_node) {
		for (int i = 1; i <= sibling->n; ++i)
			sibling->C[i - 1] = sibling->C[i];
	}

	child->n += 1;
	sibling->n -= 1;

	return;
}
// Merge
template <typename ElementType>
void Node<ElementType>::merge( long idx) { // слияние двух узлов
	Node* child = C[idx];
	Node* sibling = C[idx + 1];

	child->keys[t - 1] = keys[idx];

	for (long i = 0; i < sibling->n; ++i)
		child->keys[i + t] = sibling->keys[i];

	if (!child->leaf_node) {
		for (long i = 0; i <= sibling->n; ++i)
			child->C[i + t] = sibling->C[i];
	}

	for (long i = idx + 1; i < n; ++i)
		keys[i - 1] = keys[i];

	for (long i = idx + 2; i <= n; ++i)
		C[i - 1] = C[i];

	child->n += sibling->n + 1;
	n--;

	//delete (sibling);
	
	for (int i = 0; i < sibling->n; ++i) {
		(sibling->C)[i] = nullptr;
	}
	sibling->n = 0;
	delete[] sibling->keys;
	return;
}
// Insertion non full
template <typename ElementType>
void Node<ElementType>::Insert_Nonfull(ElementType k) {
	 long i = n - 1;

	if (leaf_node == true) { // если листовой узел, то просто ищем подходящее место
		while (i >= 0 && keys[i] > k) {
			keys[i + 1] = keys[i];
			i--;
		}

		keys[i + 1] = k;
		n++;
	}
	else {
		while (i >= 0 && keys[i] > k) //если не узловой, то ищем указателей на подходящее поддререво
			i--;
		i++; // Целевой подузел находится после ключевого слова, а порядковый номер на 1 больше, чем ключевое слово
	
		if (C[i]->n == 2 * t - 1) // если узел переполнен, то расширяем родителя и сплитим ребенка на два
		{
			splitChild(i, C[i]);

			if (keys[i] < k)
				i++;
		}
		C[i]->Insert_Nonfull(k);
	}
}
// Split child
template <typename ElementType>
void Node<ElementType>::splitChild( long i, Node* y) {
	Node* z = new Node(y->t, y->leaf_node);
	z->n = t - 1;

	for ( long j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];
	

	if (y->leaf_node == false) {
		for (long j = 0; j < t; j++)
		{
			z->C[j] = y->C[j + t];
			y->C[j + t] = nullptr;//new for avoid data leak
		}
	}
	
	for (long j = t; j < 2*t; j++) //new for avoid data leak
		z->C[j] = nullptr;

	

	y->n = t - 1;

	for ( long j = n; j >= i + 1; j--)
		C[j + 1] = C[j];

	C[i + 1] = z;

	for ( long j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	keys[i] = y->keys[t - 1];

	n = n + 1;
}

// Delete Operation
template <typename ElementType>
void BTree<ElementType>::Deletenode(ElementType k) {
	if (!root) {
		
		return;
	}

	root->Deletenode(k);

	if (root->n == 0) {
		Node<ElementType>* tmp = root;
		if (root->leaf_node)
			root = nullptr;
		else
			root = root->C[0];

		delete tmp;
	}
	return;
}
template <typename ElementType>
bool BTree<ElementType>::ExistElement(ElementType k) { // проверка существования элемента
	// Поиск в глубину
	if (!root) {
		
		return 0;
	}
	Node<ElementType>* cur_node = root;
	long idx= cur_node->n - 1;
	
	while (idx >= 0)
	{
		if ((cur_node->keys[idx] < k) && (cur_node->leaf_node == false))
		{
			cur_node = cur_node->C[idx+1];
			idx = cur_node->n - 1;
		}
		else
		{
			if ((cur_node->keys[idx] > k) && (cur_node->leaf_node == false) && (idx==0))
			{
				cur_node = cur_node->C[idx];
				idx = cur_node->n - 1;
			}
			else
			{
				if (cur_node->keys[idx] == k)
				{
					return 1;
				}
				idx--;
			}
		}
		
		
	}
	return 0;
}

// Insertion operation
template <typename ElementType>
void BTree<ElementType>::insertion(ElementType k) {
	if (root == NULL) {
		root = new Node<ElementType> (t, true);
		root->keys[0] = k;
		root->n = 1;
	}
	else {
		if (root->n == 2 * t - 1) { // если корень полный разбиваем его относильно среднего элемента
			Node<ElementType>* s = new Node<ElementType>(t, false);

			s->C[0] = root;

			s->splitChild(0, root);

			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->C[i]->Insert_Nonfull(k);

			root = s;
		}
		else
			root->Insert_Nonfull(k);
	}
}

template <typename ElementType>
std::pair<ElementType*,  long> BTree<ElementType>::Get_info_about_root()
{
	if (root!=nullptr)
		return std::pair<ElementType*,  long>(root->keys, root->n);
	else
		return std::pair<ElementType*, long>(nullptr, 0);
}
//---------------------ПОИСК---------------------------------------------------------


//-----------------------------------------------ВСТАВКА---------------------------------------------------------
// Передаем неполный узел x, а узел, на который указывает x.C [i], заполнен. 
// Переместите t-й узел x.C [i] вверх до x, чтобы он стал ключом, разделяющим y и z. X.C [i] разделен на две части, каждая с ключевыми словами t-1
// В это время общее количество дочерних элементов двух узлов равно 2 * (t) = 2 * t, которое не изменилось до разделения. 
//Новый узел z является новым дочерним элементом x и занимает место после y.


// Вспомогательный процесс, запрос x не заполнен
// insert_non_full
// Вставляем ключевые слова одним путем вниз по дереву
// Когда корневой узел заполнен. При разделении корневого узла узел, соответствующий t-му ключевому слову, становится корнем дочернего элемента с двумя дочерними элементами.
// insert
//-----------------------------------------------УДАЛЕНИЕ---------------------------------------------------------
// Чтобы удалить k из x, необходимо убедиться, что всякий раз, когда x исследует себя рекурсивно, количество ключевых слов в x не меньше t, что на единицу больше, чем в обычном минимальном дереве ключевых слов.
// Делится на следующие ситуации :
// Случай 1 : k находится в узле x, а x - листовой узел: 
//		удалите k
// Случай 2: k находится в узле x, а x - внутренний узел:
//		A : Если дочерний узел y, который предшествует k в узле x, имеет не менее t ключевых слов, найдите предшественника k в y.Рекурсивно удалите предшественника и замените k в x на предшественника.
//		B : Симметричный.Если y имеет только t - 1 узлов, проверьте узел z после k в x и найдите преемника.
//		C : Если и y, и z имеют только t - 1 ключевые слова, объединить все k и z в y, отпустить z и рекурсивно удалить k из y.
// Случай 3 : k не входит в x, необходимо определить поддерево x.C[i], содержащее k.Если x.C[i] имеет только t - 1 ключевых слов, то :
//		A : Его соседние узлы - братья имеют не менее t ключевых слов, уменьшите одно из ключевых слов x до x.C[i] и поднимите один из соседних узлов - братьев до x.
//		B : Если все соседние узлы - братья имеют только ключевые слова t - 1, объедините x.C[i] с одним родственным узлом и переместите ключевое слово x на вновь объединенный узел.




//1. If the target key is at the leaf node :
//If the target key is at the leaf node, we further study the given data to check if any of the following cases exist :
//
//Case 1 : If the leaf node consists of the min number of keys according to the given degree / order, then the key is simply deleted from the node.
//Case 2 : If the leaf contains the minimum number of keys, then :
//	Case 2a : The node can borrow a key from the immediate left sibling node, if it has more than the minimum number of keys.The transfer of the keys take place through the parent node, i.e, the maximum key of the left sibling moves upwardsand replaces the parent; while the parent key moves down to the target node from where the target key is simply deleted.
//	Case 2b: The node can borrow a key from the immediate right sibling node, if it has more than the minimum number of keys.The transfer of the keys take place through the parent node, i.e, the minimum key of the right sibling moves upwardsand replaces the parent; while the parent key moves down to the target node from where the target key is simply deleted.
//	Case 2c: If neither of the siblings have keys more than the minimum number of keys required then, merge the target node with either the left or the right sibling along with the parent key of respective node.
//	2.If the target key is at the internal node :
//	If the target key is at an internal node, we further study the given data to check if any of the following cases exist :
//
//Case 1 : If the left child has more than the minimum number of keys, the target key in the internal node is replaced by its inorder predecessor, i.e, the largest element of the left child node.
//Case 2 : If the right child has more than the minimum number of keys, the target key in the internal node is replaced by it’s inorder successor, i.e, the smallest element of the right child node.
//------------------------------------------------------------------------------

typedef BTree<int> Container;

void WorkMultiplicity(const char* fname, const char* outfname)
{
	std::ifstream inFile(fname);
	std::ofstream outFile(outfname);
	 long deg;
	inFile >> deg;
	Container Multiplicity(deg);
	std::string operation;
	 long number;
	 long amount_of_action;
	inFile >> amount_of_action;
	while ((inFile.peek() != EOF) && (amount_of_action-- > 0))
	{
		inFile >> operation;
		inFile >> number;
	
		if (operation == "+")
		{
			Multiplicity.insertion(number);
			auto info_about_root = Multiplicity.Get_info_about_root();
			outFile << info_about_root.second;
			for ( long i = 0; i < info_about_root.second; i++)
			{
				outFile << " " << info_about_root.first[i];
			}
			outFile << std::endl;
		}
		else
		{
			if (operation == "-")
			{
				Multiplicity.Deletenode(number);
				auto info_about_root = Multiplicity.Get_info_about_root();
				outFile << info_about_root.second;
				for ( long i = 0; i < info_about_root.second; i++)
				{
					outFile << " " << info_about_root.first[i];
				}
				outFile << std::endl;
			}
			else
			{
				if (operation == "?")
				{
					if (Multiplicity.ExistElement(number))
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
  
  inFile.close();
  outFile.close();
  WorkMultiplicity(argv[1], argv[2]);
  return 0;
}
