#include <iostream>
//#include <cassert>

//void counting_sort(int* arr, size_t n)
//{
//	assert(arr != nullptr);
//	assert(n > 0);
//	int minVal = arr[0];
//	int maxVal = arr[0];
//	for (int i = 0; i < n; i++)
//	{
//		minVal = std::min(minVal, arr[i]);
//		maxVal = std::max(maxVal, arr[i]);
//	}
//	int countBufsize = maxVal - minVal + 1;
//	int* countBuf = new int[countBufsize]();
//	for (int i = 0; i < n; i++)
//	{
//		countBuf[arr[i] - minVal]++;
//	}
//
//	int* temp = new int[n];
//	for (int i = 1; i < countBufsize; i++)
//	{
//		countBuf[i] += countBuf[i - 1];
//	}
//	for (int i = n - 1; i >= 0; i--)
//	{
//		int countBufPos = arr[i] - minVal;
//		countBuf[countBufPos]--;
//		temp[countBuf[countBufPos]] = arr[i];
//	}
//	for (int i = 0; i < n; i++)
//	{
//		arr[i] = temp[i];
//	}
//	delete[] countBuf;
//	delete[]  temp;
//}

void bin_quick_sort(long long unsigned* arr, int n, int i, int j, int k)
{
	if (i >= j || k < 0)
		return;
	int left = i;
	int right = j;
	while (i < j)
	{
		while (!((arr[i] >> k) & 1) && i < j)
		{
			i++;
		}
		while ((arr[j] >> k) & 1 && j > i)
		{
			j--;
		}	
		std::swap(arr[i], arr[j]);
	}
	// сдвигаем границу на 1 вправо если посередине 0
	if (!((arr[j] >> k) & 1))
		j++;
	bin_quick_sort(arr, n, left, j - 1, k - 1);
	bin_quick_sort(arr, n, j, right, k - 1);
}

int main()
{
	int n;
	std::cin >> n;
	long long unsigned* arr = new long long unsigned[n];
	for (int i = 0; i < n; i++)
	{
		std::cin >> arr[i];
	}
	int i = 0, 
		j = n - 1,
		k = 63;
	bin_quick_sort(arr, n, i, j, k);
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}
	delete[] arr;
}
