#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

//------------------------
//Period: 100 ms 
//------------------------

enum Demo_States {init, start, start_seq, paddle_out};
int Demo_Tick(int state) {
	
	//Transitions 
	switch(state){
		case init:
			state = start;
		break;
		
		case start:
			state = start_seq;
		break;
		
		case start_seq:
			state = paddle_out;
		break;
		
		case paddle_out:
			state = paddle_out;
		break;
	}

	//Actions
	switch (state){
		case init:
			PORTC = 0xFF;
		break;
	
		case start:
			PORTD = 0x0F;
		break;
		
		case start_seq:
			PORTD = 0xF0;
		break;
			
		case paddle_out:
			if (paddlepos == 0x10){
				PORTC = 0x38; 
			} else if (paddlepos == 0x20){
				PORTC = 0x70;
			} else if (paddlepos == 0x40){
				PORTC = 0xE0;
			} else if (paddlepos == 0x08){
				PORTC = 0x1C;
			} else if (paddlepos == 0x04){
				PORTC = 0x0E;	
			} else if (paddlepos == 0x02){
				PORTC = 0x07;
			}
			PORTD = 0xFE;
		break;
	}
	
	return state;	
}

#endif //__LED_MATRIX_H__
