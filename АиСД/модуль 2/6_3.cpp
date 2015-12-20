#include <iostream>

using namespace std;

template <class T>
int bit(T element, int order) 
{
    return (element >> order) & 1; 
}

template <class T>
void binaryMSDSort(T* array, int left, int right, int d) 
{
    if (right <= left || d < 0) return;

    int i = left;
    int j = right;

    while (j >= i) 
    {
        for (; bit(array[i], d) == 0 && (i <= right); i++);
        for (; bit(array[j], d) == 1 && (j >= left); j--);
        if (j >= i) 
        {
            swap(array[i], array[j]);
        }
    }

    binaryMSDSort(array, left, i - 1, d - 1);
    binaryMSDSort(array, i, right, d - 1);
}

int main() 
{
    int n;
    cin >> n;
    long long* array = new long long[n];
    for (int i = 0; i < n; ++i) 
    {
        cin >> array[i];
    }

    binaryMSDSort(array, 0, n - 1, 63);

    for (int i = 0; i < n; ++i) 
    {
        cout << array[i] << ' ';
    }

    delete[] array;
    return 0;
}
