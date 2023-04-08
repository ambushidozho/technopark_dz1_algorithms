#include <iostream>

class ArrayIterator
{
public:
	ArrayIterator()
	{
		size = 0;
		current_pos = 0;
		arr = nullptr;
	}
	ArrayIterator(int* arr, int size)
	{
		this->arr = arr;
		this->size = size;
		current_pos = 0;
	}
	void Clear()
	{
		delete[] arr;
	}
	int* arr;
	int size;
	int current_pos;
};

class ArrayIteratorComparator
{
public:
	bool operator()(const ArrayIterator& l, const ArrayIterator& r)
	{
		return l.arr[l.current_pos] > r.arr[r.current_pos];
	}
};

template <typename T, typename Comparator = std::less<>>
class Heap
{
public:
	Heap()
	{
		init_Heap();
	}
	~Heap()
	{
		delete[] arr;
	}
	void Add(T& value)
	{
		if (size + 1 == capacity)
		{
			realloc(capacity * 2);
		}
		arr[size] = value;
		siftUp(size);
		size++;
	}
	T ExtractTop()
	{
		T temp = arr[0];
		arr[0] = arr[--size];
		siftDown(0);
		return temp;
	}
	T Top()
	{
		return arr[0];
	}
private:
	void init_Heap()
	{
		capacity = 2;
		size = 0;
		arr = new T[capacity];
	}
	void realloc(int new_size)
	{
		T* new_arr = new T[new_size];
		int j = 0;
		for (int i = 0; i < size; i++)
		{
			new_arr[j] = arr[i];
			j++;
		}
		capacity = new_size;
		delete[] arr;
		arr = new_arr;
	}
	void siftDown(int i)
	{
		int left_child;
		int right_child;
		int biggest;
		while (true)
		{
			left_child = 2 * i + 1;
			right_child = 2 * i + 2;
			biggest = i;
			if (left_child < size && cmp(arr[biggest], arr[left_child]))
			{
				biggest = left_child;
			}
			if (right_child < size && cmp(arr[biggest], arr[right_child]))
			{
				biggest = right_child;
			}
			if (biggest == i)
				break;
			std::swap(arr[i], arr[biggest]);
			i = biggest;
		}
	}
	void siftUp(int i)
	{
		int parent;
		int child;
		while (true)
		{
			parent = (i - 1) / 2;
			child = i;
			if (parent >= 0 && cmp(arr[parent], arr[child]))
			{
				std::swap(arr[child], arr[parent]);
			}
			else
				break;
			i = parent;
		}
	}
	T* arr;
	Comparator cmp;
	int size;
	int capacity;
};

int main(int argc, char* argv[])
{
	int k ,n, N = 0;
	std::cin >> k;
	Heap <ArrayIterator, ArrayIteratorComparator> heap;
	for (int i = 0; i < k; i++)
	{
		std::cin >> n;
		N += n;
		int* arr = new int[n];
		for (int i = 0; i < n; i++)
		{
			std::cin >> arr[i];
		}
		ArrayIterator ArrIt(arr, n);
		heap.Add(ArrIt);
	}
	for (int i = 0; i < N; i++)
	{
		auto temp = heap.ExtractTop();
		std::cout << temp.arr[temp.current_pos] << " ";
		if (temp.current_pos == temp.size - 1)
		{
			temp.Clear();
		}
		else
		{
			temp.current_pos++;
			heap.Add(temp);
		}	
	}

	
	

	return 0;
}