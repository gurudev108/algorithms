import random

"""
class Node:
This line defines a new class named Node.

def __init__(self, data)::
This is the constructor method for the class. It is called when you create a new Node object.

self.data = data:
This line assigns the value of the data parameter to the data attribute of the Node object.
self.next = None:
This line initializes the next attribute to None. The next attribute will store a reference to the next node in the linked list
"""
class ListNode:
    def __init__(self, value=0, next=None):
        self.value = value
        self.next = next

def sort_linked_list(head):
    if not head or not head.next:
        return head

    # Split list into halves
    slow, fast = head, head.next
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next

    mid = slow.next
    slow.next = None

    left = sort_linked_list(head)
    right = sort_linked_list(mid)

    return merge(left, right)

def merge(left, right):
    dummy = ListNode()
    tail = dummy

    while left and right:
        if left.value < right.value:
            tail.next = left
            left = left.next
        else:
            tail.next = right
            right = right.next
        tail = tail.next

    tail.next = left if left else right
    return dummy.next

def print_list(head):
    while head:
        print(head.value)
        head = head.next

# Function to create a linked list with random values
def create_random_linked_list(size):
    head = ListNode(random.randint(1, 100))
    current = head
    for _ in range(size - 1):
        current.next = ListNode(random.randint(1, 100))
        current = current.next
    return head

# Example usage
head = create_random_linked_list(10)
print("Unsorted Linked List\n")
print_list(head)
print("Merge Sort on Linked List\n")
sorted_head = sort_linked_list(head)
print_list(sorted_head)