#ifndef __PADDLE_INPUT_H__
#define __PADDLE_INPUT_H__

//--------------------
//Period: 300 ms
//-------------------

//global states
enum PaddleCheck {paddle_init, paddle_start, paddle_wait, paddle_press, paddle_release, auto_press, auto_release};

int Paddle_Input(int state){
	switch(state){
		case paddle_init:
			state = paddle_start;
		break;
		
		case paddle_start:
			state = paddle_wait;
		break;
		
		case paddle_wait:
			if (b1){
				if(paddlepos != 0x40){
					state = paddle_press;
				} else {
					state = paddle_wait;
				}
			} else if (b2){
				if (paddlepos != 0x02){
					state = paddle_press;
				} else {
					state = paddle_wait;
				}
			} else if (b3){
				state = auto_press;
			}
		break;
			
		case auto_press:
			if (b3){
				state = auto_press;
			} else {
				state = autorelease;
			}
		break;
			
		case auto_release:
			state = paddle_wait;
		break;
	
		case paddle_press:
			state = paddle_release;
		break;
			
		case paddle_release:
			if (b1){
				state = paddle_release;
			} else if (b2){
				state = paddle_release;
			} else {
				state = paddle_wait;
			}
		break;
	}
	
switch (state){
	case paddle_init:
	case paddle_start:
	case paddle_wait:
	break;
		
	case auto_release:
		if (autom == 0x01){
			autom = 0x00;
		} else {
			autom = 0x01;
		}
	break;
		
	case paddle_press:
		if (b1){
			if (paddlepos != 0x40){
				paddlepos = paddlepos << 1;
			} 
		} else if (b2){
			if (paddlepos != 0x02){
				paddlepos paddlepos >> 1;
			} else {
				paddlepos = paddlepos;
			}
		}
	break;
}
	return state;
}
#endif //__PADDLE__INPUT_H__
