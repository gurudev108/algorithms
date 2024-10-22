def isAnagram(s: str, t: str) -> bool:
    if len(s) != len(t):
        return False
    
    count = {}

    for char in s:
        count[char] = count.get(char, 0) + 1
    
    for char in t:
        if char in count:
            count[char] -= 1
        else:
            return False

    for val in count.values():
        if val != 0:
            return False
    
    return True

# Test cases
s1, t1 = "anagram", "nagaram"
s2, t2 = "rat", "car"

print(isAnagram(s1, t1))
print(isAnagram(s2, t2))
    


