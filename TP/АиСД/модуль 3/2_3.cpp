#include <iostream>
#include <stack>

using std::stack;

template <typename T>
struct Node
{
    T key;
    Node<T>* left;
    Node<T>* right;
};

template <typename T>
void add(Node<T>*& root, T value)
{
    if (!root)
    {
        root = new Node<T>();
        root->key = value;
    } 
    else
    {
        Node<T>* current = root;
        while (true)
        {
            if (value >= current->key)
            {
                if (!current->right)
                {
                    current->right = new Node<T>();
                    current->right->key = value;
                    break;
                }
                current = current->right;
            } 
            else
            {
                if (!current->left)
                {
                    current->left = new Node<T>();
                    current->left->key = value;
                    break;
                }
                current = current->left;
            }
        }
    }
}

template <typename T, typename action_t>
void post_order(Node<T>* root, action_t &action)
{
    if (!root) return;

    stack<Node<T>*> Stack;
    Stack.push(root);
    Node<T>* previous = NULL;
    while (!Stack.empty())
    {
        Node<T>* current = Stack.top();

        if (!previous || previous->left == current || previous->right == current)
        {
            if (current->left)
            {
                Stack.push(current->left);
            } 
            else if (current->right)
            {
                Stack.push(current->right);
            } 
            else
            {
                action(current);
                Stack.pop();
            }
        } 
        else if (current->left == previous) 
        {
            if (current->right) 
            {
                Stack.push(current->right);
            } 
            else 
            {
                action(current);
                Stack.pop();
            }
        }
        else if (current->right == previous) 
        {
            action(current);
            Stack.pop();
        }
        previous = current;
    }
}

template <typename T>
void destroy(Node<T>* current)
{
    delete current;
}

template <typename T>
void print(Node<T>* current)
{
    std::cout << current->key << " ";
}


int main()
{
    int count;
    Node<int>* tree = NULL;

    int value;
    std::cin >> count;
    for (int i = 0; i < count; ++i)
    {
        std::cin >> value;
        add(tree, value);
    }

    post_order(tree, print<int>);
    post_order(tree, destroy<int>);

    return 0;
}