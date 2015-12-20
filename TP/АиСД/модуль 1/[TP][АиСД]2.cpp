#include "stdio.h"
#include "stdlib.h"
#include <malloc.h>

int Search_maximum_pair_of_indices (int *arr_A, int *arr_B, int n, int& A_max_id, int& B_max_id, int& B_old_max_id)
{
	int max_sum;
	A_max_id = B_max_id = B_old_max_id = n-1;
	max_sum = arr_A[A_max_id] + arr_B[B_old_max_id];
		
	for (int i = n-2; i >= 0; i--)
	{
		if (arr_A[i] >= arr_A[A_max_id])
		{
			max_sum = max_sum - arr_A[A_max_id] + arr_A[i];	
			A_max_id = i;
		}

		if (arr_B[i] >= arr_B[B_max_id]) 
		{
			B_max_id = i;
		}

		if (arr_A[i] + arr_B[B_max_id] >= max_sum)
		{
			max_sum = arr_B[B_max_id] + arr_A[i];
			B_old_max_id = B_max_id;
			A_max_id = i;
		}
	}
	return max_sum;
};

int main()
{
	int n;
	int A_max_id;
	int B_max_id;
	int B_old_max_id;
	int max_sum;
	scanf("%d", &n);
	if (n != 0)
	{
		int *arr_A;
		arr_A = (int*) malloc(n*sizeof(int));
		for (int i = 0; i < n; i++)
			scanf ("%d", &arr_A[i]);
		
		int *arr_B;
		arr_B = (int*) malloc(n*sizeof(int));
		for (int i = 0; i < n; i++)
			scanf("%d", &arr_B[i]);
	
		max_sum = Search_maximum_pair_of_indices (arr_A, arr_B, n, A_max_id, B_max_id, B_old_max_id);
		printf("%d%s%d\n", A_max_id, " ", B_old_max_id);
	}
	return 0;
}