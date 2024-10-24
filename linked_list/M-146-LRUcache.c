/*

146. LRU Cache using doubly linked list and hashmap implemented as arrays.

Approach

The description of the put method states that we are storing key-value pairs. 
This means the data structure is similar to a hash map, which also stores key-value pairs.

To keep the order in which keys have been used, we can implement a queue

1. Think about structures for a node and LRU cache and hashmap.
2. Create LRU Cache
3. Put some stuff in it
   3.1 If Key already exists, update value and move to front
   3.2 If key doesn't exist, add and move node to front
   3.3 If cache exceeds capacity, evict LRU
4. Get some stuff from it,
   4.1 if key exists, return value and move node to the front
   4.2 if key doesn't exist return -1

Verified output:
1
-1
-1
3
4
*/

#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
typedef struct Node {
    int key;
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

// LRUCache structure
typedef struct {
    int capacity;
    int size;
    Node* head;
    Node* tail;
    Node** hashmap; // Array of pointers to nodes for fast access
} LRUCache;

// Function to create a new node in Doubly Linked List
Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the LRUCache
LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    /* create memory to store 10k pointers to node of the doubly linked list for faster access */
    cache->hashmap = (Node**)malloc(sizeof(Node*) * 10000);

    // Initialize the hashmap with NULL pointers
    for (int i = 0; i < 10000; i++) {
        cache->hashmap[i] = NULL;
    }

    return cache;
}

// Function to move a node to the front of the doubly linked list (marking it as most recently used)
void moveToHead(LRUCache* cache, Node* node) {

    /* Handle Node at front */
    if (node == cache->head) {
        return; // Node is already at the front
    }

    /* pick out the node - adjust prev's next */
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    /* adjust next's prev */
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    /* Handle Node at tail */
    if (node == cache->tail) {
        cache->tail = node->prev;
    }

    /* Insert node at head */
    node->next = cache->head;
    node->prev = NULL;

    /* Handle prev of old head */
    if (cache->head != NULL) {
        cache->head->prev = node;
    }

    cache->head = node;

    if (cache->tail == NULL) {
        cache->tail = cache->head;
    }
}

// Function to evict the least recently used node
void evictLRUNode(LRUCache* cache) {
    if (cache->tail != NULL) {
        Node* toRemove = cache->tail;
        cache->tail = toRemove->prev;

        if (cache->tail != NULL) {
            cache->tail->next = NULL;
        }

        if (toRemove == cache->head) {
            cache->head = NULL;
        }

        cache->hashmap[toRemove->key % 10000] = NULL;

        free(toRemove);
        cache->size--;
    }
}

// Function to get the value associated with a key from the LRUCache
int lRUCacheGet(LRUCache* cache, int key) {
    if (cache->hashmap[key % 10000] != NULL) {
        Node* node = cache->hashmap[key % 10000];
        moveToHead(cache, node);
        return node->value;
    }
    return -1;
}

// Function to put a key-value pair into the LRUCache
void lRUCachePut(LRUCache* cache, int key, int value) {
    if (cache->hashmap[key % 10000] != NULL) {
        // Key already exists, update value and move to the front
        Node* node = cache->hashmap[key % 10000];
        node->value = value;
        moveToHead(cache, node);
    } else {
        // Key does not exist, add a new node to the front
        Node* newNode = createNode(key, value);
        newNode->next = cache->head;
        if (cache->head != NULL) {
            cache->head->prev = newNode;
        }
        cache->head = newNode;
        if (cache->tail == NULL) {
            cache->tail = newNode;
        }
        cache->hashmap[key % 10000] = newNode;
        cache->size++;

        // If the cache exceeds capacity, evict the least recently used node
        if (cache->size > cache->capacity) {
            evictLRUNode(cache);
        }
    }
}

// Function to free memory allocated for the LRUCache
void lRUCacheFree(LRUCache* cache) {
    while (cache->head != NULL) {
        Node* temp = cache->head;
        cache->head = temp->next;
        free(temp);
    }
    free(cache->hashmap);
    free(cache);
}

int main() {
    // Example usage of the LRUCache
    LRUCache* lruCache = lRUCacheCreate(2);

    lRUCachePut(lruCache, 1, 1);
    lRUCachePut(lruCache, 2, 2);
    printf("%d\n", lRUCacheGet(lruCache, 1)); // Output: 1
    lRUCachePut(lruCache, 3, 3); // Removes key 2 (LRU)
    printf("%d\n", lRUCacheGet(lruCache, 2)); // Output: -1 (not found)
    lRUCachePut(lruCache, 4, 4); // Removes key 1 (LRU)
    printf("%d\n", lRUCacheGet(lruCache, 1));  // Output: -1
    printf("%d\n", lRUCacheGet(lruCache, 3));  // Output: 3
    printf("%d\n", lRUCacheGet(lruCache, 4));  // Output: 4
    lRUCacheFree(lruCache);
    return 0;
}

