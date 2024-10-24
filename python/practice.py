def smallest_window(arr):
  n = len (arr)

  if n <= 1:
    return (0,0)
  
  left = 0
  while left < n-1 and arr[left] < arr[left+1]:
    left += 1
  
  if left == n - 1:
    return (0,0)

  right = n - 1
  while right > 0 and arr[right] > arr[right-1]:
    right -= 1

  sub_min = min(arr[left: right+1])
  sub_max = max(arr[left: right+1])

  while left > 0 and arr[left - 1] > sub_min:
    left -=  1
  
  while right < n-1 and arr[right + 1] < sub_max:
    right += 1
  
  return (left, right)


arr = [3, 7, 5, 6, 9]
result = smallest_window(arr)
print(result)





