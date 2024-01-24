#include <iostream>
#include <vector>

void countingSort(std::vector<int>& arr)
{
    int max = *std::max_element(arr.begin(), arr.end());
    std::vector<int> count(max + 1, 0);
    for(int i = 0; i < arr.size(); ++i)
    {
        count[arr[i]]++;
    }
    for(int i = 1; i <= max; ++i)
    {   
        count[i] += count[i - 1];
    }
    std::vector<int> output(arr.size());
    for(int i = 0; i < arr.size(); ++i)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for(int i = 0; i < arr.size(); ++i)
    {
        arr[i] = output[i]; 
    }
}





int main() 
{
    std::vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    std::cout << "Original array: ";
    for (int num : arr) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    countingSort(arr);
    std::cout << "Sorted array: ";
    for (int num : arr) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
