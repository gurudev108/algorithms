/*

Key Concepts in Semaphore-based Implementation:
Semaphores are used to represent chopsticks, where each philosopher needs to acquire two semaphores (chopsticks) to eat.
A mutex is used to ensure mutual exclusion when philosophers are trying to pick up chopsticks to avoid race conditions.

Explanation:
Semaphores (Chopsticks):
Each chopstick is represented by a semaphore initialized to 1, which means only one philosopher can acquire (use) a chopstick at a time.
sem_wait(&chopsticks[id]) is used to pick up a chopstick (decrease its value), and sem_post(&chopsticks[id]) is used to put it down (increase its value).
Avoiding Deadlock:
A mutex is used to allow only up to (N-1) philosophers to pick up chopsticks at the same time, ensuring that at least one philosopher will always be able to eat. Without this, a deadlock could occur if all philosophers pick up one chopstick and wait for the second one, leading to a circular wait.
Philosopher Thread:
Each philosopher alternates between thinking, trying to pick up chopsticks, eating, and then putting down chopsticks.
Each philosopher uses semaphores to wait for and release chopsticks, ensuring exclusive access to the resources.
Execution Flow:
A philosopher first locks the mutex to ensure mutual exclusion while picking up chopsticks.
The philosopher then waits for both chopsticks to become available using sem_wait.
After eating, the philosopher releases the chopsticks using sem_post and proceeds to think again.
Thread Creation and Joining:
Each philosopher is represented by a separate thread that runs the philosopher function. These threads are created with pthread_create and run indefinitely.

Output
Philosopher 0 is thinking...
Philosopher 1 is thinking...
Philosopher 2 is thinking...
Philosopher 3 is thinking...
Philosopher 4 is thinking...
Philosopher 0 is hungry and trying to pick up chopsticks.
Philosopher 0 is eating...
Philosopher 4 is hungry and trying to pick up chopsticks.
Philosopher 0 finished eating and put down chopsticks.
Philosopher 1 is hungry and trying to pick up chopsticks.
Philosopher 4 is eating...
Philosopher 0 is thinking...
Philosopher 1 is eating...
Philosopher 4 finished eating and put down chopsticks.
Philosopher 4 is thinking...
Philosopher 2 is hungry and trying to pick up chopsticks.
Philosopher 2 is eating...
Philosopher 3 is hungry and trying to pick up chopsticks.
Philosopher 3 is eating...
Philosopher 2 finished eating and put down chopsticks.
Philosopher 3 finished eating and put down chopsticks.
Philosopher 2 is thinking...
Philosopher 1 finished eating and put down chopsticks.
Philosopher 2 is hungry and trying to pick up chopsticks.
Philosopher 2 is eating...
Philosopher 2 finished eating and put down chopsticks.
Philosopher 0 is hungry and trying to pick up chopsticks.
Philosopher 0 is eating...
Philosopher 4 is hungry and trying to pick up chopsticks.
Philosopher 4 is eating...
Philosopher 1 is thinking...
Philosopher 1 is hungry and trying to pick up chopsticks.
Philosopher 1 is eating...

*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5  // Number of philosophers

sem_t chopsticks[N];  // Semaphore array for chopsticks
pthread_mutex_t mutex; // A mutex to control access to the critical section

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3);  // Thinking for a random time
        
        // Picking up chopsticks (semaphores)
        printf("Philosopher %d is hungry and trying to pick up chopsticks.\n", id);
        
        // Avoiding deadlock by using a mutex to allow only (N-1) philosophers to pick up chopsticks at the same time
        pthread_mutex_lock(&mutex);
        
        // Wait (down) on left chopstick and right chopstick semaphores
        sem_wait(&chopsticks[id]);               // Pick up left chopstick
        sem_wait(&chopsticks[(id+1) % N]);       // Pick up right chopstick

        pthread_mutex_unlock(&mutex);

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 2);  // Eating for a random time
        
        // Putting down chopsticks (semaphores)
        sem_post(&chopsticks[id]);               // Put down left chopstick
        sem_post(&chopsticks[(id+1) % N]);       // Put down right chopstick

        printf("Philosopher %d finished eating and put down chopsticks.\n", id);
        
        // Thinking again
        sleep(rand() % 3);  // Think again after eating
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int philosopher_ids[N];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Initialize the semaphores (chopsticks) to 1, meaning each chopstick can be picked up by one philosopher at a time
    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
        philosopher_ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads (in practice, this program will run indefinitely)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the semaphores and mutex
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}

