/*	Author: Sidharth Ramkumar (sramk002)
 *  Partner(s) Name: none
 *	Lab Section: 022
 *	Assignment: Lab #11  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	:wqcode, is my own original work.
 * 
 *	Demo Video - https://youtu.be/xWI4_t_5kRs
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define b1 ~PINB & 0x01
#define b2 ~PINB & 0x02
#define b3 ~PINB & 0x04
#define b4 ~PINB & 0x08
#define b5 ~PINB & 0x10
#define b6 ~PINB & 0x20
#define b7 ~PINB & 0x40

unsigned int playerpos = 4; 
unsigned int aipos = 3;

unsigned char displVal[5];
unsigned int currow = 0;

unsigned char ballVal = 0x00;
unsigned char ballRow = 0x03;
unsigned char rowDispl = 0x10;
unsigned int ballCol = 4;
//unsigned char row =  rows[index]; //Row(s) displaying pattern.
					//0: display pattern on row 
					//1: do NOT display pattern on row

#include "../header/timer.h"

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
			
	for (unsigned int i = 0; i < playerpos; i++){
		if (i > playerpos){
			displ |= bitmask;
		}
		bitmask = bitmask << 1;
	}
	displVal[4] = displ;
			
	return state;
}

enum paddleCheck2 { enemy_init };

int Enemy_Input (int state) {
     

  unsigned char tmpDispl = 0x00;
  unsigned char bitmask = 0x01;
  
 int numRand = rand() % 10;
 int posLoc = aipos - ballCol;
 
 switch(state){
  default:
  
  if (numRand < 7){
        aipos -= 1;
      }
    } else if (posLoc < 0){
        aipos += 1;
      }
  } else {
      aipos += 1;
    } else if (posLoc < 0){
    } else {
      if (aipos <= 5){
        aipos += 1;
      } else {
        aipos -= 1;
      }
    }
  }
  
  for (unsigned int i = 0; i <= aipos + 1; i++){
    if ( i > aipos){
      tmpDispl |= bitmask;
    }
    bitmask = bitmask << 1;
  }
  
  displVal[0] = tmpDispl;
  
  break;
      
  }
  
  return state;
}
enum Ball_Movement { ball_init, ball_move};

void rowSwitch(){
    if (ballVal & 0x01){
        ballVal = ballVal & 0xFE;
    } else {
        ballVal = ballVal | 0x01;
    }
}

void colSwitch(){
    if (ballVal & 0x02){
        ballVal = ballVal & 0xFD;
    } else {
        ballVal = ballVal | 0x02;
    }
}

int Ball_Tick(int state){
    
    switch (state){
        case ball_init:
             state = ball_move;
        break;
            
        case ball_move:
        break;
    }
    
    switch (state){
        case ball_move:
            if (ballVal & 0x02){
                if (ballRow < 3){
                    ballRow += 1;
                } else {
                    if (playerpos - 1 == ballCol){
                        colSwitch();
                        ballRow -= 1;
                    } else if (playerpos + 1 == ballCol ){
=                        rowSwitch();
                        ballRow -= 1;
                    } else if (playerpos == ballCol){
                        colSwitch(); 
                    } else {
                        ballCol = 4;
                        ballVal = 0x03;
                        
                    }
                }
            } else {
                if (ballRow > 1){
                    ballRow -= 1;
                } else {
                    if (aipos - 1 == ballCol){
                        colSwitch();
                        ballRow += 1;
                    } else if (aipos + 1 == ballCol){
                        rowSwitch();
                        ballRow += 1;
                    } else if (aipos == ballCol){
                        colSwitch();
                    } else {
                        ballRow = 0x03;
                        rowDispl = 0x10;
                        
                    }
                }
            }
            
            if (ballVal & 0x01){
                if (rowDispl <= 0x40){
                    rowDispl = rowDispl << 1;
                } else {
                    rowDispl = rowDispl >> 1;
                    ballCol -= 1;
                }
            } else {
                if (rowDispl >= 0x02){
                    rowDispl = rowDispl >> 1;
                } else {
                    rowDispl = rowDispl << 1;
                    ballCol += 1;
                }
            }
            break;
           
        default:
           break;
    }
        for (unsigned int i = 1; i <= 3; i++){
            if (i == ballRow){
                displVal[i] = rowDispl;
            } else {
                displVal[i] = 0;
            }
        }
      return state;
         
}

typedef struct _task {
        signed char state;
        unsigned long int period;
        unsigned long elapsedTime;
        int (*TickFct) (int);
} task;

        static task task1, task2, task3, task4;
        task* tasks[] = { &task1, &task2, &task3, &task4 };

        const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
        const char start = -1;

void TimerISR();

int main(void) {
    
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	task1.state = start;
	task1.period = 3;
	task1.elapsedTime = task1.period;
	task1.TickFct = &Demo_Tick;
	
	task2.state = start;
	task2.period = 500;
	task2.elapsedTime = task2.period;
	task2.TickFct = &Ball_Tick;
	
	task3.state = start;
	task3.period = 50;
	task3.elapsedTime = task3.period;
	task3.TickFct = &Paddle_Input;
	
	task4.state = start;
	task4.period = 300;
	task4.elapsedTime = task4.period;
	task4.TickFct = &Enemy_Input;
	
	TimerSet(1);
	TimerOn();
  
    while (1) {
	while (!TimerFlag);
	TimerFlag = 0;	
	
    }
    return 1;
}

void TimerISR() {
	unsigned char i; 
	for (i = 0; i < numTasks; ++i){
		if (tasks[i]->elapsedTime >= tasks[i]->period){
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += tasks[i]->period;
	}
}
