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

// Function to create a new node
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
    cache->hashmap = (Node**)malloc(sizeof(Node*) * 10000); // Assuming a constant hash table size

    // Initialize the hashmap with NULL pointers
    for (int i = 0; i < 10000; i++) {
        cache->hashmap[i] = NULL;
    }

    return cache;
}

// Function to move a node to the front of the doubly linked list (marking it as most recently used)
void moveToHead(LRUCache* cache, Node* node) {
    if (node == cache->head) {
        return; // Node is already at the front
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    if (node == cache->tail) {
        cache->tail = node->prev;
    }

    node->next = cache->head;
    node->prev = NULL;

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
    lRUCachePut(lruCache, 3, 3);
    printf("%d\n", lRUCacheGet(lruCache, 2)); // Output: -1 (not found)
    lRUCachePut(lruCache,

