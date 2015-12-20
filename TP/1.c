/*Составить программу определения такой максимальной последовательности среди элементов заданного 
целочисленного массива, элементы которой увеличиваются по порядку. Элементы последовательности функция 
должна вернуть через указатель-параметр, а ее длину — через возвращаемый результат 
Формат входных данных N - длина последовательности A1 ... An - последовательность Формат выходных данных 
N - длинна найденной подпоследовательности A1 ... An - подпоследовательность Если заданная подпоследовательность 
не найдена, или если найдена только вырожденная подпоследовательность(длиной 1), 
необходимо вывести только длину - 0. Программа должна уметь обрабатывать ошибки во входных данных 
(отрицательные числа и др.). В случае возникновения 
ошибки нужно вывести в поток стандартного вывода сообщение "[error]" и завершить выполнение программы.*/
#include <stdio.h>
#include <stdlib.h>

//Вывод данных в формате принимаемом системой тестирования 
void OutputTest( int* IntMas, int size )
{
	printf("%d\n%d", size, *IntMas );
	int i = 1;
	for (; i < size; ++i )
		printf(" %d", IntMas[i] );
	printf("\n");
}

//Получение входных данных и проверка их на наличие ошибок
int* input( int* size )
{
	if( scanf("%d", size ) == 1 )
	{
		if ( *size >= 0 || getchar() == '\n' )
		{
			int* IntMas = (int*) malloc( sizeof(int) * (*size) );
			if ( IntMas != NULL )
			{
				int temp, sym, i = 0;
				for (; i < *size; ++i)
				{
					if( scanf("%d", &temp ) == 1 && ( ( sym = getchar() ) == ' ' || sym == EOF || sym == '\n' ) && temp >= 0 )
					{
						IntMas[i] = temp;
					}
					else
					{
						free( IntMas );
						return NULL;
					}
				}
				return IntMas;
			}
		}
	}	
	return NULL;
}

//Поиск наибольшей по размеру возрастающей последовательности
void SearchSequence( int* IntMas, int Size, int* MIndex, int* MSize )
{
	int i = 0;
	int TempIndex = 0;	//Индекс элемента, с которого началась очередная предпологаемая последовательность
	int TempSize = 1;	//Количество элементов в этой последовательности
	for ( i = 1; i < Size; ++i )
	{
		if( IntMas[i] > IntMas[i-1] )
		{
			++TempSize;
		}
		else
		{
			if( TempSize > *MSize )
			{
				*MSize = TempSize;
				*MIndex = TempIndex;
			}
			TempSize = 1;
			TempIndex = i;
		}
	}
	if( TempSize < *MSize )	//Проверка последней последовательности проводиться отдельно, т.к. i-ого элемента нет.
		return;
	*MSize = TempSize;
	*MIndex = TempIndex;
}


int main()
{
	int N = 0;		//Размер входных данных
	int* IntMas = input(&N);//Входные данные
	if ( IntMas == NULL )
	{
		printf("[error]\n");
		return 0;
	}
	int IndexMaxSequence = 0, SizeMaxSequence = 1;
	SearchSequence( IntMas, N, &IndexMaxSequence, &SizeMaxSequence );
	if ( SizeMaxSequence == 1 )//Допущение 
	{
		free( IntMas );
		printf("0\n");
		return 0;
	}
	OutputTest( &(IntMas[IndexMaxSequence]), SizeMaxSequence );
	free( IntMas );
	return 0;
}
