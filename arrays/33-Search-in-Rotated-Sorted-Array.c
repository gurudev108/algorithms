int search(int* nums, int numsSize, int target){

    int left = 0;
    int right = numsSize - 1;
    int mid = 0;

    while (left <= right)
    {
        mid = left + (right - left)/2;
        if (nums[mid] == target)
        {
            return mid;
        }
        // Case 2: subarray on mid's left is sorted
        else if (nums[mid] >= nums[left])
        {
            if (target >= nums[left] && target < nums[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        // Case 3: subarray on mid's right is sorted
        else
        {
            if (target <= nums[right] && target > nums[mid])
            {
                left = mid + 1;
            }
            else 
            {
                right = mid - 1;
            }
        }
    }
    return -1;
}
