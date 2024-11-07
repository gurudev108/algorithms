"""
For example, given the following tree:

    5
   / \
  3   8
 / \ / \
2  4 6  10
and the range [4, 9], return 23 (5 + 4 + 6 + 8).

Verified Output:
23

"""

class TreeNode:
    def __init__(self, value=0, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

def range_sum_bst(root, a, b):
    if not root:
        return 0

    # If the current node's value is less than `a`, skip the left subtree.
    if root.value < a:
        return range_sum_bst(root.right, a, b)

    # If the current node's value is greater than `b`, skip the right subtree.
    if root.value > b:
        return range_sum_bst(root.left, a, b)

    # Otherwise, include the current node and recurse into both subtrees.
    return root.value + range_sum_bst(root.left, a, b) + range_sum_bst(root.right, a, b)

root = TreeNode(5)
root.left = TreeNode(3)
root.right = TreeNode(8)
root.left.left = TreeNode(2)
root.left.right = TreeNode(4)
root.right.left = TreeNode(6)
root.right.right = TreeNode(10)

result = range_sum_bst(root, 4, 9)
print(result)