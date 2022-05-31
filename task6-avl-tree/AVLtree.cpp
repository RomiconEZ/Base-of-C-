#include <iostream>
#include <fstream>
#include <string>
class AVLTree {
	struct Node {
		Node* left, * right, * parent;
		signed char balance;
		int data;
		Node(const int& X) : right(nullptr), left(nullptr), parent(nullptr), data(X), balance(0) {}
		~Node() {
			if (left) delete left;
			if (right) delete right;
			right = left = parent = nullptr;
		}
		int level() const {
			int L = (left != nullptr) ? left->level() : 0;
			int R = (right != nullptr) ? right->level() : 0;
			//int R = L + balance;
			return L > R ? L + 1 : R + 1;
		}
		int current_balance() {
			Node* now = this;
			return now->balance;
		}
		Node* minimum() {
			Node* now = this;
			while (now->left != nullptr) now = now->left;
			return now;
		}
		Node* maximum() {
			Node* now = this;
			while (now->right != nullptr) now = now->right;
			return now;
		}
		Node* next() {
			if (right != nullptr) return right->minimum();
			Node* p = parent, * now = this;
			while (p != nullptr) {
				if (now == p->left) break;
				now = p;
				p = p->parent;
			}
			return p;
		}
		Node* prev() {
			if (left != nullptr) return left->maximum();
			Node* p = parent, * now = this;
			while (p != nullptr) {
				if (now == p->right) break;
				now = p;
				p = p->parent;
			}
			return p;
		}
	};
	Node* root;
	unsigned int count;
	Node* _RightRotate(Node*);
	Node* _LeftRotate(Node*);
	Node* _BigRightRotate(Node*);
	Node* _BigLeftRotate(Node*);
public:
	AVLTree() : root(nullptr), count(0) {}
	~AVLTree() { clear(); }
	void clear() { if (root) delete root; root = nullptr; }
	int balance_of_root()
	{
		if (root)
			return root->current_balance();
		else
			return 0;
	}
	void insert(const int& X) {
		++count;
		if (root == nullptr) { root = new Node(X); return; }
		Node* now, * p;
		bool toLeft;
		now = root;
		do {
			p = now;
			if (X < now->data) {
				now = now->left;
				toLeft = true;
			}
			else {
				now = now->right;
				toLeft = false;
			}
		} while (now);
		now = new Node(X);
		if (toLeft)
			p->left = now;
		else
			p->right = now;
		now->parent = p;
		// Восстановить баланс
		do {
			if (now->parent->left == now) now->parent->balance -= 1;
			else now->parent->balance += 1;

			now = now->parent;
			switch (now->balance) {
			case 2:
				if (now->right->balance == -1)
					now = _BigLeftRotate(now);
				else
					now = _LeftRotate(now);
				break;
			case -2:
				if (now->left->balance == 1)
					now = _BigRightRotate(now);
				else
					now = _RightRotate(now);
				break;
			}
		} while (now != root && now->balance != 0);

	}
	unsigned int size() const { return count; }
	int height()const { return (root != nullptr) ? root->level() : 0; }


	class iterator {
		Node* now;
	public:
		iterator(Node* p = nullptr) : now(p) {}
		const int& operator*()const { return now->data; }
		bool operator==(const iterator& p) const { return now == p.now; }
		bool operator!=(const iterator& p) const { return now != p.now; }
		iterator& operator++() {
			if (now) now = now->next();
			else throw "Iterator error";
			return *this;
		}
		iterator operator++(int) {
			Node* tmp = now;
			if (now) now = now->next();
			else throw "Iterator error";
			return iterator(tmp);
		}
		friend class AVLTree;
	};
	iterator begin()const {
		if (root) return iterator(root->minimum());
		return end();
	}
	iterator end()const { return iterator(nullptr); }

