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
};

struct wanted *revert(int system_called){
	struct wanted *this;// = (struct wanted *)calloc(1, sizeof(struct wanted));  // TODO REPLACE to KERNEL!
	this->loc_value = system_called % 256;
	this->loc_where = (system_called / 256) % 256;
	this->count = (system_called / 256 / 256) % 256;
	this->timelapse = (system_called / 256 / 256 / 256) % 256;
	this->line[0].now = 4;
	this->line[0].accel = +1;
	this->line[0].line = "20091631";
	this->line[0].size = 8;
	this->line[1].now = 2;
	this->line[1].accel = +1;
	this->line[1].line = "Ryang Min Ho";
	this->line[1].size = 12;
	return this;
}

char *calc_lcd(struct wanted *var){
	char *c;// = (char *)calloc(32, sizeof(char));
	int i = 0, j, k;
	for(k=0; k<2; k++){
		for(j=0; j < var->line[k].now; i++, j++)
			c[i] = ' ';
		for(j=0; j < var->line[k].size; i++, j++)
			c[i] = var->line[k].line[j];
		for(j=0; j < 16 - var->line[k].size - var->line[k].now; i++, j++)
			c[i] = ' ';
	}
	return c;
}

void draw_clean(){
	fpga_lcd_write("                                ");
	fpga_led_write(my_fpga_led[0]);
	fpga_fnd_write("");
	fpga_dot_write(my_fpga_dot[0]);
	gpio_fnd_write(0xFF);
	gpio_led_write(my_gpio_led[0]);
}

void draw(struct wanted *var){
	if(var){
		fpga_lcd_write(calc_lcd(var));
		fpga_led_write(my_fpga_led[var->loc_value]);
		char c[4] = {
			var->count /10 /10 /10 %10 + '0',
			var->count /10 /10 %10 + '0',
			var->count /10 %10 + '0',
			var->count %10 + '0'};
		fpga_fnd_write(c);
		fpga_dot_write(my_fpga_dot[var->loc_value]);
		gpio_fnd_write(my_gpio_fnd(var->loc_where, var->loc_value));
		gpio_led_write(my_gpio_led[var->loc_where]);
	}else{
		draw_clean();
	}
}

void next_turn(struct wanted *var){
	if(var){
		if(var->count){
			var->count--;
			switch(var->loc_value){
				case 9:
					var->loc_value = 1;
					var->loc_where++;
					break;
				default:
					var->loc_value++;
					break;
			}
			switch(var->loc_where){
				case 5:
					var->loc_where = 1;
				default:
					break;
			}
			switch(var->line[0].now){
				case 0:
					var->line[0].accel = +1;
					var->line[0].now = 1;
					break;
				case 8:
					var->line[0].accel = -1;
					var->line[0].now = 7;
					break;
				default:
					var->line[0].now += var->line[0].accel;
					break;
			}
			switch(var->line[1].now){
				case 0:
					var->line[0].accel = +1;
					var->line[0].now = 1;
					break;
				case 4:
					var->line[0].accel = -1;
					var->line[0].now = 3;
					break;
				default:
					var->line[1].now += var->line[1].accel;
					break;
			}
			// TODO register new timer.
			// register_timer(var->timelapse * 100)
		}
	}
}

void current_turn(struct wanted *var){
	if(var){
		if(var->count){
			draw(var);
			next_turn(var);
		}else{
			draw(NULL);
		}
	}
}
