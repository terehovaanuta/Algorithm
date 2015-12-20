#include "stdio.h"
#include "stdlib.h"
#include <malloc.h>

int search_index_top (int *arr, int count)
{
	int i = 0;
	int index = i;
	int start_index = i;
	int finish_index = count-1;
	int max_found = 0;
	int left;
	int right;
	
	while ((max_found == 0) && ((start_index + 3) <= finish_index))
	{
		if (arr[start_index] < arr[start_index+1])
		{
			if (arr[start_index + 1]>arr[start_index + 2])
			{
				index = start_index + 1;
				max_found = 1;
			}
			
		}
		else
		{
			index = start_index;
			max_found = 1;
		}

		i = 1;
		do
		{
			i *= 2;
			
			if (start_index + 2*i <= finish_index)
			{
				right = start_index + 2*i;
			}
			else
			{
				right = finish_index;
			}
		}
		while (arr[right] > arr[right-1] && (right < finish_index));
		
		finish_index = right;
		start_index += i;	
			
	}

	if (max_found == 0)
	{
		switch(finish_index - start_index)
		{
			case 2:
				if (arr[start_index] < arr[start_index+1])
				{
					if (arr[start_index + 1] < arr[start_index + 2])
					{
						index = start_index + 2;
					}
					else
					{
						index = start_index + 1;
					}
				}
				else
				{
					index = start_index;
				}	
				break;
			case 0:
				return start_index;
			case 1:
				if (arr[start_index] < arr[start_index+1])
				{
					index = start_index + 1;
				}
				else
				{
					index = start_index;
				}	
				break; 
		}
	}	

	return index;
};


int main ()
{
	int n;
	int index;
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