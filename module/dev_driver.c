#include <linux/init.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <linux/slab.h>

#include "./4bytes.c"
#include "./drivers/gpio_fnd.c"
#include "./drivers/gpio_led.c"
#include "./drivers/fpga_dot.c"
#include "./drivers/fpga_fnd.c"
#include "./drivers/fpga_lcd.c"
#include "./drivers/fpga_led.c"

#define DEV_MAJOR 242
#define DEV_NAME "dev_device"

// XXX : No Usage Counter.
int _open(struct inode *minode, struct file *mfile){
	printk("20091631 Open\t%p\n", (void *)mfile);
	return 0;
}
int _release(struct inode *minode, struct file *mfile){
	printk("20091631 Release\t%p\n", mfile);
	return 0;
}
ssize_t _write(struct file *mfile, const char *gdata, size_t length, loff_t *off_what){
	int *data = (int *)gdata;
	printk("20091631 WRITE\t%p\t%d\n", mfile, *data);
	return sizeof(*data);
}


static struct file_operations _fops = {
	.open = _open,
	.release = _release,
	.write = _write,
	.ioctl = NULL
};


bool isInit[6] = {false, };
int __init dev_device_init(void){
	int result;
	if((result = register_chrdev(DEV_MAJOR, DEV_NAME, &_fops)) < 0){
		printk(KERN_WARNING "Failed to register.\n");
		return result;
	}
	if(gpio_fnd_init())
		goto failed;
	isInit[0] = true;
	if(gpio_led_init())
		goto failed;
	isInit[1] = true;
	if(fpga_dot_init())
		goto failed;
	isInit[2] = true;
	if(fpga_fnd_init())
		goto failed;
	isInit[3] = true;
	if(fpga_lcd_init())
		goto failed;
	isInit[4] = true;
	if(fpga_led_init())
		goto failed;
	isInit[5] = true;

	printk("20091631 Init\n");
	return 0;
failed:
	if(isInit[0])
		gpio_fnd_exit();
	if(isInit[1])
		gpio_led_exit();
	if(isInit[2])
		fpga_dot_exit();
	if(isInit[3])
		fpga_fnd_exit();
	if(isInit[4])
		fpga_lcd_exit();
	if(isInit[5])
		fpga_led_exit();
	return 1;
}
void __exit dev_device_exit(void){
	gpio_fnd_exit();
	gpio_led_exit();
	fpga_dot_exit();
	fpga_fnd_exit();
	fpga_lcd_exit();
	fpga_led_exit();
	unregister_chrdev(DEV_MAJOR, DEV_NAME);
	printk("20091631 Exit\n");
}
module_init(dev_device_init);
module_exit(dev_device_exit);
MODULE_AUTHOR("20091631MINHORYANG");
MODULE_LICENSE("GPL");
