// sync_spinlock_example.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

static spinlock_t my_spinlock;
static int shared_counter = 0;
static struct task_struct *task1, *task2;

int thread_fn(void *data) {
    int i;
    for (i = 0; i < 5; i++) {
        // Acquire spinlock before accessing shared resource
        spin_lock(&my_spinlock);

        shared_counter++;
        printk(KERN_INFO "Thread %s: Shared Counter: %d\n", current->comm, shared_counter);

        // Release spinlock
        spin_unlock(&my_spinlock);

        msleep(1000); // Simulate work
    }

    return 0;
}

static int __init sync_spinlock_init(void) {
    printk(KERN_INFO "Spinlock Synchronization Example Module Loaded\n");

    // Initialize spinlock
    spin_lock_init(&my_spinlock);

    // Create kernel threads
    task1 = kthread_run(thread_fn, NULL, "Thread1");
    task2 = kthread_run(thread_fn, NULL, "Thread2");

    return 0;
}

static void __exit sync_spinlock_exit(void) {
    printk(KERN_INFO "Spinlock Synchronization Example Module Unloaded\n");

    if (task1) kthread_stop(task1);
    if (task2) kthread_stop(task2);
}

module_init(sync_spinlock_init);
module_exit(sync_spinlock_exit);

