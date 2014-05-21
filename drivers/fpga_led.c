#include "./drivers.h"
#define IOM_LED_ADDRESS 0x04000016 // pysical address
#define IOM_DEMO_ADDRESS 0x04000300 

#define UON 0x00 // IOM
#define UOFF 0x01 // IOM


//Global variable
static unsigned char *iom_fpga_led_addr;
static unsigned char *iom_demo_addr;

// when write to led device  ,call this function
ssize_t fpga_led_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what) 
{
	unsigned char value;
	const char *tmp = gdata;

	if (copy_from_user(&value, tmp, 1))
		return -EFAULT;

	outb(value,(unsigned int)iom_fpga_led_addr);	    
	
	return length;
}


int __init fpga_led_init(void)
{


	iom_fpga_led_addr = ioremap(IOM_LED_ADDRESS, 0x1);
	iom_demo_addr = ioremap(IOM_DEMO_ADDRESS, 0x1);
	
	outb(UON,(unsigned int)iom_demo_addr);	    

	return 0;
}

void __exit fpga_led_exit(void) 
{
	iounmap(iom_fpga_led_addr);
	iounmap(iom_demo_addr);
}

