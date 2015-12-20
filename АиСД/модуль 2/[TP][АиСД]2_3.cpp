#include <iostream>
#include <algorithm>
#include <vector>

using namespace std; 
struct Timetable
{
	int enter;
	int out;

	bool operator<(const Timetable & second) const 
	{
		return (this->enter != second.enter) ? this->enter > second.enter : this->out > second.out;
	}
};

template<class T>
class CHeapSort 
{
public:
	void operator()(T* arr, const int n)
	{
		BildHeap(arr, n);
		for (int i = 0; i < n; i++) 
		{
			T temp;
			temp = ExtractMin(arr, n - i);
			arr[n - i - 1] = temp;
		}
	}

private:
	void SiftDown(T* arr, int i, int n)
	{
		int min = i;
		while (i*2 + 1 < n) 
		{
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			if (left < n && arr[left] < arr[min])
			{
				min = left;
			}

			if (right < n && arr[right] < arr[min])
			{
				min = right;
			}

			if (min != i) 
			{
				swap(arr[i], arr[min]);
				i = min;
			} 
			else 
			{
				return;
			}
		}
	}

	void BildHeap(T* arr, int n)
	{
		for (int i = n/2 - 1; i >= 0; i--) 
		{
			SiftDown(arr, i, n);
		}
	}

	void SiftUp(T* arr, int i)
	{
		while (i > 0)
		{
			int parent = (i - 1)/2;
			if (arr[i] >= arr[parent])
				return;
			swap(arr[i], arr[parent]);
			i = parent;
		}
	}

	T ExtractMin(T* arr, int n)
	{
		T result = arr[0];
		arr[0] = arr[n - 1];
		SiftDown(arr, 0, n - 1);
		return result;
	}
};

int CompileAddView(Timetable* arr, int n)
{
	vector<int> ans(1, 0);
	int minAnsID = -1;

	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < ans.size(); j++) 
		{
			if (arr[i].enter > ans[j]) 
			{
				minAnsID = j;
				break;
			}
		}
		if (minAnsID >= 0) 
		{
			ans[minAnsID] = arr[i].out;
		} 
		else 
		{
			ans.insert(ans.end(), arr[i].out);
		}
		minAnsID = -1;
	}
	return ans.size();
}


int main()
{
	int n = 0;
	cin >> n;
	Timetable* arr = new Timetable[n];
	for (int i = 0; i < n; i++) 
	{
		cin >> arr[i].enter >> arr[i].out;
	}
	CHeapSort<Timetable> Sort;
	Sort(arr, n);
	cout << CompileAddView(arr, n);
	delete arr;
	return 0;
}