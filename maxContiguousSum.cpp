#include <iostream>
using namespace std;
//finding the maximum sum for a contiguous part of the array
int maxSum(int* arr, size_t sz)
{
	int maxInterSum = -1000, maxSum = -1000;

	for(int i = 0; i<sz; i++)
	{
		if(maxInterSum < 0)
		{
			maxInterSum = arr[i];
		}
		else
		{
			maxInterSum += arr[i];
		}

		if(maxInterSum>maxSum)
		{
			maxSum = maxInterSum;
		}
	}

	return maxSum;
	
}

int main()
{
	size_t sz = 7;
	int a[] = {  -3 , -4, 4, 2, 5, 3, 4};
	cout << "the max sum was " << maxSum(a, sz) << endl;
	return 0;
}