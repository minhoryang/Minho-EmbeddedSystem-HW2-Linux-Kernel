#include <stdio.h>
#include <stdlib.h>

struct wanted{
	char timelapse;
	char count;
	char loc_where;  // 1~4
	char loc_value;  // 1~8
};
struct wanted *revert(int system_called);
int system_call(int timelapse, int count, int loc);
void current_turn(struct wanted *var);
void draw(struct wanted *var);
void next_turn(struct wanted *var);

struct wanted *revert(int system_called){
	struct wanted *this = (struct wanted *)calloc(1, sizeof(struct wanted));  // TODO REPLACE to KERNEL!
	this->loc_value = system_called % 256;
	this->loc_where = (system_called / 256) % 256;
	this->count = (system_called / 256 / 256) % 256;
	this->timelapse = (system_called / 256 / 256 / 256) % 256;
	return this;
}

int system_call(int timelapse, int count, int loc){
	// 3 vars -> 4bytes
	if((timelapse < 1) || (timelapse > 100))
		return 0;
	if((count < 1) || (count > 100))
		return 0;
	char _t = timelapse;
	char _c = count;
	char _lw, _lv;
	if((1000<=loc) && (loc<=8000)){
		_lw = 1;
		_lv = loc / 1000;
	}else if((100<=loc) && (loc<=800)){
		_lw = 2;
		_lv = loc / 100;
	}else if((10<=loc) && (loc<=80)){
		_lw = 3;
		_lv = loc / 10;
	}else if((1<=loc) && (loc<=8)){
		_lw = 4;
		_lv = loc;
	}else{
		return 0;
	}
	return (_t * 256 * 256 * 256) + (_c * 256 * 256) + (_lw * 256) + (_lv);
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

int main(){
	char i = 20;
	char j = 50;
	char k = 1;
	char l = 8;
	int g = (i * 256 * 256 * 256) + (j * 256 * 256) + (k * 256) + l;
	int r;
	printf("%X\n", g);
	printf("%X\n", (r = system_call(i, j, 8000)));
	struct wanted *t = revert(r);
	printf("%d %d %d %d\n", t->timelapse, t->count, t->loc_where, t->loc_value);
	return 0;
}
