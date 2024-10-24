/*
Certainly! Writing a simple Linux kernel module is an essential skill for working on kernel-level programming, such as device drivers. Kernel modules are dynamically loadable pieces of code that can be added or removed from the running kernel without rebooting the system.

In this example, I’ll walk you through writing a basic Linux kernel module that prints messages when it’s loaded and unloaded. You can load this module into the kernel, verify it, and then unload it.

### Steps to Write and Load a Simple Linux Kernel Module

#### 1. Write the Kernel Module

Here's a simple Linux kernel module written in C:

```c
// simple_module.c
*/

#include <linux/init.h>    // Needed for the macros
#include <linux/module.h>  // Needed for all kernel modules
#include <linux/kernel.h>  // Needed for KERN_INFO

// Meta information about the module
MODULE_LICENSE("GPL");       // License type
MODULE_AUTHOR("Your Name");  // Author of the module
MODULE_DESCRIPTION("A Simple Linux Kernel Module"); // Description of the module
MODULE_VERSION("1.0");       // Version of the module

// Function that runs when the module is loaded
static int __init simple_module_init(void) {
    printk(KERN_INFO "Simple Module: Loaded into the kernel!\n");
    return 0;  // Return 0 if successful
}

// Function that runs when the module is unloaded
static void __exit simple_module_exit(void) {
    printk(KERN_INFO "Simple Module: Unloaded from the kernel!\n");
}

// Specify the initialization and cleanup functions
module_init(simple_module_init);
module_exit(simple_module_exit);
```

/*
#### 2. Explanation:

- **MODULE_LICENSE("GPL")**: Specifies the license under which the module is released. GPL is the most common for kernel modules.
- **MODULE_AUTHOR()**: Specifies the author of the module.
- **printk()**: Similar to `printf()`, but it logs messages to the kernel log buffer, accessible via `dmesg`.
- **__init and __exit**: Macros used to declare the initialization and cleanup functions for the module.
- **module_init() and module_exit()**: Macros to register the entry and exit points for the module.

#### 3. Compile the Kernel Module

You need to compile the kernel module into a loadable kernel object (`.ko` file). Create a `Makefile` for compiling it.

##### Makefile:
```makefile
obj-m += simple_module.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

Explanation:
- `obj-m += simple_module.o`: This specifies the object file to be built (our kernel module).
- `make -C /lib/modules/...` command will compile the kernel module using the current kernel's build system.

#### 4. Compile the Module

Open a terminal, navigate to the directory where you saved the kernel module (`simple_module.c`) and `Makefile`, then run:

```bash
make
```

This will generate a `simple_module.ko` file, which is the kernel module that can be loaded.

#### 5. Load the Kernel Module

To load the module into the running kernel, use the `insmod` command:

```bash
sudo insmod simple_module.ko
```

#### 6. Verify if the Module is Loaded

To verify that the module has been loaded, use the `lsmod` command:

```bash
lsmod | grep simple_module
```

To check the kernel messages, including the `printk()` output, use:

```bash
dmesg | tail
```

You should see the message: `"Simple Module: Loaded into the kernel!"`

#### 7. Unload the Kernel Module

To remove the module from the kernel, use the `rmmod` command:

```bash
sudo rmmod simple_module
```

Then check `dmesg` again to verify that the message `"Simple Module: Unloaded from the kernel!"` is printed.

#### 8. Clean the Build

If you want to clean up the build artifacts, you can use:

```bash
make clean
```

### Example Output:
When the module is loaded:
```bash
[12345.678901] Simple Module: Loaded into the kernel!
```

When the module is unloaded:
```bash
[12346.789012] Simple Module: Unloaded from the kernel!
```

### Final Thoughts:

This is a simple kernel module to demonstrate how to write, compile, load, and unload a Linux kernel module. In real-world applications, kernel modules can be more complex, handling hardware devices, interrupts, or interacting with various subsystems of the Linux kernel.

You can now expand this knowledge to more advanced kernel programming, such as working with device drivers or kernel synchronization primitives.

*/