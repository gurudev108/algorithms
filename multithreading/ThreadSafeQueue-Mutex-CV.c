/*
Same as P
Output - 
Produced: 7 | Queue size: 1
Consumed: 7 | Queue size: 0
Produced: 49 | Queue size: 1
Consumed: 49 | Queue size: 0
Produced: 73 | Queue size: 1
Consumed: 73 | Queue size: 0
Produced: 9 | Queue size: 1
Consumed: 9 | Queue size: 0
Produced: 65 | Queue size: 1
Consumed: 65 | Queue size: 0
Produced: 40 | Queue size: 1
Consumed: 40 | Queue size: 0
Produced: 42 | Queue size: 1
Consumed: 42 | Queue size: 0
Produced: 69 | Queue size: 1
Consumed: 69 | Queue size: 0
Produced: 9 | Queue size: 1
Produced: 99 | Queue size: 2
Consumed: 9 | Queue size: 1
Consumed: 99 | Queue size: 0
Produced: 16 | Queue size: 1
Consumed: 16 | Queue size: 0
Produced: 67 | Queue size: 1
Consumed: 67 | Queue size: 0
Produced: 79 | Queue size: 1
Consumed: 79 | Queue size: 0
Produced: 21 | Queue size: 1
Consumed: 21 | Queue size: 0
Produced: 93 | Queue size: 1
Produced: 85 | Queue size: 2
Consumed: 93 | Queue size: 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define QUEUE_SIZE 5  // Size of the queue

typedef struct {
    int items[QUEUE_SIZE];
    int front, rear, size;
    pthread_mutex_t lock;            // Mutex to protect the queue
    pthread_cond_t not_full;         // Condition variable for producer (queue not full)
    pthread_cond_t not_empty;        // Condition variable for consumer (queue not empty)
} Queue;

// Initialize the queue
void init_queue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);
}

// Enqueue (add) an item to the queue
void enqueue(Queue* q, int item) {
    pthread_mutex_lock(&q->lock);  // Lock the queue

    // Wait if the queue is full
    while (q->size == QUEUE_SIZE) {
        pthread_cond_wait(&q->not_full, &q->lock);
    }

    // Add the item to the queue
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->items[q->rear] = item;
    q->size++;
    printf("Produced: %d | Queue size: %d\n", item, q->size);

    // Signal that the queue is not empty (wake up consumers)
    pthread_cond_signal(&q->not_empty);

    pthread_mutex_unlock(&q->lock);  // Unlock the queue
}

// Dequeue (remove) an item from the queue
int dequeue(Queue* q) {
    pthread_mutex_lock(&q->lock);  // Lock the queue

    // Wait if the queue is empty
    while (q->size == 0) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }

    // Remove the item from the queue
    int item = q->items[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->size--;
    printf("Consumed: %d | Queue size: %d\n", item, q->size);

    // Signal that the queue is not full (wake up producers)
    pthread_cond_signal(&q->not_full);

    pthread_mutex_unlock(&q->lock);  // Unlock the queue
    return item;
}

// Producer thread function
void* producer(void* arg) {
    Queue* q = (Queue*)arg;
    int item;
    while (1) {
        item = rand() % 100;  // Produce an item (random number)
        enqueue(q, item);     // Add the item to the queue
        sleep(rand() % 3);    // Simulate some time for producing
    }
}

// Consumer thread function
void* consumer(void* arg) {
    Queue* q = (Queue*)arg;
    while (1) {
        int item = dequeue(q); // Remove the item from the queue
        sleep(rand() % 2);     // Simulate some time for consuming
    }
}

int main() {
    Queue q;
    init_queue(&q);

    pthread_t prod[3], cons[3];

    // Create producer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&prod[i], NULL, producer, (void*)&q);
    }

    // Create consumer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&cons[i], NULL, consumer, (void*)&q);
    }

    // Join threads (though the program runs indefinitely)
    for (int i = 0; i < 3; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    return 0;
}

