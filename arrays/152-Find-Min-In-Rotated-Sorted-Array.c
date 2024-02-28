int findMin(int* nums, int numsSize){
    int left = 0;
    int right = numsSize -1;
    int mid = 0;

    if (numsSize == 1)
    {
        return nums[0];
    }
    // if the array is not rotated 1<2<3<4<5<6<7
    if (nums[right] > nums[0])
    {
        return nums[0];
    }

    // Rotated 6<7<>1<2<3<4<5

    while (left<=right)
    {
        mid = left + (right - left)/2;

        if (nums[mid] >= nums[mid+1])
        {
            return nums[mid+1];
        }
        else if (nums[mid] <= nums[mid-1])
        {
            return nums[mid];
        }
        if (nums[mid] > nums[left])
        {
            left = mid + 1;
        }
        else 
        {
            right = mid - 1;
        }
    }
    return -1;

}
