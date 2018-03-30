#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define MAJOR_NUMBER 61

MODULE_LICENSE("GPL");

/* forward declaration */
int onebyte_open(struct inode *inode, struct file *filep);
int onebyte_release(struct inode *inode, struct file *filep);
ssize_t onebyte_read(struct file *filep, char *buf, size_t count,
	       	loff_t *f_pos);
ssize_t onebyte_write(struct file *filep, const char *buf, size_t count,
	       	loff_t *f_pos);
static int onebyte_init(void);
static void onebyte_exit(void);

/* definition of file_operation structure*/
struct file_operations onebyte_fops = 
{
	.read =  onebyte_read,
	.write = onebyte_write,
	.open = onebyte_open,
	.release = onebyte_release,
};

char *onebyte_data = NULL;

int onebyte_open(struct inode *inode, struct file *filep)
{
	return 0; // always successful
}

int onebyte_release(struct inode *indoe, struct file *filep)
{
	return 0; // always successful
}

ssize_t onebyte_read(struct file *filep, char *buf, size_t count,
	       	loff_t *f_pos)
{
	/* please complete the function on your own */
	copy_to_user(buf, onebyte_data, 1);
	return 1;
}

/**
 * @brief Called whenever the device is written to.
 * @param filep A pointer to a file object.
 * @param buf The buffer containing the string to write.
 * @param count The length of buffer.
 * @param The offset if required.
 */
ssize_t onebyte_write(struct file *filep, const char *buf, size_t count,
		loff_t *f_pos)
{
	/* please complete the function on your own */
	if(count < 1)
		return 0;
	*onebyte_data = *buf;
	return 1;
}

static int onebyte_init(void)
{
	int result;
	/* register the device */
	result = register_chrdev(MAJOR_NUMBER, "onebyte", &onebyte_fops);
	if (result < 0)
	{
		return result;
	}
	/* allocate one byte of memory for storage. */
	/* kmalloc is just like malloc, the second parameter is the type of */
	/* memory to be allocated. */
	/* To release the memory allocated by kmalloc, use kfree. */
	onebyte_data = kmalloc(sizeof(char), GFP_KERNEL);
	if(!onebyte_data)
	{
		onebyte_exit();
		/* cannot allocate memory */
		/* return no memroy error, negative signify a failure */
		return -ENOMEM;
	}
	/* initialize the value to be X */
	*onebyte_data = 'X';
	printk(KERN_ALERT "This is a onebyte device module \n");
	return 0;
}

static void onebyte_exit(void)
{
	if(onebyte_data)
	{
		kfree(onebyte_data);
		onebyte_data = NULL;
	}
	unregister_chrdev(MAJOR_NUMBER, "onebyte");
	printk(KERN_ALERT "Onebyte device module is unloaded\n");
}

MODULE_LICENSE("GPL");
module_init(onebyte_init);
module_exit(onebyte_exit);

