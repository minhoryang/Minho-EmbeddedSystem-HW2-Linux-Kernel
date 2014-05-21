#include "./fpga_dot.h"

#define IOM_FPGA_DOT_ADDRESS 0x04000210 // pysical address
#define IOM_FPGA_DEMO_ADDRESS 0x04000300 

#define UON 0x00 // IOM
#define UOFF 0x01 // IOM


//Global variable
static unsigned char *iom_fpga_dot_addr;
static unsigned char *iom_dot_demo_addr;

// when write to fpga_dot device  ,call this function
ssize_t fpga_dot_write(unsigned char value[10]) 
{
	int i;

	for(i=0;i<10;i++)
		outb(value[i],(unsigned int)iom_fpga_dot_addr+i);
	
	return sizeof(value);
}


int __init fpga_dot_init(void)
{
	printk("%s\n", __FUNCTION__);
	iom_fpga_dot_addr = ioremap(IOM_FPGA_DOT_ADDRESS, 0x10);
	iom_dot_demo_addr = ioremap(IOM_FPGA_DEMO_ADDRESS, 0x1);
	
	outb(UON,(unsigned int)iom_dot_demo_addr);	    

	return 0;
}

void __exit fpga_dot_exit(void) 
{
	printk("%s\n", __FUNCTION__);
	iounmap(iom_fpga_dot_addr);
}
