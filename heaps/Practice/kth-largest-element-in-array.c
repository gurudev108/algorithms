/* 
Approach - Using a min heap of k elements,
1. Create a size k min heap
2. Start adding elements one by one into the heap. 
3. If the heap is full, compare the top element with the current element. If the current element is bigger, replace top with the current item (add it in the min heap) and heapify
*/

#include<stdio.h>
/* For 0 indexed array */
#define PARENT(i) ((i-1)/2)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int* nums, int size, int index)
{
    int smallest = index;
    if ((LEFT(index) < size) && (nums[LEFT(index)] < nums[smallest]))
    {
        smallest = LEFT(index);
    }
    if ((RIGHT(index) < size) && (nums[RIGHT(index)] < nums[smallest]))
    {
        smallest = RIGHT(index);
    }
    
    if (smallest != index)
    {
        swap(&nums[index], &nums[smallest]);
        /*
        int temp = nums[index];
        nums[index] = nums[smallest];
        nums[smallest] = temp;
*/
        heapify(nums, size, smallest);
    }
    
}

void build_heap(int* nums, int size)
{
    for (int i = PARENT(size-1); i>=0; i--)
    {
        heapify(nums, size, i);
    }
}

int findKthLargest(int* nums, int numsSize, int k) {

    /* Step 1 - Build min heap of k elements */
    build_heap(nums, k);
    
    /* Step 2 - Process remaning elements and if current element is greater than top */
    for (int i=k; i<numsSize; i++)
    {
        if(nums[i] > nums[0])
        {
            int temp = nums[0];
            nums[0] = nums[i];
            nums[i] = temp;
            
            heapify(nums, k, 0);
        }
    }
    return nums[0];
    
}

int main()
{
    // Example usage:
    int nums[] = {3, 2, 1, 5, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;

    int result = findKthLargest(nums, numsSize, k);

    printf("The %dth largest element is: %d\n", k, result);

    return 0;
}
