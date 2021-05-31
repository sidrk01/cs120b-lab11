#ifndef __PADDLE_INPUT_H__
#define __PADDLE_INPUT_H__

//--------------------
//Period: 300 ms
//-------------------

#define button1 ~PINB & 0x01
#define button2 ~PINB & 0x02
#define button3 ~PINB & 0x04

//global states
enum PaddleCheck {reset, wait, press_b1, press_b2};

//write paddle pos 
unsigned char pattern = 0x80; //LED pattern - 0: LED off; 1: LEDon
unsigned char row =  0x19; //Row(s) displaying pattern.
					//0: display pattern on row 
					//1: do NOT display pattern on row

int Paddle_Input(int state){
	switch(state){
	case reset:
		state = wait;
	break;
	
	case wait:
		if ((button1) && !(button2) && !(button3)){
			state = press_b1;
		} else if (!(button1) && (button2) && !(button3)){
			state = press_b2;
		} else if (!(button1) && !(button2) && (button3)){
			state = reset;
		} else {
			state = wait;
		}
	break;

	case press_b1:
		if (!(button1) && !(button2) && !(button3)){
			state = wait;
		} else {
			state = press_b1;	
		}
	break;

	case press_b2:
		if (!(button1) && !(button2) && !(button3)){
			state = wait;
		} else {
			state = press_b2;
		}

	break;

	}

	switch (state){
	case reset:
		pattern = 0x80;
		row = 0x19;
	break;

	case wait:
	break;

	case press_b1:

	switch(row){
	   case 0x07:
		row = 0x13;
	   break;

	   case 0x13:
		row = 0x19;
	   break;

	   case 0x19:
		row = 0x1C;
	   break;
		
	   default:
           break;
	}		
	
	break;

	case press_b2:

	switch(row){
           case 0x1C:
                row = 0x19;
           break;

           case 0x19:
                row = 0x13;
           break;

           case 0x13:
                row = 0x07;
           break;
        }
	
	break;	
	}	

return state;
}

#endif //__PADDLE__INPUT_H__
