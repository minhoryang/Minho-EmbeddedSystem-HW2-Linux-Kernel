#define IOM_FPGA_TEXT_LCD_ADDRESS 0x04000100 // pysical address - 32 Byte (16 * 2)
#define IOM_FPGA_DEMO_ADDRESS 0x04000300 

#define UON 0x00 // IOM
#define UOFF 0x01 // IOM


//Global variable
static unsigned char *iom_fpga_text_lcd_addr;
static unsigned char *iom_lcd_demo_addr;



// when write to fpga_text_lcd device  ,call this function
ssize_t fpga_lcd_write(unsigned char value[32]) 
{
	int i;
	for(i=0;i<32;i++){
		if(!value[i])
			break;
	}
	size_t length = i;

	value[length]=0;
	printk("Get Size : %d / String : %s\n",length,value);

	for(i=0;i<length-1;i++)
		outb(value[i],(unsigned int)iom_fpga_text_lcd_addr+i);
	outb(value[i],(unsigned int)iom_fpga_text_lcd_addr+i);
	
	return length;
}


int __init fpga_lcd_init(void)
{
	printk("%s\n", __FUNCTION__);
	iom_fpga_text_lcd_addr = ioremap(IOM_FPGA_TEXT_LCD_ADDRESS, 0x20);
	iom_lcd_demo_addr = ioremap(IOM_FPGA_DEMO_ADDRESS, 0x1);
	
	outb(UON,(unsigned int)iom_lcd_demo_addr);	    
	return 0;
}

void __exit fpga_lcd_exit(void) 
{
	printk("%s\n", __FUNCTION__);
	iounmap(iom_fpga_text_lcd_addr);
}
