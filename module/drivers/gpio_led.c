#include "./gpio_led.h"

#define LED_GPBCON 0x11400040   
#define LED_GPBDAT 0x11400044  

static unsigned char *gpio_led_data;
static unsigned int *gpio_led_ctrl;


ssize_t gpio_led_write(unsigned short led_buff)  
{
    printk("DATA : %d\n",led_buff);
    outb (led_buff, (unsigned int)gpio_led_data);

    return sizeof(led_buff);
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
