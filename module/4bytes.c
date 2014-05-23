struct strrow{
	int now;
	int accel;
	char *line;
	int size;
};

struct wanted{
	char timelapse;
	char count;
	char loc_where;  // 1~4
	char loc_value;  // 1~8
	struct strrow line[2];
	char print[32];
};

static struct wanted now;

void revert(int system_called){
	now.loc_value = system_called % 256;
	now.loc_where = (system_called / 256) % 256;
	now.count = (system_called / 256 / 256) % 256;
	now.timelapse = (system_called / 256 / 256 / 256) % 256;
	now.line[0].now = 4;
	now.line[0].accel = +1;
	now.line[0].line = "20091631";
	now.line[0].size = 8;
	now.line[1].now = 2;
	now.line[1].accel = +1;
	now.line[1].line = "Ryang Min Ho";
	now.line[1].size = 12;
}

void calc_lcd(){
	int i = 0, j, k;
	for(k=0; k<2; k++){
		for(j=0; j < now.line[k].now; i++, j++)
			now.print[i] = ' ';
		for(j=0; j < now.line[k].size; i++, j++)
			now.print[i] = now.line[k].line[j];
		for(j=0; j < 16 - now.line[k].size - now.line[k].now; i++, j++)
			now.print[i] = ' ';
	}
}

void draw_clean(){
	fpga_lcd_write("                                ");
	fpga_led_write(my_fpga_led[0]);
	fpga_fnd_write("");
	fpga_dot_write(my_fpga_dot[0]);
	gpio_fnd_write(0xFF);
	gpio_led_write(my_gpio_led[0]);
}

void draw(){
	calc_lcd();
	fpga_lcd_write(now.print);
	fpga_led_write(my_fpga_led[now.loc_value]);
	char c[4] = {
		now.count /10 /10 /10 %10 + '0',
		now.count /10 /10 %10 + '0',
		now.count /10 %10 + '0',
		now.count %10 + '0'};
	fpga_fnd_write(c);
	fpga_dot_write(my_fpga_dot[now.loc_value]);
	gpio_fnd_write(my_gpio_fnd(now.loc_where, now.loc_value));
	gpio_led_write(my_gpio_led[now.loc_where]);
}

void next_turn(){
	if(now.count){
		now.count--;
		now.loc_value++;
		switch(now.loc_value){
			case 9:
				now.loc_value = 1;
				now.loc_where++;
				break;
		}
		switch(now.loc_where){
			case 5:
				now.loc_where = 1;
				break;
		}
		switch(now.line[0].now){
			case 0:
				now.line[0].accel = +1;
				now.line[0].now = 1;
				break;
			case 8:
				now.line[0].accel = -1;
				now.line[0].now = 7;
				break;
			default:
				now.line[0].now += now.line[0].accel;
				break;
		}
		switch(now.line[1].now){
			case 0:
				now.line[1].accel = +1;
				now.line[1].now = 1;
				break;
			case 4:
				now.line[1].accel = -1;
				now.line[1].now = 3;
				break;
			default:
				now.line[1].now += now.line[1].accel;
				break;
		}
		// register new timer.
		timer_add();
	}
}

void current_turn(){
	if(now.count){
		draw();
		next_turn();
	}else{
		draw_clean();
	}
}
