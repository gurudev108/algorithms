/* This file contains my experiments with hashtable data structure. Hashtable is 
   often implemented as array of linked list or binary search tree. Array of
   linked list because of collisions

   7/10/23 - Add romanToInt and intToRoman using hash
   7/10/23 - Add hash() and djb2_hash - Create hash table, pending hash lookup

 */


#include <stdlib.h> // for malloc, qsort
#include <stdio.h>  // for printf scanf
#include <string.h> // for strlen

struct hashtable
{
  char str[10];
  int marks;
  /* In case there are conflicts for the hash */
  struct hashtable *next;
};

/*
Hash for A = 65, B=66, a=97
Hash for AB = 197 [1*65 + 2*66]
*/
unsigned long hash(char* str)
{
  unsigned long hash = 0;
  int len = strlen(str);
  printf("length=%d\n", len);
  for (int i=0; i<len; i++)
  {
    hash += (i+1)*str[i];
    printf("hash =%lu\n", hash);
  }
  return hash;
}

unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void hash_create()
{
  struct hashtable* grades[10];
  char input[10];
  int marks=0;
  int count = 0;
  unsigned long hashnum = 0;
  /* Populating hashtable */
  while(count<10)
  {
    struct hashtable *ptr = malloc(sizeof(struct hashtable));
    printf("Enter Name:");
    scanf("%s", &ptr->str[0]);
    printf("Enter marks:");
    scanf("%d", &ptr->marks);
    hashnum = hash(&ptr->str[0]);
    printf("hash for %s is %lu\n", &ptr->str[0], hash(&input[0]));
  }

  /*printf("hash for A is %d\n", hash("A"));
  printf("hash for a is %d\n", hash("a"));
  printf("hash for B is %d\n", hash("B"));
  printf("hash for AB is %d\n", hash("AB")); */


  return;
}


/* this function convers roman# to integer */
int romanToInt(char * s)
{
    /* <<<<<Note how array is used as hash>>>>>>> */
    int t['X' + 1] = {
        ['I'] = 1,
        ['V'] = 5,
        ['X'] = 10,
        ['L'] = 50,
        ['C'] = 100,
        ['D'] = 500,
        ['M'] = 1000,
    };
    int res = 0;
    //printf("size of hashtable =%d size of int=%d",(int)sizeof(t), (int)sizeof(int));
    for (int i = 0; s[i]; i++) {
        if (t[s[i]] < t[s[i+1]])
            res -= t[s[i]];
        else
            res += t[s[i]];
    }
    return res;
}

/* Leetcode Medium - https://leetcode.com/problems/integer-to-roman/description/
NOT TESTED 
*/
char * intToRoman(int num)
{
  char* result = NULL;
/*
  int value[13] = {1,4,5,9,10,40,50,90,100,400,500,900,1000};
  char* key[13]  = {'I','IV','V','IX','X','XL','L','XC','C','CD','D','CM','M'};
  int index = 6;
  char *result = malloc(sizeof(char)*10);
  int i=0;
  int temp=0;
  while(num)
  {
      if (num/value[index])
      {
        result[i++] = key[index];
        num = num - value[index];
      }
      else
      {
        index--;
      }
  }
*/
  return result;
}

/*
2 functionalities
Integer to roman
Roman to Integer
*/
void roman_numeral_main()
{
  char *ptr=NULL;
  printf("Roman to Int for XVII is %d\n",romanToInt("XVII"));
  printf("Roman to Int for XIV is %d\n",romanToInt("XIV"));
  ptr = intToRoman(2023);
  printf("Integer 2023, Roman=%s\n", ptr);
  free(ptr);
  ptr = intToRoman(663);
  printf("Integer 663, Roman=%s\n", ptr);
  free(ptr);
  ptr = intToRoman(1994);
  printf("Integer 1994, Roman=%s\n", ptr);
  free(ptr);

}

/*
https://leetcode.com/problems/two-sum/description/
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order. Note: The returned array must be malloced, assume caller calls free().
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
*/

#define TABLE_SIZE 10

typedef struct{
  int key;
  int value;
  /* for collision implement LinkedList */
} Entry;

typedef struct{
  Entry* entries[TABLE_SIZE];
} HashTable;

int hashFunction2sum (int key)
{
  return key%TABLE_SIZE;
}

HashTable* createHashTable()
{
  HashTable* ptr = (HashTable*) malloc(sizeof(HashTable));
  for (int i=0; i<TABLE_SIZE; i++)
  {
    ptr->entries[i] = NULL;
  }
  return ptr;
}

void insert(HashTable* hashtable, int key, int value)
{
  int index = hashFunction2sum(key);
  Entry* entry = (Entry*) malloc(sizeof(Entry));
  entry->key = key;
  entry->value = value;
  hashtable->entries[index] = entry;
}

int lookup(HashTable* hashtable, int key)
{
  int index = hashFunction2sum(key);
  if (hashtable->entries[index])
  {
    if (hashtable->entries[index]->key == key)
    {
      return hashtable->entries[index]->value;
    }
  }
  else
  {
    printf("Entry:%d not found\n", key);
    return -1;
  }
  return -1;
}

void freeHashTable(HashTable* hashtable)
{
  for (int i=0; i<TABLE_SIZE; i++)
  {
    if(hashtable->entries[i])
    {
      free(hashtable->entries[i]);
    }
  }
  free(hashtable);
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
  int search = 0;
  int index = 0;
  int* result = (int*)malloc(2*sizeof(int));
  HashTable * ptr = createHashTable();
  for (int i= 0; i<numsSize; i++)
  {
    search = target - nums[i];
    index = lookup(ptr, search);
    if (index == -1)
    {
      insert(ptr, nums[i], i);
    }
    else
    {
      printf("target:%d found at index:%d and %d\n", target, index, i);
      result[0] = index;
      result[1] = i;
      *returnSize = 2;
      return result;
    }
  }
  result[0] = -1;
  result[1] = -1;
  return result;
}

void two_sum_main()
{
  int input[] = {2,7,11,15};
  int numSize = 4;
  int target = 9;
  int returnSize = 0;
  int* result = twoSum(&input[0], numSize, target, &returnSize);
}

// END OF twoSum 

/* Learn to use qsort from stdlib */

int compare(const void* num1, const void* num2)
{
  int element1 = *((int*)num1);
  int element2 = *((int*)num2);
  if (element1>element2) return 1;
  if (element1<element2) return -1;
  return 0;
}

void use_qsort()
{
  int array[] = {3,6,2,7,9,8,1,5,0,4};
  int len = sizeof(array)/sizeof(int);
  qsort(array, len, sizeof(int), compare);
  for (int i=0; i<len; i++)
    printf(" %d ", array[i]);
}


/*
This problem was asked by Microsoft.

Given a dictionary of words and a string made up of those words (no spaces),
return the original sentence in a list. If there is more than one possible
reconstruction, return any of them. If there is no possible reconstruction,
then return null.

For example, given the set of words 'quick', 'brown', 'the', 'fox', and the
string "thequickbrownfox", you should return ['the', 'quick', 'brown', 'fox'].

Given the set of words 'bed', 'bath', 'bedbath', 'and', 'beyond', and the
string "bedbathandbeyond", return either ['bed', 'bath', 'and', 'beyond] or
['bedbath', 'and', 'beyond']. 
*/

void brown_fox_main()
{
  char* dictionary[] = {"quick", "brown", "the", "fox"};
  char sentence[] = {"thequickbrownfox"};
  
}

int main()
{
  //hash_create();
  //roman_numeral_main();
  two_sum_main();
  //use_qsort();
  //brown_fox_main();
}
