#include <iostream>
#include <sstream>
int binary_search(const int* A, int left, int right, const int target)
{
	if (left > right)
		return -1;
	int middle = (right + left) / 2;
	if (A[middle] == target)
		return middle;
	else if (target > A[middle])
	{
		return binary_search(A, middle + 1, right, target);
	}
	else
	{
		return binary_search(A, left, middle - 1, target);
	}
}
int search(int* A, int n, int target, int& left_bound, int& right_bound)
{
	while (A[right_bound] < target && right_bound < n)
	{
		right_bound *= 2;
		if (right_bound > n - 1)
			right_bound = n - 1;
	}
	return binary_search(A, left_bound, right_bound, target);
}

void run(std::istream& input, std::ostream& output)
{
	int n, m;
	input >> n >> m;
	int* A = new int[n];
	int* B = new int[m];
	for (int i = 0; i < n; i++)
	{
		input >> A[i];
	}
	for (int i = 0; i < m; i++)
	{
		input >> B[i];
	}
	int left_bound = 0;
	int right_bound = 1;
	for (int i = 0; i < m; i++)
	{
		if (A[n - 1] < B[i])
		{
			break;
		}
		int index = search(A, n, B[i], left_bound, right_bound);
		if (index != -1)
		{
			left_bound = index + 1;
			if (right_bound < left_bound)
			{
				right_bound = left_bound;
			}
			output << A[index];
			if (i != m - 1)
				output << " ";
		}

	}
	delete[] A;
	delete[] B;
}

int main()
{
	run(std::cin, std::cout);
	return 0;
}

