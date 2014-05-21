struct wanted{
	char timelapse;
	char count;
	char loc_where;  // 1~4
	char loc_value;  // 1~8
};

struct wanted *revert(int system_called){
	struct wanted *this = (struct wanted *)calloc(1, sizeof(struct wanted));  // TODO REPLACE to KERNEL!
	this->loc_value = system_called % 256;
	this->loc_where = (system_called / 256) % 256;
	this->count = (system_called / 256 / 256) % 256;
	this->timelapse = (system_called / 256 / 256 / 256) % 256;
	return this;
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

void draw(struct wanted *var){
	if(var){
		;
	}else{
		// clean up;
		// draw_lcd(NULL);
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
			// TODO register new timer.
			// register_timer(var->timelapse * 100)
		}
	}
}

