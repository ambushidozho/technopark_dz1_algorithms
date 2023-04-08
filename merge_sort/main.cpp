#include <iostream>
#include <sstream>
//#define DEBUG
template <typename T, typename Comparator = std::less<int>>
void merge(T* arr, int left, int middle, int right, Comparator cmp)
{
	int size = right;
	int left_temp_size = middle - left + 1;
	int right_temp_size = right - middle;
	T* left_temp_arr = new T[left_temp_size];
	T* right_temp_arr = new T[right_temp_size];
	for (auto i = 0; i < left_temp_size; i++)
	{
		left_temp_arr[i] = arr[left + i];
	}
	for (auto j = 0; j < right_temp_size; j++)
	{
		right_temp_arr[j] = arr[middle + 1 + j];
	}
	int left_It = 0;
	int right_It = 0;
	int merge_It = left;

	while (left_It < left_temp_size && right_It < right_temp_size)
	{
		if (cmp(left_temp_arr[left_It], right_temp_arr[right_It]))
		{
			arr[merge_It] = left_temp_arr[left_It];
			left_It++;
		}
		else {
			arr[merge_It] = right_temp_arr[right_It];
			right_It++;
		}
		merge_It++;
	}
	while (left_It < left_temp_size) {
		arr[merge_It] = left_temp_arr[left_It];
		left_It++;
		merge_It++;
	}
	while (right_It < right_temp_size) {
		arr[merge_It]
			= right_temp_arr[right_It];
		right_It++;
		merge_It++;
	}
	delete[] left_temp_arr;
	delete[] right_temp_arr;
}

template <typename T, typename Comparator = std::less<T>>
void merge_sort(T* arr, int left, int right, Comparator cmp = Comparator())
{
	if (left >= right)
		return;

	int middle = left + (right - left) / 2;

	merge_sort(arr, left, middle, cmp);
	merge_sort(arr, middle + 1, right, cmp);
	merge(arr, left, middle, right, cmp);
}



class Customer
{
public:
	Customer()
	{
		in_time = 0;
		out_time = 0;
		second_ad = 0;
	}
	Customer(int in_time, int out_time)
	{
		this->in_time = in_time;
		this->out_time = out_time;
		second_ad = out_time;
	}
	int in_time;
	int out_time;
	int second_ad;
};

class CustomerComparator
{
public:
	bool operator()(const Customer& l, const Customer& r)
	{
		if (l.out_time == r.out_time)
		{
			return l.in_time > r.in_time;
		}
		else
		{
			return l.out_time < r.out_time;
		}
	}
};

int run(std::istream& input, std::ostream& output)
{
	unsigned int n;
	input >> n;
	Customer* arr = new Customer[n];
	CustomerComparator cmp;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		input >> a >> b;
		if (a >= b)
			return -1;
		Customer c(a, b);
		arr[i] = c;
	}
	merge_sort(arr, 0, n - 1, cmp);
	

	unsigned int ads = 2;
	if (n == 0)
		ads = 0;
	int last_ad = arr[0].second_ad;
	for (int i = 1; i < n; i++)
	{
		if (arr[i].out_time == last_ad)
			continue;
		else if (arr[i].in_time > last_ad)
			ads += 2;
		else if (arr[i].in_time <= last_ad - 1)
			continue;
		else if (arr[i].in_time == last_ad)
			ads++;
		last_ad = arr[i].second_ad;
	}
	output << ads;
	delete[] arr;
	return 0;
}
#ifdef DEBUG
void test1()
{
	std::stringstream input;
	input << "5\n";
	input << "5 10\n";
	input << "2 10\n";
	input << "3 10\n";
	input << "10 14\n";
	input << "9 11\n";
	run(input, std::cout);
}
void test2()
{
	std::stringstream input;
	input << "5\n";
	input << "1 3\n";
	input << "4 5\n";
	input << "5 6\n";
	input << "7 8\n";
	input << "9 11\n";
	run(input, std::cout);
}
void test3()
{
	std::stringstream input;
	input << "1\n";
	input << "1 3\n";
	run(input, std::cout);
}
void test4()
{
	std::stringstream input;
	input << "5\n";
	input << "0 10\n";
	input << "9 10\n";
	input << "10 11\n";
	input << "7 8\n";
	input << "0 20\n";
	run(input, std::cout);
}
void test5()
{
	std::stringstream input;
	input << "0\n";
	run(input, std::cout);
}
void test6()
{
	std::stringstream input;
	input << "6\n";
	input << "5 10\n";
	input << "3 6\n";
	input << "0 2\n";
	input << "4 5\n";
	input << "9 11\n";
	input << "10 11\n";
	run(input, std::cout);
}
void test7()
{
	std::stringstream input;
	input << "4\n";
	input << "-5 9\n";
	input << "-1 0\n";
	input << "-3 -1\n";
	input << "0 1\n";
	run(input, std::cout);
}
void test8()
{
	std::stringstream input;
	input << "4\n";
	input << "3 4\n";
	input << "2 4\n";
	input << "1 4\n";
	input << "5 6\n";
	run(input, std::cout);
}
#endif // DEBUG
int main(int argc, char* argv[])
{
#ifdef DEBUG
	test1();
	std::cout << std::endl << "=========================" << std::endl;
	test2();
	std::cout << std::endl << "=========================" << std::endl;
	test3();
	std::cout << std::endl << "=========================" << std::endl;
	test4();
	std::cout << std::endl << "=========================" << std::endl;
	test5();
	std::cout << std::endl << "=========================" << std::endl;
	test6();
	std::cout << std::endl << "=========================" << std::endl;
	test7();
	std::cout << std::endl << "=========================" << std::endl;
	test8();
	std::cout << std::endl << "=========================" << std::endl;
	return 0;
#else // DEBUG
	return run(std::cin, std::cout);
#endif


}