#include <iostream>
#include <vector>



void merge(std::vector<int>& arr, int left, int mid, int right)
{
    int size1 = right - left;
    int size2 = mid - left + 1;
    std::vector<int> arr1(size1);
    std::vector<int> arr2(size2);
    for(int i = 0; i < size1; ++i)
    {
        arr1[i] = arr[left + i];
    }
    for(int j = 0; j < size2; ++j)
    {
        arr2[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while(i < size1 && j < size2)
    {
        if(arr1[i] < arr2[j])
        {
            arr[k] = arr1[i++];
        }
        else
        {
            arr[k] = arr2[j++];
        }
        ++k;
    }
    while (i < size1)
    {
        arr[k++] = arr1[i++];
    }
    while (j < size2)
    {
        arr[k++] = arr2[j++];
    }

}




void mergeSort(std::vector<int>& arr, int left, int right)
{
    if(left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, mid + 1, right);
        mergeSort(arr, left, mid - 1);
        merge(arr, left, mid, right);
    }
}


int main() 
{
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    std::cout << "Original array: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, n - 1);

    std::cout << "Sorted array: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
