#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstdio>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

template<class T>

class BST_Node 
{
public:
	bool empty;
	T data;
	int height;
	BST_Node<T> *left;
	BST_Node<T> *right;
	BST_Node<T> *parent;
	int size;

	BST_Node()
	{
		this->empty = true;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->height = 0;
		this->size = 0;
	}
	
	BST_Node(const T& element)
	{
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->data = element;
		this->empty = false;
		this->height = 1;
		this->size = 1;
	}
	
	~BST_Node()
	{
		delete this->right;
		delete this->left;
	}

	virtual BST_Node<T>* Find(const T& value);

	virtual BST_Node<T>* Min();
	virtual BST_Node<T>* Max();

	virtual BST_Node<T>* Next();
	virtual BST_Node<T>* Prev();

	virtual BST_Node<T>* Insert(const T& value);
	BST_Node<T>* Delete(BST_Node<T>* toDelete);
	virtual BST_Node<T>* erase(const T& value); 

	virtual T operator *()
	{
		return this->data;
	}
};

template<class T>
BST_Node<T>* BST_Node<T>::Find(const T& value)
{
	if (!this)
	{
		return NULL;
	}
	
	if (this->empty)
	{
		return NULL;
	}
	
	if (this->data == value)
		return this;
	else if (this->data < value)
	{
		if (this->right)
			return this->right->Find(value);
		return NULL;
	}
	else
	{
		if (this->left)
			return this->left->Find(value);
		return NULL;
	}
}

template<class T>
BST_Node<T>* BST_Node<T>::Insert(const T& value)
{
	if (this->empty)
	{
		this->empty = false;
		this->data = value;
		this->height = 1;
		this->size = 1;
		return this;
	}
	
	BST_Node<T>* Parent = this->parent;
	BST_Node<T>* cur = this; 
	while (cur)
	{
		Parent = cur;
		if (value == cur->data)
		{	
			return cur;
		}
		
		if (value >= cur->data)
		{
			cur = cur->right;
		}
		else
		{
			cur = cur->left;
		}
	}

	BST_Node<T>* new_vertex = new BST_Node<T>(value);
	new_vertex->parent = Parent;
	if (value > Parent->data)
	{
		Parent->right = new_vertex;
	}
	else
	{
		Parent->left = new_vertex;
	}
	
	cur = new_vertex;
	while (cur)
	{
		cur->height = max<int>((cur->left) ? (cur->left->height) : 0, (cur->right) ? (cur->right->height) : 0) + 1;
		cur->size = ((cur->left) ? (cur->left->size) : 0) + ((cur->right) ? (cur->right->size) : 0) + 1;
		cur = cur->parent;
	}

	return new_vertex;
}

template<class T>
BST_Node<T>* BST_Node<T>::Min() 
{
	BST_Node<T>* cur = this;
	while (cur->left)
	{
		cur = cur->left;
	}
	return cur;
}

template<class T>
BST_Node<T>* BST_Node<T>::Max() 
{
	BST_Node<T>* cur = this;
	if (!cur)
	{
		return NULL;
	}
	
	while (cur->right)
	{
		cur = cur->right;
	}
	return cur;
}

template<class T>
BST_Node<T>* BST_Node<T>::Next() 
{
	if (!this)
	{
		return NULL;
	}
	
	BST_Node<T>* cur = this;
	if (cur->right)
	{
		return cur->right->Min();
	}
	
	BST_Node<T>* Parent = cur->parent;
	while (Parent && cur == Parent->right)
	{
		cur = Parent;
		Parent = Parent->parent;
	}
	return cur;
}

template<class T>
BST_Node<T>* BST_Node<T>::Prev()
{
	if (!this)
	{
		return NULL;
	}
	BST_Node<T>* cur = this;
	if (cur->right)
	{
		return cur->left->Max();
	}
	BST_Node<T>* Parent = cur->parent;
	while (Parent && cur == Parent->left)
	{
		cur = Parent;
		Parent = Parent->parent;
	}
	return cur;
}

