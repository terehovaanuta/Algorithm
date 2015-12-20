#include "stdio.h"
#include "stdlib.h"


class queue 
{
public:
	queue( int size );
	~queue() { delete[] buffer; }
	bool push( int a );
	int pop(); 
	bool IsEmpty() const { return head == tail; }

private:
	bool Resize();
	int* buffer;
	int bufferSize;
	int head;
	int tail; 
};

bool queue::Resize()
{
	int bufferSize_new = bufferSize * 2;
	int* buffer_new = new  int[(unsigned long)bufferSize_new];
	int  j = 0;

	if (head == 0)
	{
		
		for (int i = 0; i < tail; i++)
		{
			buffer_new[i] = buffer[i];
			j++;
		}
	}
	else 
	{
		for (int i = head; i < bufferSize; ++i)
		{
			buffer_new[j] = buffer[i];
			j++;
		}

		for (int i = 0; i < tail; i++)
		{
			buffer_new[j] = buffer[i];
			j++;
		}
	}
	delete [] buffer;
	buffer = buffer_new;
	bufferSize *= 2;
	head = 0;
	tail = j;

	return true;
}

queue::queue( int size ) : head( 0 ), tail( 0 )
{
	if (size<4)
		size = 4;
	buffer = new int[(unsigned long)size]; 
	bufferSize = size;

}


bool queue::push( int a )
{
	if (tail == (head - 1) % bufferSize)
		if (!Resize())
			return false;
	buffer[tail] = a;
	tail = ( tail + 1 ) % bufferSize;
	return true;
}


int queue::pop()
{
	if (head == tail)
		return -1;
	int result = buffer[head];
	head = ( head + 1 ) % bufferSize;
	return result;
}


int main()
{
	int n;
	int command;
	int element;
	int flag = 1;

	queue queue_dinam(8);

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &command);
		scanf("%d", &element);
		switch (command)
		{
			case 2:
				if (queue_dinam.pop() != element)
				{
					flag = 0;
				}
				break;
			case 3:
				queue_dinam.push(element);
				break; 
			default:
				flag = 0;
				break;
		}
	}

	if (flag == 1)
	{
		printf("%s\n", "YES");
	}
	else 
	{
		printf("%s\n", "NO");
	}

	return 0;
}