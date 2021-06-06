#ifndef __PADDLE_INPUT_H__
#define __PADDLE_INPUT_H__

//--------------------
//Period: 300 ms
//-------------------

//global states
enum PaddleCheck {paddle_init, paddle_wait, press_left, wait_left, press_right, wait_right, press_reset, wait_reset};

int Paddle_Input(int state){
	unsigned char displ = 0x00;
	unsigned char bitmask = 0x01;

	switch(state){
		case paddle_init:
			state = paddle_wait;
		break;
			
		case paddle_wait:
			if (b1){
				state = press_left;
			} else if (b2){
				state = press_right;
			} else if (b3) {
				state = press_reset;
			} else {
				state = paddle_wait;
			}
		break;
			
		case press_left:
			if (b1){
				state = wait_left; 
			} else if (b2){
				state = press_right;
			} else {
				state = paddle_wait;
			}
		break;
			
		case wait_left:
			if (b1){
				state = wait_left;
			} else if (b2){
				state = press_right;
			} else {
				state = paddle_wait;
			}
		break;
		
		case press_right:
			if (b1){
				state = press_left;
			} else if (b2){
				state = wait_right;
			} else {
				state = paddle_wait;
			}
		break;
			
		case wait_right:
			if (b1){
				state = press_left;
			} else if (b2){
				state = wait_right;
			} else {
				state = paddle_wait;
			}
		break;
		
		case press_reset:
			state = wait_reset;
		break;
		
		case wait_reset:
			if (b3){
				state = wait_reset;
			} else {
				state = paddle_wait;
			}
		break;
	}
	
	switch (state){
		case press_left:
			if (playerpos <= 5){
				playerpos += 1;
			}
		break;
		
		case press_right:
			if (playerpos >= 2){
				playerpos -= 1;
			}
		break;
		
		case press_reset:
			playerpos = 4;
			aipos = 3;
			ballVal = 0x00;
			ballRow = 0x03;
			ballCol = 4;
			rowDispl = 0x10;
		break;
		
		default:
		break;
	}
			
	for (unsigned int i = 0; i <= playerpos + 1; i++){
		if (i >= playerpos - 1){
			displ |= bitmask;
		}
		bitmask = bitmask << 1;
	}
	displVal[4] = displ;
			
	return state;
}
#endif //__PADDLE__INPUT_H__
