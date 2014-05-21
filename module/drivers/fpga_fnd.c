#define IOM_FND_ADDRESS 0x04000004 // pysical address
#define IOM_DEMO_ADDRESS 0x04000300 

#define UON 0x00 // IOM
#define UOFF 0x01 // IOM



static unsigned char *iom_fpga_fnd_addr;
static unsigned char *iom_fnd_demo_addr;


// when write to fnd device  ,call this function
ssize_t fpga_fnd_write(unsigned char value[4]) 
{
	int i;

	for(i=0;i<4;i++) 
		outb(value[i],(unsigned int)iom_fpga_fnd_addr+i);	    
	
	return sizeof(value);
}

int __init fpga_fnd_init(void)
{
	printk("%s\n", __FUNCTION__);
	iom_fpga_fnd_addr = ioremap(IOM_FND_ADDRESS, 0x4);
	iom_fnd_demo_addr = ioremap(IOM_DEMO_ADDRESS, 0x1);
	
	outb(UON,(unsigned int)iom_fnd_demo_addr);	    


	return 0;
}

void __exit fpga_fnd_exit(void) 
{
	printk("%s\n", __FUNCTION__);
	iounmap(iom_fpga_fnd_addr);
	iounmap(iom_fnd_demo_addr);
}

