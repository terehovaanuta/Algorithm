#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template<class T>
struct CTreapNode 
{
    T data;
    int priority;
    CTreapNode *left;
    CTreapNode *right;

    CTreapNode(T data, int priority) : data(data), left(NULL), right(NULL), priority(priority) { }
};

template<class T>
struct CBinaryNode 
{
    T data;
    CBinaryNode *left;
    CBinaryNode *right;

    CBinaryNode(T data) : data(data), left(NULL), right(NULL) { }
};

template<class T>
struct CBNodePerLevel 
{
    int level;
    CBinaryNode<T> *node;

    CBNodePerLevel(int level, CBinaryNode<T> *node) : level(level), node(node) { }
};

template<class T>
struct CTNodePerLevel 
{
    int level;
    CTreapNode<T> *node;

    CTNodePerLevel(int level, CTreapNode<T> *node) : level(level), node(node) { }
};

template<class T>
void deleteNode(CBinaryNode<T> *node) 
{
    if (node == NULL) 
    {
        return;
    }

    deleteNode(node->left);
    deleteNode(node->right);

    delete node;
}

template<class T>
void deleteNode(CTreapNode<T> *node) 
{
    if (node == NULL) 
    {
        return;
    }

    deleteNode(node->left);
    deleteNode(node->right);

    delete node;
}

template<class T>
class DecartTree 
{
public:
    CTreapNode<T> *root;

    DecartTree() : root(NULL) { };

    ~DecartTree()
    {
       deleteNode(root);
    };

    void add(CTreapNode<T> *&node, T data, int priority) 
    {
        if (node != NULL) 
        {
            if (node->priority < priority) 
            {
                CTreapNode<T> *left = NULL;
                CTreapNode<T> *right = NULL;

                split(node, data, left, right);

                CTreapNode<T> *newNode = new CTreapNode<T>(data, priority);
                newNode->left = left;
                newNode->right = right;

                node = newNode;

                return;
            }
            
            if (node->data > data) 
            {
                add(node->left, data, priority);
            }
            else 
            {
                add(node->right, data, priority);
            }
        } 
        else 
        {
            node = new CTreapNode<T>(data, priority);
        }
    }

    int getMaxCountNodesInLevels() 
    {
        vector<int> nodesNumsPerLevels;
        int sumPerLevel = 0;
        int level = 0;
        queue<CTNodePerLevel<T> *> queue;
        if (root == NULL) 
        {
            return 0;
        }

        queue.push(new CTNodePerLevel<T>(level, root));

        while (!queue.empty()) 
        {

            CTNodePerLevel<T> *node = queue.front();

            if (level == node->level) 
            {
                sumPerLevel++;
            } 
            else 
            {
                nodesNumsPerLevels.push_back(sumPerLevel);
                sumPerLevel = 1;
                level = node->level;
            }

            queue.pop();

            if (node->node->left != NULL) 
            {
                queue.push(new CTNodePerLevel<T>(level + 1, node->node->left));
            }

            if (node->node->right != NULL) 
            {
                queue.push(new CTNodePerLevel<T>(level + 1, node->node->right));
            }

            delete node;
        }

        int max = nodesNumsPerLevels[0];
        for (int i = 1; i < nodesNumsPerLevels.size(); ++i) 
        {
            if (nodesNumsPerLevels[i] > max) 
            {
                max = nodesNumsPerLevels[i];
            }
        }

        return max;
    }

private:
    void split(CTreapNode<T> *currentNode, T data, CTreapNode<T> *&left, CTreapNode<T> *&right) 
    {
        if (currentNode == 0) 
        {
            left = 0;
            right = 0;
        } 
        else if (currentNode->data <= data) 
        {
            split(currentNode->right, data, currentNode->right, right);
            left = currentNode;
        } 
        else 
        {
            split(currentNode->left, data, left, currentNode->left);
            right = currentNode;
        }
    }

    
    CTreapNode<T> *merge(CTreapNode<T> *left, CTreapNode<T> *right) 
    {
        if (left == 0 || right == 0) 
        {
            return left == 0 ? right : left;
        }
        
        if (left->priority > right->priority) 
        {
            left->right = merge(left->right, right);
            return left;
        }
        
        right->left = merge(left, right->left);
        return right;
    }
};


template<class T>
class BinaryTree 
{
public:
    CBinaryNode<T> *root;

    BinaryTree(): root(NULL) { };

    ~BinaryTree()
    {
        deleteNode(root);
    };

    void add(CBinaryNode<T> *&node, T data) 
    {
        if (node != NULL) 
        {
            if (node->data > data) 
            {
                add(node->left, data);
            }
            else 
            {
                add(node->right, data);
            }
        } 
        else 
        {
            node = new CBinaryNode<T>(data);
        }
    }

    int getMaxCountNodesInLevels() 
    {
        vector<int> nodesNumsPerLevels;
        int sumPerLevel = 0;
        int level = 0;
        queue<CBNodePerLevel<T> *> queue;
        if (root == NULL) 
        {
            return 0;
        }

        queue.push(new CBNodePerLevel<T>(level, root));

        while (!queue.empty()) 
        {

            CBNodePerLevel<T> *node = queue.front();

            if (level == node->level) 
            {
                sumPerLevel++;
            } 
            else 
            {
                nodesNumsPerLevels.push_back(sumPerLevel);
                sumPerLevel = 1;
                level = node->level;
            }

            queue.pop();

            if (node->node->left != NULL) 
            {
                queue.push(new CBNodePerLevel<T>(level + 1, node->node->left));
            }

            if (node->node->right != NULL) 
            {
                queue.push(new CBNodePerLevel<T>(level + 1, node->node->right));
            }

            delete node;
        }

        int max = nodesNumsPerLevels[0];
        for (int i = 1; i < nodesNumsPerLevels.size(); ++i) 
        {
            if (nodesNumsPerLevels[i] > max) 
            {
                max = nodesNumsPerLevels[i];
            }
        }

        return max;
    }
};


int main() 
{
    BinaryTree<int> *naiveTree = new BinaryTree<int>();
    DecartTree<int> *decartTree = new DecartTree<int>();

    int n;
    cin >> n;

    int data;
    int priority;

    for (int i = 0; i < n; ++i) 
    {
        cin >> data >> priority;
        naiveTree->add(naiveTree->root, data);
        decartTree->add(decartTree->root, data, priority);
    }

    int decartMaxCount = decartTree->getMaxCountNodesInLevels();
    int naiveMaxCount = naiveTree->getMaxCountNodesInLevels();

    cout << decartMaxCount - naiveMaxCount;

    delete naiveTree;
    delete decartTree;
    return 0;
}