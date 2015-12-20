#include "stdio.h"
#include "stdlib.h"

int search_for_the_first_prime_divisor (int n)
{
	for (int i=2; i*i<n; i++)
	{
		if (n%i == 0) 
			return i;
	};
	return 1;
}

int main()
{
	int n = 0;
	int div = 0;
	scanf("%d", &n);
	div = search_for_the_first_prime_divisor(n);
	if (div == 1)
		printf("%d%s%d\n",1, " ", n - 1);
	else
		printf("%d%s%d\n",n/div, " ", n - n/div);
	return 0;
}

