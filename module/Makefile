obj-m := fpga_dot.o fpga_fnd.o fpga_lcd.o fpga_led.o gpio_fnd.o gpio_led.o

KDIR := /root/mylinux/kernel/kernel-root
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean :
	rm -rf *.o
	rm -rf *.ko
	rm -rf *.mod.c
	rm -rf *.order
	rm -rf *.symvers
	rm -rf .*.cmd
	rm -rf .tmp_versions
