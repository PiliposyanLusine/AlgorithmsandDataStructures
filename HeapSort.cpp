#include <iostream>
#include <vector>

void heapify(std::vector<int>& arr, int n, int i) 
{
    int largest = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    if (left_child < n && arr[left_child] > arr[largest]) 
    {
        largest = left_child;
    }

    if (right_child < n && arr[right_child] > arr[largest]) 
    {
        largest = right_child;
    }

    if (largest != i) 
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(std::vector<int>& arr) 
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) 
    {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) 
    {
        std::swap(arr[i], arr[0]); 
        heapify(arr, i, 0);
    }
}

int main() 
{
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    heap_sort(arr);

    std::cout << "Sorted array:";
    for (int num : arr) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