template<class T>
BST_Node<T>* BST_Node<T>::Delete(BST_Node<T>* toDelete)
{
	if (!toDelete)
	{
		return NULL;
	}
	
	if (toDelete->left == NULL && toDelete->right == NULL)
	{
		if (!toDelete->parent)
		{
			toDelete->empty = true;
			toDelete->height = 0;
			toDelete->size = 1;
			return this;
		}
		else
		{
			BST_Node<T>* cur_vertex = toDelete->parent;
			BST_Node<T>* parent = toDelete->parent;
			if (toDelete->parent->data <= toDelete->data)
			{
				toDelete->parent->right = NULL;
				toDelete->parent = NULL;
				assert(!toDelete->left && !toDelete->right);
				delete toDelete;
			}
			else
			{
				toDelete->parent->left = NULL;
				toDelete->parent = NULL;
				assert(!toDelete->left && !toDelete->right);
				delete toDelete;
			}
			
			while (cur_vertex)
			{
				cur_vertex->height = max<int>((cur_vertex->right) ? (cur_vertex->right->height) : 0, (cur_vertex->left) ? (cur_vertex->left->height) : 0) +1;
				cur_vertex->size = ((cur_vertex->left) ? (cur_vertex->left->size) : 0) + ((cur_vertex->right) ? (cur_vertex->right->size) : 0) + 1; 
				cur_vertex = cur_vertex->parent;
			}
			return parent;
		}
	}

	BST_Node<T>* parent = toDelete->parent;
	if (toDelete->right)
	{	
		BST_Node<T>* next = toDelete->Next();
		assert(next->parent);
		if (next->parent != toDelete)
		{
			BST_Node<T>* cur = next->parent;
			toDelete->data = next->data;
			if (next->right)
			{
				next->right->parent = next->parent;
				next->parent->left = next->right;
			}
			else
			{
				next->parent->left = NULL;
			}
			
			assert(!next->left);
			next->right = NULL;
			BST_Node<T>* next_parent = next->parent;
			delete next; 
			while (cur)
			{
				cur->height = max<int>((cur->left) ? (cur->left->height) : 0, (cur->right) ? (cur->right->height) : 0) + 1;
				cur->size = ((cur->left) ? (cur->left->size) : 0) + ((cur->right) ? (cur->right->size) : 0) + 1;
				cur = cur->parent;
			}
			return next_parent;
		}
		else
		{
			assert(next->parent == toDelete);
			if (parent)
			{
				BST_Node<T>* cur = next;
				next->parent = parent;
				if (parent->data <= toDelete->data)
				{
					parent->right = next;
				}
				else
				{
					parent->left = next;
				}
				
				if (toDelete->left)
				{
					next->left = toDelete->left;
					toDelete->left->parent = next;
				}
				else
				{
					next->left = NULL;
				}
				
				toDelete->left = toDelete->right = NULL;
				delete toDelete;
				
				while (cur)
				{
					cur->height = max<int>((cur->left) ? (cur->left->height) : 0, (cur->right) ? (cur->right->height) : 0) + 1;
					cur->size = ((cur->left) ? (cur->left->size) : 0) + ((cur->right) ? (cur->right->size) : 0) + 1;
					cur = cur->parent;
				}
				return parent;
			}
			else
			{
				assert(this == next->parent);
				this->right = next->right;
				if (next->right)
				{
					next->right->parent = this;
				}
				this->data = next->data;
				next->left = next->right = NULL;
				delete next;
				this->height = max<int>((this->left) ? (this->left->height) : 0, (this->right) ? (this->right->height) : 0) + 1;
				this->size = ((this->left) ? (this->left->size) : 0) + ((this->right) ? (this->right->size) : 0) + 1;
				return this;
			}
		}
	}
	else
	{
		BST_Node<T>* child = toDelete->left; 
		if (parent)
		{						
			if (parent->data <= toDelete->data)
			{
				parent->right = child;
			}
			else
			{
				parent->left = child;
			}
			
			child->parent = parent;
			assert(!toDelete->right);
			BST_Node<T>* cur = toDelete->parent;
			toDelete->left = NULL;
			toDelete->right = NULL;
			toDelete->parent = NULL;
			delete toDelete;
			
			while (cur)
			{
				cur->height = max<int>((cur->left) ? (cur->left->height) : 0, (cur->right) ? (cur->right->height) : 0) + 1;
				cur->size = ((cur->left) ? (cur->left->size) : 0) + ((cur->right) ? (cur->right->size) : 0) + 1;
				cur = cur->parent;
			}
			return parent;
		}
		else
		{
			assert(toDelete == this);
			this->data = child->data;
			this->left = child->left;
			this->right = child->right;
			this->height = child->height;
			this->size = child->size;
			if (child->left)
			{
				child->left->parent = this;
			}
			if (child ->right)
			{
				child->right->parent = this;
			}
			child->left = NULL;
			child->right = NULL;
			delete child;
			return this;
		}
	}
}

