#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000

typedef struct CacheNode {
    int key;
    int value;
    struct CacheNode* prev;
    struct CacheNode* next;
} CacheNode;

typedef struct {
    int capacity;
    int size;
    CacheNode* head;
    CacheNode* tail;
    CacheNode* map[HASH_SIZE]; // Direct lookup table for simulation
} LRUCache;

LRUCache* createLRUCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    for (int i = 0; i < HASH_SIZE; i++) {
        cache->map[i] = NULL;
    }
    return cache;
}

// Detach node from DLL
void detachNode(LRUCache* cache, CacheNode* node) {
    if (node->prev != NULL) node->prev->next = node->next;
    else cache->head = node->next;

    if (node->next != NULL) node->next->prev = node->prev;
    else cache->tail = node->prev;

    node->prev = NULL;
    node->next = NULL;
}

// Add node to head of DLL (Most Recently Used)
void addToHead(LRUCache* cache, CacheNode* node) {
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head != NULL) {
        cache->head->prev = node;
    } else {
        cache->tail = node;
    }
    cache->head = node;
}

// Move existing node to head
void moveToHead(LRUCache* cache, CacheNode* node) {
    detachNode(cache, node);
    addToHead(cache, node);
}

// Get value from cache
int get(LRUCache* cache, int key) {
    if (key < 0 || key >= HASH_SIZE || cache->map[key] == NULL) {
        printf("GET [key=%d] -> Cache MISS (-1)\n", key);
        return -1;
    }
    CacheNode* node = cache->map[key];
    moveToHead(cache, node);
    printf("GET [key=%d] -> Cache HIT (value=%d)\n", key, node->value);
    return node->value;
}

// Put key-value pair into cache
void put(LRUCache* cache, int key, int value) {
    if (key < 0 || key >= HASH_SIZE) return;

    if (cache->map[key] != NULL) {
        // Key exists, update value and move to MRU
        CacheNode* node = cache->map[key];
        node->value = value;
        moveToHead(cache, node);
        printf("PUT [key=%d, val=%d] -> Updated existing key\n", key, value);
        return;
    }

    // Evict least-recently-used (LRU) from tail if cache full
    if (cache->size >= cache->capacity) {
        CacheNode* lru = cache->tail;
        printf("PUT [key=%d, val=%d] -> Cache FULL! Evicting LRU [key=%d, val=%d]\n", 
               key, value, lru->key, lru->value);
        cache->map[lru->key] = NULL;
        detachNode(cache, lru);
        free(lru);
        cache->size--;
    }

    // Insert new node at head
    CacheNode* newNode = (CacheNode*)malloc(sizeof(CacheNode));
    newNode->key = key;
    newNode->value = value;
    addToHead(cache, newNode);
    cache->map[key] = newNode;
    cache->size++;
    printf("PUT [key=%d, val=%d] -> Added to cache (size: %d/%d)\n", 
           key, value, cache->size, cache->capacity);
}

void displayCache(LRUCache* cache) {
    printf("Current Cache (MRU to LRU): ");
    CacheNode* curr = cache->head;
    while (curr != NULL) {
        printf("[%d:%d] ", curr->key, curr->value);
        if (curr->next != NULL) printf("<-> ");
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    printf("--- LRU Cache Simulation (Capacity: 3) ---\n\n");
    LRUCache* cache = createLRUCache(3);

    put(cache, 1, 100);
    put(cache, 2, 200);
    put(cache, 3, 300);
    displayCache(cache);

    // Access key 1 (becomes most recently used)
    get(cache, 1);
    displayCache(cache);

    // Put key 4 (causes eviction of key 2, since 1 was just accessed and 3 is newer than 2)
    put(cache, 4, 400);
    displayCache(cache);

    get(cache, 2); // Should miss (-1)
    get(cache, 3); // Hit
    displayCache(cache);

    return 0;
}
