#include <iostream>
#include <vector>






template<typename T, typename Hasher>
class HashTable
{
public:
	HashTable(size_t initial_size)
		: table(initial_size), size(0), max_load_rate(0.75), current_load_rate(0)
	{

	}

	~HashTable()
	{

	}

	bool Add(const T& data)
	{
		int index = probe_for_add(data);
		if (index < 0)
			return false;	
		HashTableNode node(index, data, false, true);
		table.at(index) = node;
		size++;
		current_load_rate = static_cast<float>(size) / table.capacity();
		if (current_load_rate >= max_load_rate)
			grow();
		return true;
	}
	bool Has(const T& data)
	{
		int index = probe_for_find(data);
		if (index < 0)
			return false;
		return true;
	}
	bool Delete(const T& data)
	{
		int index = probe_for_find(data);
		if (index < 0) {
			return false;
		}
		table.at(index).isDeleted = true;
		size--;
		return true;
	}

private:
	void grow()
	{
		std::vector<HashTableNode> new_table(2 * table.size());
		for (HashTableNode& node: table)
		{
			if (!node.isAdded)
				continue;
			if (node.isDeleted)
				continue;
			size_t key = hasher(node.data, first_prime) % new_table.size();
			for (int i = 0; i < new_table.size(); i++)
			{
				key = (hasher(node.data, first_prime) + (2 * hasher(node.data, second_prime) + 1) * i) % new_table.size();
				HashTableNode element = new_table.at(key);
				if (!element.isAdded)
				{
					node.key = key;
					break;
				}
			}
			new_table.at(node.key) = node;
		}
		table = std::move(new_table);
	}
	int probe_for_add(const T& data)
	{
		size_t key = hasher(data, first_prime) % table.size();
		int pos_del = -1;
		int pos_nil = -1;
		for (int i = 0; i < table.size(); i++)
		{
			key = (hasher(data, first_prime) + (2 * hasher(data, second_prime) + 1) * i) % table.size();
			HashTableNode element = table.at(key);
			if (!element.isAdded)
			{
				pos_nil = key;
				break;
			}
			if (element.isDeleted && pos_del < 0)
				pos_del = element.key;
			if (element.data == data && !element.isDeleted)
				return -1;
		}
		if (pos_del == -1)
			return pos_nil;
		return pos_del;
	}
	int probe_for_find(const T& data)
	{
		size_t key = hasher(data, first_prime) % table.size();
		for (int i = 0; i < table.size(); i++)
		{
			key = (hasher(data, first_prime) + (2 * hasher(data, second_prime) + 1) * i) % table.size();
			HashTableNode element = table.at(key);
			if (element.data == data && !element.isDeleted && element.isAdded)
				return element.key;
			if (!element.isAdded)
				return -1;
		}
		return -1;
	}


	struct HashTableNode 
	{
		HashTableNode(size_t key, T data, bool isDeleted, bool isAdded)
		{
			this->key = key;
			this->data = data;
			this->isAdded = isAdded;
			this->isDeleted = isDeleted;
		}
		HashTableNode()
		{
			isDeleted = false;
			isAdded = false;
		}
		size_t key;
		T data;
		bool isDeleted;
		bool isAdded;
	};
	std::vector<HashTableNode> table;
	size_t first_prime = 11;
	size_t second_prime = 29;
	Hasher hasher;
	size_t size;
	float current_load_rate;
	float max_load_rate;
};


class StringHasher
{
public:
	size_t operator()(const std::string& str, size_t prime)
	{
		size_t hash = 0;
		for (int i = 0; i < str.size(); i++)
		{
			hash = hash * prime + str[i];
		}
		return hash;
	}
};





int main(int argc, char** argv)
{
	HashTable<std::string, StringHasher> table(8);
	char op;
	std::string key;
	while (std::cin >> op >> key)
	{
		switch (op)
		{
		case '+':
			std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
			break;
		case '-' :
			std::cout << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
			break;
		case '?':
			std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
			break;
		default:
			break;
		}
	}
	return 0;
}