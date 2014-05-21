#define LED_GPBCON 0x11400040   
#define LED_GPBDAT 0x11400044  

static unsigned char *gpio_led_data;
static unsigned int *gpio_led_ctrl;


ssize_t led_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what)  
{
	/*
    const char *tmp = gdata;
    
    if (copy_from_user(&led_buff, tmp, length)) // 2byte receive from application
        return -EFAULT;
	*/

    unsigned short led_buff=0;
    printk("DATA : %d\n",led_buff);
    outb (led_buff, (unsigned int)gpio_led_data);

    return length;
}

int __init gpio_led_init(void) 
{
	printk("%s\n", __FUNCTION__);
    unsigned int get_ctrl_io=0;

    gpio_led_data = ioremap(LED_GPBDAT, 0x01);
    if(gpio_led_data==NULL)
    {   
        printk("ioremap failed!\n");
        return -1;
    }

    gpio_led_ctrl = ioremap(LED_GPBCON, 0x04);
    if(gpio_led_ctrl==NULL)  
    {
        printk("ioremap failed!\n");
        return -1;
    } else {         
        get_ctrl_io=inl((unsigned int)gpio_led_ctrl);

        get_ctrl_io|=(0x11110000);  
        outl(get_ctrl_io,(unsigned int)gpio_led_ctrl);    
    }

    outb(0xF0, (unsigned int)gpio_led_data);

    return 0;
}

void __exit gpio_led_exit(void)
{
	printk("%s\n", __FUNCTION__);
    outb(0xF0, (unsigned int)gpio_led_data);
    iounmap(gpio_led_data);
    iounmap(gpio_led_ctrl);


}
