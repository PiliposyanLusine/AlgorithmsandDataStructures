// Time complexity O(n^2)

#include <iostream>
#include <vector>

void InsertionSort(std::vector<int>&);

int main()
{
    std::cout << "Enter size for array: " << std::endl;
    int size = 0;
    std::cin >> size;
    std::vector<int> arr(size); 
    std::cout << "Enter elements " << std::endl;
    for(int i = 0; i < size; ++i)
    {
        std::cin >> arr[i];
    }

    std::cout << "Sort array: " << std::endl;
    InsertionSort(arr);
    for(int i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}

void InsertionSort(std::vector<int>& arr)
{
    int size = arr.size();
    for(int i = 1; i < size; ++i)
    {
        int j = i - 1;
        int key = arr[i];
        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

