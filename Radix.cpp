#include <iostream>
#include <vector>



int getMax(int* arr, int n) 
{
    int max = arr[0];
    for (int i = 1; i < n; i++) 
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}


void countingSort(int arr[], int n, int exp) 
{
    const int radix = 10; 
    std::vector<int> output(n);
    std::vector<int> count(radix, 0);


    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % radix]++;
    }


    for (int i = 1; i < radix; i++)
    {
        count[i] += count[i - 1];
    }


    for (int i = n - 1; i >= 0; i--) 
    {
        output[count[(arr[i] / exp) % radix] - 1] = arr[i];
        count[(arr[i] / exp) % radix]--;
    }


    for (int i = 0; i < n; i++)
    { 
       arr[i] = output[i];
    }
}


void radixSort(int arr[], int n) 
{
    int max = getMax(arr, n);


    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        countingSort(arr, n, exp);
    }
}

int main() 
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    radixSort(arr, n);

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
