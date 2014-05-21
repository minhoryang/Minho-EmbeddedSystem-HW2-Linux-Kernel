#define IOM_LED_ADDRESS 0x04000016 // pysical address
#define IOM_DEMO_ADDRESS 0x04000300 

#define UON 0x00 // IOM
#define UOFF 0x01 // IOM


//Global variable
static unsigned char *iom_fpga_led_addr;
static unsigned char *iom_led_demo_addr;

// when write to led device  ,call this function
ssize_t fpga_led_write(unsigned char value) 
{
	outb(value,(unsigned int)iom_fpga_led_addr);	    
	
	return sizeof(value);
}


int __init fpga_led_init(void)
{
	printk("%s\n", __FUNCTION__);


	iom_fpga_led_addr = ioremap(IOM_LED_ADDRESS, 0x1);
	iom_led_demo_addr = ioremap(IOM_DEMO_ADDRESS, 0x1);
	
	outb(UON,(unsigned int)iom_led_demo_addr);	    

	return 0;
}

void __exit fpga_led_exit(void) 
{
	printk("%s\n", __FUNCTION__);
	iounmap(iom_fpga_led_addr);
	iounmap(iom_led_demo_addr);
}