	class reverse_iterator {
		Node* now;
	public:
		reverse_iterator(Node* p = nullptr) : now(p) {}
		const int& operator*()const { return now->data; }
		bool operator==(const reverse_iterator& p) const { return now == p.now; }
		bool operator!=(const reverse_iterator& p) const { return now != p.now; }
		reverse_iterator& operator++() {
			if (now) now = now->prev();
			else throw "Iterator error";
			return *this;
		}
		reverse_iterator operator++(int) {
			Node* tmp = now;
			if (now) now = now->prev();
			else throw "Iterator error";
			return reverse_iterator(tmp);
		}
	};
	reverse_iterator rbegin()const {
		if (root) return reverse_iterator(root->maximum());
		return rend();
	}
	reverse_iterator rend()const { return reverse_iterator(nullptr); }

	iterator find(const int& X) {
		Node* now = root;
		while (now) {
			if (X == now->data) break;
			if (X < now->data) now = now->left;
			else now = now->right;
		}
		return iterator(now);
	}
	void erase(iterator);
};

//------------------------------------------------------------------------------
void AVLTree::erase(typename AVLTree::iterator pos) {
	Node* toDelete = pos.now;
	if (toDelete == nullptr) return;

	Node* Alt;
	if (toDelete->left == nullptr)
		Alt = toDelete->right;
	else if (toDelete->right == nullptr)
		Alt = toDelete->left;
	else {
		Alt = toDelete->right->minimum();
		if (Alt->parent != toDelete) {
			Alt->parent->left = Alt->right;
			if (Alt->right) Alt->right->parent = Alt->parent;
			Alt->right = toDelete->right;
			toDelete->right->parent = Alt;
		}
		Alt->left = toDelete->left;
		toDelete->left->parent = Alt;
	}

	Node* notBalanced;
	if (Alt == nullptr) {
		notBalanced = toDelete->parent;
		if (notBalanced != nullptr) {
			if (notBalanced->left == toDelete) notBalanced->balance += 1;
			else notBalanced->balance -= 1;
		}
	}
	else {
		Alt->balance = toDelete->balance;
		if (Alt->parent == toDelete) {
			notBalanced = Alt;
			if (Alt == toDelete->left) notBalanced->balance += 1;
			else notBalanced->balance -= 1;
		}
		else {
			notBalanced = Alt->parent;
			notBalanced->balance += 1;
		}
	}

	if (toDelete->parent == nullptr) // toDelete == root
		root = Alt;
	else {
		if (toDelete->parent->left == toDelete)
			toDelete->parent->left = Alt;
		else
			toDelete->parent->right = Alt;
	}
	if (Alt != nullptr) Alt->parent = toDelete->parent;

	toDelete->right = nullptr; toDelete->left = nullptr;
	delete toDelete;
	--count;

	// Балансировка
	if (notBalanced != NULL)
	{
		while (notBalanced)
		{
			switch (notBalanced->balance) {
			case 2:
				if (notBalanced->right->balance == -1)
					notBalanced = _BigLeftRotate(notBalanced);
				else
					notBalanced = _LeftRotate(notBalanced);
				break;
			case -2:
				if (notBalanced->left->balance == 1)
					notBalanced = _BigRightRotate(notBalanced);
				else
					notBalanced = _RightRotate(notBalanced);
				break;
			}

			if (notBalanced->balance == 1 || notBalanced->balance == -1) break;

			if (notBalanced->parent != nullptr) {
				if (notBalanced->parent->left == notBalanced)
					notBalanced->parent->balance += 1;
				else
					notBalanced->parent->balance -= 1;
			}

			notBalanced = notBalanced->parent;
		}
	}

}
//------------------------------------------------------------------------------
typename AVLTree::Node*
AVLTree::_RightRotate(typename AVLTree::Node* c) {
	if (c->balance != -2) return c;
	Node* a = c->left;
	if (a->balance == 1) return c;
	c->left = a->right;
	if (a->right) a->right->parent = c;
	a->parent = c->parent;
	if (c->parent) {
		if (c->parent->left == c) c->parent->left = a;
		else c->parent->right = a;
	}
	else
		root = a;
	a->right = c;
	c->parent = a;

	if (a->balance == -1) {
		a->balance = 0; c->balance = 0;
	}
	else {
		a->balance = 1; c->balance = -1;
	}
	return a;
}

