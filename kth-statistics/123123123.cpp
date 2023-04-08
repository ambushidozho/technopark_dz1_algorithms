
#include <algorithm>
#include <iostream>

template <typename T, typename Comparator = std::less<int>>
int median_of_three(T* arr, int l, int r, Comparator cmp = Comparator())
{
    int mid = (l + r) / 2;
    if (arr[l] < arr[mid]) {
        if (arr[r] < arr[l]) {
            return l;
        }
        else if (arr[r] < arr[mid]) {
            return r;
        }
        return mid;
    }
    else
    {
        if (arr[r] < arr[mid]) {
            return mid;
        }
        else if (arr[r] < arr[l]) {
            return r;
        }
        return l;
    }
}

template <typename T, typename Comparator = std::less<int>>
int Partition(T* arr, int l, int r, Comparator cmp = Comparator())
{
    int index_of_pivot = median_of_three(arr, l, r, cmp);
    T pivot = arr[index_of_pivot];
    std::swap(arr[index_of_pivot], arr[r]);
    int i = l;
    int j = i;
    while (1)
    {
        while (cmp(arr[i], pivot) && j < r)
        {
            i++;
            j++;
        }
        while (cmp(pivot,arr[j]) && j < r)
        {
            j++;
        }
        if (j == r)
        {
            std::swap(arr[i], arr[j]);
            return i;
        }
        if(cmp(arr[j], pivot))
            std::swap(arr[i++], arr[j]);
        j++;
    }
}

template<typename T, typename Comparator = std::less<int>>
T kth_statistics(T* arr, int k, int l, int r, Comparator cmp = Comparator())
{
    int pivot_pos = 0;
    int left = l;
    int right = r;
    while (left <= right)
    {
        pivot_pos = Partition(arr, left, right, cmp);
        if (pivot_pos == k)
        {
            return arr[pivot_pos];
        }
        else if (pivot_pos > k)
        {
            right = pivot_pos - 1;
        }
        else
        {
            left = pivot_pos + 1;
        }
    }
}


int main()
{
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    std::cout << kth_statistics(arr, 0.1 * n, 0, n - 1) << std::endl;
    std::cout << kth_statistics(arr, n / 2, 0, n - 1) << std::endl;
    std::cout << kth_statistics(arr, 0.9 * n, 0, n - 1) << std::endl;

    return 0;

}

