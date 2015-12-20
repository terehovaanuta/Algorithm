#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
struct coordinate
{
	float X;
	float Y;
};

bool lessPoint(const coordinate& lhs, const coordinate& rhs) 
{
    if (lhs.X < rhs.X) 
    {
        return true;
    }
    
    if (lhs.X > rhs.X) 
    {
        return false;
    }
    
    return lhs.Y < rhs.Y;
}

int main ()
{
	int size_arr = 0;
	
	cin >> size_arr;
	coordinate *point = new coordinate [size_arr];
	
	for (int i = 0; i < size_arr; i++)
	{
		cin >> point[i].X;
		cin >> point[i].Y;
	}
	
    sort(point, point + size_arr, &lessPoint);

	for ( int i = 0; i < size_arr; i++)
	{
    	cout << point[i].X << " ";
		cout << point[i].Y << endl;
	}
  	return 0;
}
