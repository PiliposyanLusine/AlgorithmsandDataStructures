#include <iostream>
#include <vector>
//iterativ

int binarySearch(std::vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(nums[mid] == target)
        {
            return mid;
        }
        if(nums[mid] < target)
        {
            left = mid + 1;
        }
        else if(nums[mid] > target)
        {
            right = mid - 1;
        }
    }
    return -1;
} 


//recursive
int binarySearch(std::vector<int>& nums, int target, int left, int right)
{
    if(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(nums[mid] == target)
        {
            return mid;
        }
        if(nums[mid] > target)
        {
            return binarySearch(nums, target, left, mid - 1);
        }
        else if(nums[mid] < target)
        {
            return binarySearch(nums, target, mid + 1, right);
        }
        return -1;
    }
}


int main() 
{
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 7;

    int result = binarySearch(nums, target, 0, nums.size() - 1);

    if (result != -1) 
    {
        std::cout << "Element found at index " << result << std::endl;
    } 
    else 
    {
        std::cout << "Element not found in the array" << std::endl;
    }

    return 0;
}



