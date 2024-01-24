#include <iostream>
#include <vector>
#include <algorithm>


void insertionSort(std::vector<int>& bucket)
{
    int n = bucket.size();
    for(int i = 1; i < n; ++i)
    {
        int j = i - 1;
        int key = bucket[i];
        while (j >= 0 && bucket[j] > key)
        {
            bucket[j + 1] = bucket[j--];
        }
        bucket[j + 1] = key;
    }
}



void bucketSort(std::vector<int>& arr)
{
    int n = arr.size();
    int min_val = *std::min_element(arr.begin(), arr.end());
    int max_val = *std::max_element(arr.begin(), arr.end());
    int rande = max_val - min_val + 1;
    std::vector<std::vector<int>> buckets(rande);
    for(int i = 0; i < n; ++i)
    {
        int index = arr[i] - min_val;
        buckets[index].push_back(arr[i]);
    }
    for(int i = 0; i < rande; ++i)
    {
        if(!buckets[i].empty())
        {
            insertionSort(buckets[i]);
        }
    }
    int index = 0;
    for(int i = 0; i < rande; ++i)
    {
        for(int j = 0; j < buckets[i].size(); ++j)
        {
            arr[index++] = buckets[i][j];
        }
    }
}




int main() 
{
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    bucketSort(arr);
    std::cout << "Sorted array: ";
    for (int num : arr) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
