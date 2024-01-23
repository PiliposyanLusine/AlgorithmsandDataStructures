// Time complexity O(n^2)

#include <iostream>
#include <vector>

void boubleSort(std::vector<int>&);

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
    boubleSort(arr);
    for(int i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}


void boubleSort(std::vector<int>& arr)
{
    int size = arr.size();
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size - 1 - i; ++j)
        {
            if(arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