//---------------------------------------------------------------------------------
typename AVLTree::Node*
AVLTree::_LeftRotate(typename AVLTree::Node* a) {
	if (a->balance != 2) return a;
	Node* c = a->right;
	if (c->balance == -1) return a;
	a->right = c->left;
	if (c->left) c->left->parent = a;
	c->parent = a->parent;
	if (a->parent) {
		if (a->parent->left == a) a->parent->left = c;
		else a->parent->right = c;
	}
	else
		root = c;
	c->left = a;
	a->parent = c;

	if (c->balance == 1) {
		a->balance = 0; c->balance = 0;
	}
	else {
		a->balance = 1; c->balance = -1;
	}
	return c;
}
//---------------------------------------------------------------------------------
typename AVLTree::Node*
AVLTree::_BigRightRotate(typename AVLTree::Node* c) {
	if (c->balance != -2) return c;
	Node* a = c->left;
	if (a->balance != 1) return c;
	Node* b = a->right;

	a->right = b->left; if (b->left) b->left->parent = a;
	c->left = b->right; if (b->right) b->right->parent = c;

	b->parent = c->parent;
	if (c->parent) {
		if (c->parent->left == c) c->parent->left = b;
		else c->parent->right = b;
	}
	else
		root = b;

	b->left = a; a->parent = b;
	b->right = c; c->parent = b;

	if (b->balance == 0) {
		a->balance = 0; c->balance = 0;
	}
	else if (b->balance == 1) {
		a->balance = -1; c->balance = 0;
	}
	else {
		a->balance = 0; c->balance = 1;
	}
	b->balance = 0;
	return b;
}

//---------------------------------------------------------------------------------
typename AVLTree::Node*
AVLTree::_BigLeftRotate(typename AVLTree::Node* a) {
	if (a->balance != 2) return a;
	Node* c = a->right;
	if (c->balance != -1) return a;
	Node* b = c->left;

	a->right = b->left; if (b->left) b->left->parent = a;
	c->left = b->right; if (b->right) b->right->parent = c;

	b->parent = a->parent;
	if (a->parent) {
		if (a->parent->left == a) a->parent->left = b;
		else a->parent->right = b;
	}
	else
		root = b;

	b->left = a; a->parent = b;
	b->right = c; c->parent = b;

	if (b->balance == 0) {
		a->balance = 0; c->balance = 0;
	}
	else if (b->balance == 1) {
		a->balance = -1; c->balance = 0;
	}
	else {
		a->balance = 0; c->balance = 1;
	}
	b->balance = 0;
	return b;
}
typedef AVLTree Container;

Container WorkMultiplicity(const char* fname, const char* outfname) {
	Container Multiplicity;
	
	std::ifstream inFile(fname);
	std::ofstream outFile(outfname);
	int a=0;
	if (!inFile) {
		a=-1;
	}
	if (!outFile) {
		a=-2;
	}
	std::string operation;
	std::string number;
	std::string string_amount_of_action;
	std::getline(inFile, string_amount_of_action);
	int amount_of_action = std::stoi(string_amount_of_action);
	
	while ((inFile.peek() != EOF) && (amount_of_action-- > 0))
	{
		inFile >> operation;
		inFile >> number;
		if (operation == "+")
		{
			Multiplicity.insert(std::stoi(number));
			outFile << Multiplicity.balance_of_root() << "\r\n";
		}
		else
		{
			if (operation == "-")
			{
				auto iter = Multiplicity.find(std::stoi(number));
				if (iter != nullptr)
					Multiplicity.erase(iter);
				outFile << Multiplicity.balance_of_root() << "\r\n";
			}
			else
			{
				if (operation == "?")
				{
					auto iter = Multiplicity.find(std::stoi(number));
					if (iter != nullptr)
						outFile << "true\r\n";
					else
						outFile << "false\r\n";
				}
			}
		}


	}
	
	inFile.close();
	outFile.close();
	return Multiplicity;
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

  auto test=WorkMultiplicity(argv[1], argv[2]);
  return 0;
}
