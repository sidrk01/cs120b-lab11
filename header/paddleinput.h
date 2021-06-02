#ifndef __PADDLE_INPUT_H__
#define __PADDLE_INPUT_H__

//--------------------
//Period: 300 ms
//-------------------

#define b1 ~PINB & 0x01
#define b2 ~PINB & 0x02
#define b3 ~PINB & 0x04

//global states
enum PaddleCheck {reset, b1_press, b1_wait, b2_press, b2_wait};

//write paddle pos 
unsigned char rows[3] = {0x03, 0x11, 0x18}
unsigned char pattern = 0x80; //LED pattern - 0: LED off; 1: LEDon
unsigned int index = 1;
unsigned char row =  rows[index]; //Row(s) displaying pattern.
					//0: display pattern on row 
					//1: do NOT display pattern on row

int Paddle_Input(int state){
	switch(state){
	case reset:
		if (!(b1) && !(b2) && !(b3)){
			state = b1_press;	
		} else if (!(b1) && (b2) && !(b3)){
			state = b2_press;
		} else {
			state = reset;
		}	
	break;
	
	case b1_press:
		if (!(b1) && !(b2) && !(b3)){
			state = b1_wait;
		} else {
			state = b1_press;
		}
	break;

	case b2_press:
		if (!(b1) && !(b2) && !(b3)){
			state = b2_wait;
		} else {
			state = b2_press;
		}
	break;

	case b1_wait:
		if ((b1) && !(b2) && !(b3)){
			state = b1_press;
		} else if (!(b1) && (b2) && !(b3)){
			state = b2_press;
		} else if (!(b1) && !(b2) && (b3)){
			state = reset;
		} else {
			state = b1_wait;
		}
	break;
			
	case b2_wait:
		if ((b1) && !(b2) && !(b3)){
			state = b1_press;
		} else if (!(b1) && (b2) && !(b3)){
			state = b2_press;
		} else if (!(b1) && !(b2) && (b3)){
			state = reset;
		} else {
			state = b2_wait;
		}
	break;
	}
	
switch (state){
	case reset:
		index = 1; 
	break;
		
	case b1_press:
		if (index < 2){
			index++;
		} 
	break;
	
	case b2_press:
		if (index > 0){
			index--;
		}
	break;	
		
	default:
	break;
}	

row = rows[index];
return state;
}

#endif //__PADDLE__INPUT_H__
