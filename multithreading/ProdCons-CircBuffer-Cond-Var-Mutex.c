/*

Enhancement to Producer Consumer with Condition Variable and Mutex with Circular buffer instead of standard.
 
Key Changes for Circular Buffer:
Two indices:
in: tracks where the producer will insert the next item.
out: tracks where the consumer will remove the next item.
Circular behavior: The indices in and out use modulo arithmetic (% BUFFER_SIZE) to wrap around the buffer when they reach the end.
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the circular buffer

int buffer[BUFFER_SIZE];  // Shared circular buffer
int in = 0;               // Index for the producer (write position)
int out = 0;              // Index for the consumer (read position)
int count = 0;            // Number of items in the buffer

pthread_mutex_t mutex;             // Mutex to protect shared buffer
pthread_cond_t cond_producer;       // Condition variable for producer
pthread_cond_t cond_consumer;       // Condition variable for consumer

// Function for the producer thread
void* producer(void* args) {
    int item;
    while (1) {
        // Produce an item (here we're just generating a random number)
        item = rand() % 100;
        
        // Lock the mutex to protect shared buffer
        pthread_mutex_lock(&mutex);
        
        // Wait if the buffer is full
        while (count == BUFFER_SIZE) {
            printf("Producer waiting, buffer full.\n");
            pthread_cond_wait(&cond_producer, &mutex);
        }
        
        // Add the item to the circular buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;  // Circular wrap-around
        count++;
        printf("Producer produced: %d, buffer size: %d\n", item, count);
        
        // Signal the consumer that an item has been produced
        pthread_cond_signal(&cond_consumer);
        
        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
        
        // Sleep for a random amount of time (to simulate work)
        sleep(rand() % 3);
    }
    return NULL;
}

// Function for the consumer thread
void* consumer(void* args) {
    int item;
    while (1) {
        // Lock the mutex to protect shared buffer
        pthread_mutex_lock(&mutex);
        
        // Wait if the buffer is empty
        while (count == 0) {
            printf("Consumer waiting, buffer empty.\n");
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        
        // Remove the item from the circular buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;  // Circular wrap-around
        count--;
        printf("Consumer consumed: %d, buffer size: %d\n", item, count);
        
        // Signal the producer that an item has been consumed
        pthread_cond_signal(&cond_producer);
        
        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
        
        // Sleep for a random amount of time (to simulate work)
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Initialize the mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);
    
    // Create the producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Join the threads (this will never actually complete in this example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // Destroy the mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);
    
    return 0;
}

