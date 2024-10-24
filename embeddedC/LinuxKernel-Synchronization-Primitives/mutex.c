// sync_mutex_example.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

static struct mutex my_mutex;
static int shared_counter = 0;
static struct task_struct *task1, *task2;

// Thread function
int thread_fn(void *data) {
    int i;
    for (i = 0; i < 5; i++) {
        // Acquire mutex before accessing shared resource
        mutex_lock(&my_mutex);

        shared_counter++;
        printk(KERN_INFO "Thread %s: Shared Counter: %d\n", current->comm, shared_counter);

        // Release the mutex
        mutex_unlock(&my_mutex);

        msleep(1000); // Sleep to simulate work
    }

    return 0;
}

// Module init function
static int __init sync_mutex_init(void) {
    printk(KERN_INFO "Mutex Synchronization Example Module Loaded\n");

    // Initialize mutex
    mutex_init(&my_mutex);

    // Create kernel threads
    task1 = kthread_run(thread_fn, NULL, "Thread1");
    task2 = kthread_run(thread_fn, NULL, "Thread2");

    return 0;
}

// Module exit function
static void __exit sync_mutex_exit(void) {
    printk(KERN_INFO "Mutex Synchronization Example Module Unloaded\n");

    // Clean up
    if (task1) kthread_stop(task1);
    if (task2) kthread_stop(task2);
}

module_init(sync_mutex_init);
module_exit(sync_mutex_exit);

