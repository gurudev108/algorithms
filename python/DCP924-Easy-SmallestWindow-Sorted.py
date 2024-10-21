def find_unsorted_window(arr):
    n = len(arr)
    if n <= 1:
        return (0, 0)  # A single element array or empty array is trivially sorted

    # Step 1: Find the initial left boundary
    left = 0
    while left < n - 1 and arr[left] <= arr[left + 1]:
        left += 1

    if left == n - 1:
        # The array is already sorted
        return (0, 0)

    # Step 2: Find the initial right boundary
    right = n - 1
    while right > 0 and arr[right] >= arr[right - 1]:
        right -= 1

    # Step 3: Find the min and max within the window (left to right)
    sub_min = min(arr[left:right + 1])
    sub_max = max(arr[left:right + 1])

    # Step 4: Expand the left boundary if needed
    while left > 0 and arr[left - 1] > sub_min:
        left -= 1

    # Step 5: Expand the right boundary if needed
    while right < n - 1 and arr[right + 1] < sub_max:
        right += 1

    return (left, right)

# Example usage:
arr = [3, 7, 5, 6, 9]
result = find_unsorted_window(arr)
print(result)  # Output should be (1, 3)

