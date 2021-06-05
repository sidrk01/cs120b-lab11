#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

//------------------------
//Period: 100 ms 
//------------------------

enum Demo_States {init, start, start_seq, paddle_out, ball_out, enemy_out};
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
			state = ball_out;
		break;
			
		case ball_out:
			state = enemy_out;
		break;
			
		case enemy_out:
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
		
		case ball_out:
			if ((x_pos_left == 0x01) && (y_pos_up == 0x01) && (ypos == 0x80)){
				ypos = ypos << 1;
				xpos = xpos >> 1;
				PORTD = ~ypos;
				x_pos_left = 0x00;
				x_pos_right = 0x01;
				y_pos_up = 0x00;
				y_pos_down = 0x01;
			} else if ((x_pos_right == 0x01) && (y_pos_up  == 0x01) && (ypos == 0x80)){
				ypos = ypos >> 1;
				xpos = xpos << 1;
				PORTD = ~ypos;
				x_pos_left = 0x01;
				x_pos_right = 0x00;
				y_pos_up = 0x00;
				y_pos_down = 0x01;
			} else if ((x_pos_right == 0x01) && (y_pos_down == 0x01) && (ypos == 0x01)){
				ypos = ypos << 1;
				xpos = xpos << 1;
				PORTD = ~ypos;
				x_pos_left = 0x01;
				x_pos_right = 0x00;
				y_pos_up = 0x01;
				y_pos_down = 0x00;
			} else if ((x_pos_left == 0x01) && (y_pos_down == 0x01) && (ypos == 0x01)){
				ypos = ypos << 1;
				xpos = xpos >> 1;
				PORTD = ~ypos;
				x_pos_left = 0x00;
				x_pos_right = 0x01;
				y_pos_up = 0x01;
				y_pos_down = 0x00;
			} else {
				PORTD = ~ypos;
			}
				PORTC = xpos;
			break;
			
		case enemy_out:
			PORTC = 0x7F;
			
	}
	
	return state;	
}

#endif //__LED_MATRIX_H__
