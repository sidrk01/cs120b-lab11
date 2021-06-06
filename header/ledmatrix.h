#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

//------------------------
//Period: 100 ms 
//------------------------

enum Demo_States { init, output};

int Demo_Tick(int state) {
	unsigned char bitmask = 0x01;
	
	switch(state){
		case init:
			state = output;
		break;
			
		case output:
		break;
	}
	
	switch(state){
		case output:
			PORTC = displVal[currow];
			for (unsigned int i = 0; i < currow; i++){
				bitmask = bitmask << 1;
			}
			PORTD = ~bitmask;
			
			currow += 1;
			if (currow >= 6){
				currow = 0;
			}
		break;
		
		default:
		break;
	}
	return state;	
}

#endif //__LED_MATRIX_H__
