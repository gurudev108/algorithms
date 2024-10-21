/*

The Dining Philosophers Problem is a classical synchronization problem in which five philosophers are seated around a table. Each philosopher alternates between thinking and eating, and needs two chopsticks (forks) to eat. The challenge is to prevent deadlock (where no philosopher can eat) and starvation (where a philosopher never gets to eat).
Solution Using Mutexes:
One of the simplest ways to avoid deadlock is to use a mutex for each chopstick and to have the philosophers pick up the chopsticks in a way that ensures there will be no circular wait.

Key Points:
1. Mutexes for Chopsticks:
Each chopstick is represented by a mutex. Philosophers must lock two mutexes (chopsticks) to eat.
2. Avoiding Deadlock:
Philosophers are prevented from causing deadlock by having an even philosopher pick up their left chopstick first and an odd philosopher pick up their right chopstick first. This avoids the circular wait condition that would lead to deadlock.
3. Avoiding Starvation:
The philosophers alternate between thinking and eating. Each philosopher eventually gets a chance to eat because they spend time thinking, which allows other philosophers to eat.

Explanation of Execution Flow:
Each philosopher goes through the following states:
Thinking: The philosopher spends some time thinking.
Hungry: The philosopher becomes hungry and tries to pick up both chopsticks.
Eating: Once the philosopher picks up both chopsticks (i.e., locks both mutexes), they eat for a random period.
Put Down Chopsticks: After eating, the philosopher puts down both chopsticks (i.e., unlocks the mutexes), making them available for other philosophers.
By alternating the order in which philosophers pick up chopsticks, the solution prevents deadlock while allowing all philosophers to eat eventually.

Output - 
Philosopher 0 is thinking...
Philosopher 3 is thinking...
Philosopher 1 is thinking...
Philosopher 4 is thinking...
Philosopher 2 is thinking...
Philosopher 0 is hungry and trying to pick up chopsticks.
Philosopher 0 is eating...
Philosopher 0 finished eating and put down chopsticks.
Philosopher 0 is thinking...
Philosopher 3 is hungry and trying to pick up chopsticks.
Philosopher 3 is eating...
Philosopher 2 is hungry and trying to pick up chopsticks.
Philosopher 1 is hungry and trying to pick up chopsticks.
Philosopher 4 is hungry and trying to pick up chopsticks.
Philosopher 3 finished eating and put down chopsticks.
Philosopher 2 is eating...
Philosopher 4 is eating...
Philosopher 2 finished eating and put down chopsticks.
Philosopher 2 is thinking...
Philosopher 1 is eating...
Philosopher 0 is hungry and trying to pick up chopsticks.
Philosopher 3 is thinking...
Philosopher 0 is eating...
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5  // Number of philosophers

pthread_mutex_t chopsticks[N];  // Mutexes for chopsticks

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3);  // Philosopher is thinking for a random time
        
        // Pick up chopsticks (lock mutexes)
        printf("Philosopher %d is hungry and trying to pick up chopsticks.\n", id);
        
        // To avoid deadlock, pick up chopstick with a lower number first
        if (id % 2 == 0) {
            pthread_mutex_lock(&chopsticks[id]);          // Pick up left chopstick
            pthread_mutex_lock(&chopsticks[(id+1) % N]);  // Pick up right chopstick
        } else {
            pthread_mutex_lock(&chopsticks[(id+1) % N]);  // Pick up right chopstick
            pthread_mutex_lock(&chopsticks[id]);          // Pick up left chopstick
        }

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 2);  // Philosopher is eating for a random time
        
        // Put down chopsticks (unlock mutexes)
        pthread_mutex_unlock(&chopsticks[id]);           // Put down left chopstick
        pthread_mutex_unlock(&chopsticks[(id+1) % N]);   // Put down right chopstick
        
        printf("Philosopher %d finished eating and put down chopsticks.\n", id);
        
        sleep(rand() % 3);  // Philosopher is thinking again
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int philosopher_ids[N];

    // Initialize the mutexes (chopsticks)
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        philosopher_ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads (this will not actually terminate in this example)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}

