#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

void Permute(int* arr, int* permutation, const int n)
{
    if( n == 0)
    {
    	int i = 5;// FIXME: HARD-CODED
    	static int noOfPermutations = 0;
    	noOfPermutations++;
    	for(; i>0; i--)
    	{
    		cout << permutation[i] << ",";
    	}
    	cout << permutation[i] << "\n";
    }
    
    for(int i=0; i<n; i++)
    {
       //cout << "(" << i<< "," << n << ")" << arr[i] << ",";
       permutation[n-1] = arr[i];
       int temp = arr[0];
       arr[0] = arr[i];
       arr[i] = temp;
       Permute(arr+1, permutation, n-1);
       temp = arr[i];
       arr[i] = arr[0];
       arr[0] = temp;
    }
}

int main()
{
    int array[] = {1,2,3,4,5,6};
    const int SIZE = 6;
    int* permutation = new int[SIZE];
    Permute(array, permutation, SIZE);
    return 0;
}
