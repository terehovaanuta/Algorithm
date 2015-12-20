#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

template <class T>
void merge(T *a, int a_len, T *b, int b_len, T *c) 
{
    int i = 0;
    int j = 0;

    for (; i < a_len and j < b_len;) 
    {
        if (a[i] < b[j]) 
        {
            c[i + j] = a[i];
            ++i;
        } 
        else 
        {
            c[i + j] = b[j];
            ++j;
        }
    }

    if (i == a_len) 
    {
        memcpy(c + i + j, b + j, (b_len - j) * sizeof(T));
    } 
    else if (j == b_len) 
    {
        memcpy(c + i + j, a + i, (a_len  - i) * sizeof(T));
    }
}

template <class T>
void mergeSort(T* array, int count) 
{
    T* temp = new T[count];

    for (int i = 1; i < count; i *= 2) 
    {
        int start = 0;
        for (; start + i < count; start += i * 2) 
        {
            merge(array + start, i, array + start + i, std::min(i, count - start - i), temp + start);
        }

        if (start < count) 
        {
            memcpy(temp + start, array + start, (count - start) * sizeof(T));
        }

        memcpy(array, temp, count * sizeof(T));
    }

    delete[] temp;
}

template <class T>
void mergeArraysIntoKElementsArray(vector<T> &array, vector<T> &kElementsArray, const int k) 
{
    mergeSort(array.data(), array.size()); 

    int* temp = new int[kElementsArray.size() + array.size()];
    merge(kElementsArray.data(), kElementsArray.size(), array.data(), array.size(), temp);

    kElementsArray.clear();
    kElementsArray.insert(kElementsArray.begin(), temp, temp + k);

    delete[] temp;
    array.clear();
}

int main() 
{
    int n;
    int k;
    vector<int> array;
    vector<int> sortedFirstKElements;

    cin >> n >> k;

    int num;
    for (int i = 0; i < n; ++i) 
    {
        cin >> num;
        array.push_back(num);

        if (i > 0 && (i + 1) % k == 0 || i == n - 1) 
        {
            mergeArraysIntoKElementsArray(array, sortedFirstKElements, k);
        }
    }

    for (int i = 0; i < k; ++i) 
    {
        cout << sortedFirstKElements[i] << ' ';
    }

    return 0;
}

