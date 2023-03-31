#include <iostream>
template<typename T>
class Deque
{
public:
	Deque()
	{
		buff = nullptr;
		head = 0;
		tail = 0;
		size_ = 0;
		capacity = 0;
	}
	~Deque()
	{
		if (buff)
		{
			delete[] buff;
		}
	}
	void push_back(T value)
	{
		if (capacity == 0)
		{
			create_buf();
		}
		if (size_ + 1 == capacity)
		{
			realloc(mem_size * capacity);
		}
		buff[tail++] = value;
		tail = tail % capacity;
		size_++;
	}
	void push_front(T value)
	{
		if (capacity == 0)
		{
			create_buf();
		}
		if (size_ + 1 == capacity)
		{
			realloc(mem_size * capacity);
		}
		head = (head - 1 + capacity) % capacity;
		buff[head] = value;
		size_++;
	}
	T pop_back()
	{
		if(!empty())
		{
			tail = (tail - 1 + capacity) % capacity;
			T value = buff[tail];
			size_--;
			return value;
		}
		else
		{
			return -1;
		}
	}
	T pop_front()
	{
		if(!empty())
		{
			T value = buff[head];
			head = (head + 1) % capacity;
			size_--;
			return value;
		}
		else
		{
			return -1;
		}
	}
	bool empty()
	{
		if (size_ == 0)
			return true;
		else
			return false;
	}

private:
	void realloc(int size)
	{
		T* new_buff = new T[size];
		int j = 0;
		for(int i = head; i != tail; i = (i + 1) % capacity)
		{
			new_buff[j] = buff[i];
			j++;
		}
		head = 0;
		tail = size_;
		capacity = size;
		delete[] buff;
		buff = new_buff;
	}
	void create_buf()
	{
		capacity = mem_size;
		buff = new T[mem_size];
	}
	unsigned const int mem_size = 2;
	unsigned int size_;
	unsigned int capacity;
	T* buff;
	int head;
	int tail;
};
int main()
{
	Deque<int> dq;
	int n;
	std::cin >> n;
	int a, b;
	bool flag = true;
	for(int i = 0; i < n; i++)
	{
		std::cin >> a >> b;
		switch(a)
		{
		case 1:
			dq.push_front(b);
			break;
		case 2:
			if(dq.empty())
			{
				if(b != -1)
				{
					flag = false;
				}
			}
			else
			{
				int test = dq.pop_front();
				if(test != b)
				{
					flag = false;
				}
			}
			break;
		case 3:
			dq.push_back(b);
			break;
		case 4:
			if(dq.empty())
			{
				if(b != -1)
				{
					flag = false;
				}
			}
			else
			{
				int test = dq.pop_back();
				if(test != b)
				{
					flag = false;
				}
			}
			break;
		default:
			break;
		}
	}
	if(flag)
	{
		std::cout << "YES" << std::endl;
	}
	else
	{
		std::cout << "NO" << std::endl;
	}
	return 0;
}