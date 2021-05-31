#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

//------------------------
//Period: 100 ms 
//------------------------

enum Demo_States {shift};
int Demo_Tick(int state) {
	
	//Transitions 
	switch(state){
		case shift:
			break;
		
		default:
			state = shift;
			break;
	}

	//Actions
	switch (state){
	case shift:
	PORTC = pattern; //Pattern to display 
        PORTD = row;    // Row(s) displaying pattern
	break;
	}
	
	return state;	
}

#endif //__LED_MATRIX_H__
