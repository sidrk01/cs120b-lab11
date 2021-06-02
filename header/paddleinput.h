#ifndef __PADDLE_INPUT_H__
#define __PADDLE_INPUT_H__

//--------------------
//Period: 300 ms
//-------------------

#define b1 ~PINB & 0x01
#define b2 ~PINB & 0x02
#define b3 ~PINB & 0x40

//global states
enum PaddleCheck {paddle_init, paddle_start, paddle_wait, paddle_press, paddle_release, auto_press, auto_release};

//write paddle pos 
unsigned char paddlepos = 0x10;
//unsigned char rows[3] = {0x03, 0x11, 0x18}
unsigned char autom = 0x00;
//unsigned char pattern = 0x80; //LED pattern - 0: LED off; 1: LEDon
unsigned int index = 1;
//unsigned char row =  rows[index]; //Row(s) displaying pattern.
					//0: display pattern on row 
					//1: do NOT display pattern on row
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