template<class T>
BST_Node<T>* BST_Node<T>::erase(const T& value)
{
	return this->Delete(this->Find(value));
}


template<class T>
class AVL_Tree : public BST_Node<T> 
{
public:
	AVL_Tree<T>* Left()
	{
		if (this->left)
		{
			return static_cast<AVL_Tree<T>*>(this->left);
		}
		return NULL;
	}

	AVL_Tree <T>* Right()
	{
		if (this->right)
		{
			return static_cast<AVL_Tree<T>*>(this->right);
		}
		return NULL;
	}
	AVL_Tree <T>* Parent()
	{
		if (this->parent)
		{
			return static_cast<AVL_Tree<T>* > (this->parent);
		}
		return NULL;
	}

	int get_height()
	{
		if (!this)
		{
			return 0;
		}
		return this->height;
	}
	int get_size() 
	{
		if (!this) 
		{
			return 0;
		}
		return this->size;
	}

	int difference() 
	{
		if (!this)
		{
			return 0;
		}
		int left_height = (this->left)?(this->Left()->get_height()):0;
		int right_height = (this->right)?(this->Right()->get_height()):0;
		return right_height - left_height;
	}
	
	void fix_height() 
	{
		if (!this)
		{
			return;
		}
		int left_height = (this->left) ? (this->Left()->get_height()) : 0;
		int right_height = (this->right) ? (this->Right()->get_height()) : 0;
		int left_size = (this->left) ? (this->Left()->get_size()) : 0;
		int right_size = (this->right) ? (this->Right()->get_size()): 0;

		this->size = left_size + right_size + 1;
		this->height = max<int>(left_height, right_height) + 1;
	}
	AVL_Tree<T>* right_rotate();
	AVL_Tree<T>* left_rotate();
	bool balancing_node();
	AVL_Tree<T>* balancing_tree(AVL_Tree<T>* from);
	AVL_Tree<T>* Insert(const T& value);
	AVL_Tree<T>* erase (const T& value);
	AVL_Tree<T>* Prev();
	AVL_Tree<T>* Next();
	AVL_Tree<T>* Find(const T& value);
	T find_kth(int number);
	T operator *()
	{
		return this->data;
	}
};

template<class T>
AVL_Tree<T>* AVL_Tree<T>::left_rotate()
{
	AVL_Tree<T>* for_rotating = this->Right(); 
	AVL_Tree<T>* parent = this->Parent();
	this->right = for_rotating->left;
	if (this->right)
	{
		this->right->parent = this;	
	}
	for_rotating->left = this;
	this->parent = for_rotating;
	for_rotating->parent = parent;
	if (parent)
	{
		if (for_rotating->data >= parent->data)
		{
			parent->right = for_rotating;
		}
		else
		{
			parent->left = for_rotating;
		}
	}
	this->fix_height();
	for_rotating->fix_height();
	return for_rotating;
}

