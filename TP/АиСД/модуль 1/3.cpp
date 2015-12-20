#include "stdio.h"
#include "stdlib.h"
#include <malloc.h>

int find_index_bin(int *arr, int start_index, int finish_index) 
{
    int index_top = 0;
    while (finish_index - start_index > 1 ) 
    {
        index_top = (start_index + finish_index) / 2;
       
        if (arr[index_top] < arr[index_top + 1])
        {
        	start_index = index_top;
        }
        else
        {
            finish_index = index_top;
        }
    }
    return (arr[finish_index] > arr[start_index]) ? finish_index : start_index;
}


int search_index_top (int *arr, int count)
{
	int i = 0;
	int index = i;
	int start_index = i;
	int finish_index = count-1;


	if (arr[start_index] > arr[start_index + 1])
	{
		return start_index;
	}

	if (arr[finish_index] > arr[finish_index - 1])
	{
		return finish_index;
	}

	i = 1;
    while (i < count && arr[2 * i - 1] < arr[2 * i]) 
    {
        i *= 2;
    }
    
    if (2*i < count)
    {
        return find_index_bin(arr, i, 2 * i);
    }
    else
    {
    	return find_index_bin(arr, i/2, count);
    }
};

int main ()
{
	int n = 0;
	int index = 0;
	scanf("%d", &n);

	int *arr_A;
	arr_A = (int*) malloc(n*sizeof(int));

	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr_A[i]);
	}

	if ( n == 0 )
		return 1;
	
	index = search_index_top(arr_A, n);
	printf("%d\n", index);

	free(arr_A);
	return 0;
}