#include "./fpga_dot.h"

#define IOM_FPGA_DOT_ADDRESS 0x04000210 // pysical address
#define IOM_FPGA_DEMO_ADDRESS 0x04000300 

#define UON 0x00 // IOM
#define UOFF 0x01 // IOM


//Global variable
static unsigned char *iom_fpga_dot_addr;
static unsigned char *iom_demo_addr;

// when write to fpga_dot device  ,call this function
ssize_t fpga_dot_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what) 
{
	int i;

	unsigned char value[10];
	const char *tmp = gdata;

	if (copy_from_user(&value, tmp, length))
		return -EFAULT;

	for(i=0;i<length;i++)
		outb(value[i],(unsigned int)iom_fpga_dot_addr+i);
	
	return length;
}


int __init fpga_dot_init(void)
{
	iom_fpga_dot_addr = ioremap(IOM_FPGA_DOT_ADDRESS, 0x10);
	iom_demo_addr = ioremap(IOM_FPGA_DEMO_ADDRESS, 0x1);
	
	outb(UON,(unsigned int)iom_demo_addr);	    

	return 0;
}

void __exit fpga_dot_exit(void) 
{
	iounmap(iom_fpga_dot_addr);
}