template<class T>
AVL_Tree<T>* AVL_Tree <T>::right_rotate()
{
	AVL_Tree<T>* for_rotating = this->Left();
	AVL_Tree<T>* parent  = this->Parent();
	this->left = for_rotating->right;
	if (this->left)
	{
		this->left->parent = this;
	}
	for_rotating->right = this;
	this->parent = for_rotating;
	for_rotating->parent = parent;
	if (parent)
	{
		if (for_rotating->data >= parent->data)
		{
			parent->right = for_rotating;
		}
		else
		{
			parent->left = for_rotating;
		}
	}
	this->fix_height();
	for_rotating->fix_height();
	return for_rotating;
}

template<class T>
bool AVL_Tree<T>::balancing_node()
{
	this->fix_height();
	if ((this->difference()) == 2)
	{
		if (this->Right()->difference() < 0)
		{
			this->right = this->Right()->right_rotate();
		}
		this->left_rotate();
		return true;
	}
	if ((this->difference()) == -2)
	{
		if (this->Left()->difference() > 0)
		{
			this->left = this->Left()->left_rotate();
		}
		this->right_rotate();
		return true;
	}
	return false;
}

template<class T>
AVL_Tree<T>* AVL_Tree<T>::balancing_tree(AVL_Tree<T>* from)
{
	if (!from)
	{
		return from;
	}
	while (from->parent && from->balancing_node())
	{
		from = static_cast<AVL_Tree*>(from->parent);
	}
	return from;
}

template<class T>
AVL_Tree<T>* AVL_Tree<T>::Insert(const T& value)
{
	AVL_Tree* current = static_cast<AVL_Tree*>(BST_Node<T>::Insert(value));
	return this->balancing_tree(current);
}

template<class T>
AVL_Tree<T>* AVL_Tree<T>::erase(const T& value)
{
	AVL_Tree* current = static_cast<AVL_Tree*>(BST_Node<T>::erase(value));
	return this->balancing_tree(current);
}

template<class T>
AVL_Tree<T>* AVL_Tree<T>::Prev()
{
	return static_cast<AVL_Tree<T>*>(this->BST_Node<T>::Prev());
}

template<class T>
AVL_Tree<T>* AVL_Tree<T>::Next()
{
	return static_cast<AVL_Tree<T>*>(this->BST_Node<T>::Next());
}

template<class T>
AVL_Tree<T>* AVL_Tree<T>::Find(const T& value)
{
	BST_Node<T>* that = BST_Node<T>::Find(value);
	if (that)
	{
		return static_cast<AVL_Tree<T>*>(that);
	}
	return NULL;
}

template<class T>
T AVL_Tree<T>::find_kth(int number) 
{
	if (number < 0) 
	{
		throw runtime_error("Small number");
	} else if (number > this->size) 
	{
		throw runtime_error("Big number");
	}
	
	AVL_Tree<T>* left_node = Left();
	AVL_Tree<T>* right_node = Right();
	int left_size = 0;
	int right_size = 0;
	if (left_node != NULL) 
	{
		left_size = left_node->get_size();
	}
	if (right_node != NULL) 
	{
		right_size = right_node->get_size();
	}
	if (left_size == number - 1) 
	{
		return this->data;
	}
	if (left_size > number - 1) 
	{
		return left_node->find_kth(number);
	} 
	else 
	{
		return right_node->find_kth(number - left_size - 1);
	}
}





int main()
{
	int number_of_queries;
	cin >> number_of_queries;

	AVL_Tree<int> tree;
	for (int index = 0; index < number_of_queries; ++index) 
	{
		int number;
		cin >> number;
		int statistic;
		cin >> statistic;
		statistic++; 
		if (number > 0) 
		{
			tree.Insert(number);
		} 
		else 
		{
			number = -number;
			tree.erase(number);
		}
		cout << tree.find_kth(statistic) << "\n";
	}

	return 0;
}