#include <linux/kernel.h>

asmlinkage int sys_dev_driver(int timelapse, int count, int loc){
	// 3 vars -> 4bytes
	if((timelapse < 1) || (timelapse > 100))
		return -1;
	if((count < 1) || (count > 100))
		return -1;
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
		return -1;
	}
	return (_t * 256 * 256 * 256) + (_c * 256 * 256) + (_lw * 256) + (_lv);
}
