#include <iostream>

using namespace std;

bool compare_ints(const int& L, const int& R) 
{
    return L < R;
}


template <class T>
T median_of_three(T* arr, int l, int r, bool (*is_less)(const T&, const T&)) 
{
    int cntr = (r + l + 1)/2;
    if (is_less(arr[r], arr[l])) 
    {
        swap(arr[r], arr[l]);
    }

    if (is_less(arr[cntr], arr[l])) 
    {
        swap(arr[cntr], arr[l]);
    }

    if (is_less(arr[r], arr[cntr])) 
    {
        swap(arr[r], arr[cntr]);
    }

    swap(arr[cntr], arr[r]);
    return arr[r];
}


template <class T>
int partition(T* arr, int l, int r, bool (*is_less)(const T&, const T&)) 
{
    T pivot = median_of_three<T>(arr, l, r, is_less);
    
    int i = l;
    int j = l + 1;
    int pivot_index = r;
    while (j < pivot_index) 
    {
        if (is_less(pivot, arr[j])) 
        {
            j++ ;
        } 
        else 
        {
            swap(arr[++i ], arr[j++ ]);
        }
    }
    
    if (i + 1 < r) 
    {
        i++ ;
        swap(arr[pivot_index], arr[i]);
    }
    return i;
}


template <class T>
T find_K_stat(T* array, int asize, int k, bool (*is_less)(const T&, const T&)) 
{
    int l = 0;
    int r = asize - 1;
    while (true) 
    {
        int index = partition(array, l, r, is_less);
        if (index == k) 
        {
            return array[k];
        } 
        else if (k < index) 
        {
            r = index;
        } 
        else 
        {
            l = index + 1;
        }
    }
}

int main() 
{
    int n = 0;
    int k = 0;
    cin >> n >> k;
    int* array = new int[n];
    for (int i = 0; i < n; ++i) 
    {
        cin >> array[i];
    }
    cout << find_K_stat<int>(array, n, k, compare_ints);
    delete [] array;
    return 0;
}