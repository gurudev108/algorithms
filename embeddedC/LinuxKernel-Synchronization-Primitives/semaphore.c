// sync_semaphore_example.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

static struct semaphore my_semaphore;
static int shared_counter = 0;
static struct task_struct *task1, *task2;

int thread_fn(void *data) {
    int i;
    for (i = 0; i < 5; i++) {
        // Down (acquire) the semaphore before accessing shared resource
        if (down_interruptible(&my_semaphore)) {
            printk(KERN_ALERT "Failed to lock semaphore\n");
            return -1;
        }

        shared_counter++;
        printk(KERN_INFO "Thread %s: Shared Counter: %d\n", current->comm, shared_counter);

        // Up (release) the semaphore
        up(&my_semaphore);

        msleep(1000); // Simulate work
    }

    return 0;
}

static int __init sync_semaphore_init(void) {
    printk(KERN_INFO "Semaphore Synchronization Example Module Loaded\n");

    // Initialize the semaphore with a value of 1
    sema_init(&my_semaphore, 1);

    // Create kernel threads
    task1 = kthread_run(thread_fn, NULL, "Thread1");
    task2 = kthread_run(thread_fn, NULL, "Thread2");

    return 0;
}

static void __exit sync_semaphore_exit(void) {
    printk(KERN_INFO "Semaphore Synchronization Example Module Unloaded\n");

    if (task1) kthread_stop(task1);
    if (task2) kthread_stop(task2);
}

module_init(sync_semaphore_init);
module_exit(sync_semaphore_exit);

