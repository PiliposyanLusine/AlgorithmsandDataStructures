#include <iostream>
int partition (int *arr, int start, int end);
void quick_sort (int *arr, int satrt, int end);
int find_median (int *arr, int start, int end);


int main() 
{   
    int size;
    std::cin >> size;
    int *arr = new int[size];
    for (int i = 0; i < size; ++i) 
    {
        std::cin >> arr[i];
    }
    quick_sort(arr, 0, size - 1);
    for (int i = 0; i < size; ++i) 
    {
        std::cout << arr[i] << " ";
    }

    delete[] arr;
    return 0;
}

void quick_sort(int* arr, int start, int end)
{
    if(start < end)
    {
        int pr = partition(arr, start, end);
        quick_sort(arr, start, pr - 1);
        quick_sort(arr, pr + 1, end);
    }
}


//first as a pivot 
int partition(int* arr, int start, int end)
{
    int pivot = arr[start];
    int i = start + 1;
    for(int j = start + 1; j <= end; ++j)
    {
        if(arr[j] <= pivot)
        {
            std::swap(arr[i++], arr[j]);
        }
    }
    std::swap(arr[i - 1], arr[start]);
    return (i - 1);
}







//last as a pivot
int partition(int* arr, int start, int end)
{
    int pivot = arr[end];
    int i = start;
    for(int j = start; j < end; ++j)
    {
        if(arr[j] <= pivot)
        {
            std::swap(arr[j], arr[i++]);
        }
    }
    std::swap(arr[i], arr[end]);
    return i;
}



// //Median of three
int find_median(int* arr, int start, int end)
{
    int mid = start + (end - start) / 2;
    if(arr[start] > arr[mid])
    {
        std::swap(arr[mid], arr[start]);
    }
    if(arr[end] < arr[mid])
    {
        std::swap(arr[end], arr[mid]);
    }
    if(arr[start] > arr[end])
    {
        std::swap(arr[end], arr[start]);
    }
    return mid;
}



int partition (int *arr, int start, int end) 
{
    int index = find_median(arr, start, end);
    int pivot = arr[index];
    std::swap(arr[end], arr[index]);
    int i = start;
    for(int j = start; j < end; ++j)
    {
        if(arr[j] <= pivot)
        {
            std::swap(arr[i++], arr[j]);
        }
    }
    std::swap(arr[i], arr[end]);
    return i;
}



// //random as a pivot
int partition(int* arr, int start, int end)
{
    int random = start + rand() % (end - start + 1);
    int pivot = arr[random];
    std::swap(arr[random], arr[end]);
    int i = start;
    for(int j = start; j < end; ++j)
    {
        if(arr[j] <= pivot)
        {
            std::swap(arr[j], arr[i++]);
        }
    }
    std::swap(arr[i], arr[end]);
    return i;
}

