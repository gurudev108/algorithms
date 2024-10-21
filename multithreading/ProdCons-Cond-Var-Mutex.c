/*

Producer Consumer problem with Mutex and Condition Variable

 In this problem, the producer will produce items and place them into a shared buffer, 
 while the consumer will consume them. Mutexes are used to ensure exclusive access to
 the shared buffer, and condition variables are used to synchronize the producer and 
 consumer threads.

Output - 
Producer produced: 7, buffer size: 1
Consumer consumed: 7, buffer size: 0
Producer produced: 58, buffer size: 1
Consumer consumed: 58, buffer size: 0
Producer produced: 44, buffer size: 1
Consumer consumed: 44, buffer size: 0
Producer produced: 9, buffer size: 1
Producer produced: 65, buffer size: 2
Producer produced: 42, buffer size: 3
Producer produced: 3, buffer size: 4
Producer produced: 29, buffer size: 5
Consumer consumed: 29, buffer size: 4
Producer produced: 3, buffer size: 5
Consumer consumed: 3, buffer size: 4
Consumer consumed: 3, buffer size: 3
Producer produced: 60, buffer size: 4
Producer produced: 99, buffer size: 5
Producer waiting, buffer full.
Consumer consumed: 99, buffer size: 4
Producer produced: 16, buffer size: 5
Consumer consumed: 16, buffer size: 4
Producer produced: 26, buffer size: 5
Producer waiting, buffer full.
Consumer consumed: 26, buffer size: 4
Consumer consumed: 60, buffer size: 3
Producer produced: 10, buffer size: 4
Consumer consumed: 10, buffer size: 3
Consumer consumed: 42, buffer size: 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the shared buffer

int buffer[BUFFER_SIZE];  // Shared buffer
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
        
        // Add the item to the buffer
        buffer[count] = item;
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
        
        // Remove the item from the buffer
        item = buffer[count - 1];
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

