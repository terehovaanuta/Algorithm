#include <iostream>
#include <string>
#include <vector>

#define HASH_PARAMETER_A 37
#define HASH_PARAMETER_B 59
#define INITIAL_SIZE 8
#define RESIZE_KOEFF 3.0/4.0

using namespace std;

struct TableElement 
{
    TableElement(const string &s) : data(s), isDeleted(false) { }

    string data;
    bool isDeleted;
};

int hashA(const string &s, int m) 
{
    int result = 0;
    for (int i = 0; i < s.length(); ++i) 
    {
        result = (result * HASH_PARAMETER_A + s[i]) % m;
    }
    return result;
}

int hashB(const string &s, int m) 
{
    int result = 0;
    for (int i = 0; i < s.length(); ++i) 
    {
        result = (result * HASH_PARAMETER_B + s[i]) % m;
    }
    return (2 * result + 1) % m;
}


class CHashTable 
{
public:
    CHashTable(): table(INITIAL_SIZE, NULL), size(INITIAL_SIZE), realSize(0){};

	bool add(const string &s) 
	{
	    if ((float) realSize / (float) size >= RESIZE_KOEFF) 
	    {
	        rehash();
	    }
	    
	    int currentHash = hashA(s, size);
	    int anotherHash = hashB(s, size);
	    int i = 0;
	    int firstDeletedElement = -1;
	    while (table[currentHash] != NULL && i < size) 
	    {
	        if (table[currentHash]->data == s && !table[currentHash]->isDeleted) 
	        {
	            return false;
	        }
	        
	        if (table[currentHash]->isDeleted && firstDeletedElement < 0) 
	        {
	            firstDeletedElement = currentHash;
	        }
	        
	        currentHash = (currentHash + anotherHash) % size;
	        ++i;
	    }

	    if (firstDeletedElement < 0) 
	    {
	        table[currentHash] = new TableElement(s);
	    } 
	    else 
	    {
	        table[firstDeletedElement]->data = s;
	        table[firstDeletedElement]->isDeleted = false;
	    }
	    
	    realSize++;
	    return true;
	}

	bool remove(const string &s) 
	{
	    int currentHash = hashA(s, size);
	    int anotherHash = hashB(s, size);
	    int i = 0;
	    while (table[currentHash] != NULL && i < size) 
	    {
	        if (table[currentHash]->data == s && !table[currentHash]->isDeleted) 
	        {
	            table[currentHash]->isDeleted = true;
	            realSize--;
	            return true;
	        }
	        
	        currentHash = (currentHash + anotherHash) % size;
	        ++i;
	    }

	    return false;
	}

	bool has(const string &s) 
	{
	    int currentHash = hashA(s, size);
	    int anotherHash = hashB(s, size);
	    int i = 0;
	    while (table[currentHash] != NULL && i < size) 
	    {
	        if (table[currentHash]->data == s && !table[currentHash]->isDeleted) 
	        {
	            return true;
	        }
	        
	        currentHash = (currentHash + anotherHash) % size;
	        ++i;
	    }
	    return false;
	}

private:
    vector<TableElement *> table;
    int size; 
    int realSize;

	void rehash() 
	{
	    int newSize = size * 2;
	    vector<TableElement *> newTable(newSize, NULL);
	    for (int i = 0; i < size; ++i) 
	    {
	        if (table[i] != NULL && !table[i]->isDeleted) 
	        {
	            string data = table[i]->data;
	            int currentHash = hashA(data, newSize);
	            int anotherHash = hashB(data, newSize);
	            int j = 0;

	            while (newTable[currentHash] != NULL && j < newSize) 
	            {
	                currentHash = (currentHash + anotherHash) % newSize;
	                ++j;
	            }

	            newTable[currentHash] = new TableElement(data);
	        }
	    }

	    table = newTable;
	    size = newSize;
	}
};


void performCommand(char const command, string const &s, CHashTable &table) 
{
    bool result;
    switch (command) 
    {
        case '+':
            result = table.add(s);
            break;
        case '-':
            result = table.remove(s);
            break;
        case '?':
            result = table.has(s);
            break;
        default:
            result = false;
    }

    if (result) 
    {
        cout << "OK" << endl;
    } else 
    {
        cout << "FAIL" << endl;
    }
}


int main() 
{
    char command;
    string data;
    CHashTable table;

    while (cin >> command >> data) 
    {
        performCommand(command, data, table);
    }

    return 0;
}