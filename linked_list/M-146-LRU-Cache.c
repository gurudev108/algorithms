/* 

LRU Cache - Doubly linked list with array based cache lookup

Output -
1
-1
-1
3
4
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct LRUCacheNode {
    int key;
    int value;
    struct LRUCacheNode* prev;
    struct LRUCacheNode* next;
} LRUCacheNode;

typedef struct {
    int capacity;
    int size;
    LRUCacheNode* head;
    LRUCacheNode* tail;
    LRUCacheNode** cache;
} LRUCache;

LRUCacheNode* createLRUCacheNode(int key, int value) {
    LRUCacheNode* newNode = (LRUCacheNode*)malloc(sizeof(LRUCacheNode));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->cache = (LRUCacheNode**)malloc(sizeof(LRUCacheNode*) * 10000);  // Assuming a maximum of 10000 keys
    for (int i = 0; i < 10000; i++) {
        cache->cache[i] = NULL;
    }
    return cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (obj == NULL) {
        return -1;
    }

    if (obj->cache[key] == NULL) {
        return -1;  // Key not found
    }

    // Move the accessed node to the front (most recently used)
    LRUCacheNode* node = obj->cache[key];
    if (node != obj->head) {
        if (node == obj->tail) {
            obj->tail = node->prev;
            obj->tail->next = NULL;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        node->next = obj->head;
        node->prev = NULL;
        obj->head->prev = node;
        obj->head = node;
    }

    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj == NULL) {
        return;
    }

    if (obj->cache[key] != NULL) {
        // Key exists, update the value, and move the node to the front
        obj->cache[key]->value = value;
        lRUCacheGet(obj, key); // Move to the front
    } else {
        // Key doesn't exist, create a new node, add it to the front, and check capacity
        LRUCacheNode* newNode = createLRUCacheNode(key, value);
        if (obj->size == 0) {
            obj->head = newNode;
            obj->tail = newNode;
            obj->size++;
        } else {
            newNode->next = obj->head;
            obj->head->prev = newNode;
            obj->head = newNode;
            obj->size++;
        }

        obj->cache[key] = newNode;

        // Check if the cache is full, if yes, remove the LRU node
        if (obj->size > obj->capacity) {
            LRUCacheNode* toRemove = obj->tail;
            obj->tail = obj->tail->prev;
            obj->tail->next = NULL;
            obj->cache[toRemove->key] = NULL;
            free(toRemove);
            obj->size--;
        }
    }
}

void lRUCacheFree(LRUCache* obj) {
    if (obj == NULL) {
        return;
    }

    for (int i = 0; i < 10000; i++) {
        if (obj->cache[i] != NULL) {
            free(obj->cache[i]);
        }
    }
    free(obj->cache);
    free(obj);
}

int main() {
    LRUCache* obj = lRUCacheCreate(2);

    lRUCachePut(obj, 1, 1);
    lRUCachePut(obj, 2, 2);
    printf("%d\n", lRUCacheGet(obj, 1));  // Output: 1
    lRUCachePut(obj, 3, 3);  // Removes key 2 (LRU)
    printf("%d\n", lRUCacheGet(obj, 2));  // Output: -1
    lRUCachePut(obj, 4, 4);  // Removes key 1 (LRU)
    printf("%d\n", lRUCacheGet(obj, 1));  // Output: -1
    printf("%d\n", lRUCacheGet(obj, 3));  // Output: 3
    printf("%d\n", lRUCacheGet(obj, 4));  // Output: 4

    lRUCacheFree(obj);
    return 0;
}

