/*	Author: Sidharth Ramkumar (sramk002)
 *  Partner(s) Name: none
 *	Lab Section: 022
 *	Assignment: Lab #11  Exercise #0
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	:wqcode, is my own original work.
 */
/*
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
#include "../header/ledmatrix.h"
#include "../header/paddleinput.h"
#include "../header/aiinput.h"
#include "../header/ballmove.h"


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
	task1.period = 1;
	task1.elapsedTime = task1.period;
	task1.TickFct = &Demo_Tick;
	
	task2.state = start;
	task2.period = 1000;
	task2.elapsedTime = task2.period;
	task2.TickFct = &Ball_Tick;
	
	task3.state = start;
	task3.period = 20;
	task3.elapsedTime = task3.period;
	task3.TickFct = &Paddle_Input;
	
	task4.state = start;
	task4.period = 350;
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
*/

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <unistd.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "task.h"
#include "gcd.h"
#endif

//--------------------------------------
// LED Matrix Demo SynchSM
// Period: 100 ms
//--------------------------------------


unsigned char playerPosition = 4, AIPosition = 3;
unsigned char rowDisplays[5];
unsigned char currentRow = 0;

enum Display_States {display_init, display_display};

int Display_Tick(int state) {
	unsigned char tmpC = 0x00, tmpD = 0x00;

	switch (state) {
		case display_init:
			state = display_display;
			break;
		case display_display:
			break;
	}

	switch(state){
		case display_display:
			tmpC = rowDisplays[currentRow];
			unsigned char mask = 0x01;
			for (int i=0;i<currentRow;i++){
				mask *= 2;
			}
			tmpD = mask;

			currentRow++;
			if (currentRow >= 6){
				currentRow = 0;
			}

			break;
		default:
			break;
	}


	PORTC = tmpC;
	PORTD = ~tmpD;
	return state;
}

unsigned char ballVector = 0x00;
//first bit: 0 is right, 1 is left
//second bit: 1 is down, 0 is up
unsigned char ballRow = 0x03, ballRowDisplay = 0x10, ballCol = 4;


enum Player_States {player_init, player_wait, player_pressLeft, player_waitLeft, player_pressRight, player_waitRight, player_pressReset, player_waitReset};
int Player_Tick(int state) {
	unsigned char tmpDisplay = 0x00;
	unsigned char tmpA = ~PINA;

	switch(state){
		case player_init:
			state = player_wait;
			break;
		case player_wait:
			if (tmpA & 0x01){
				state = player_pressLeft;
			} else if (tmpA & 0x02){
				state = player_pressRight;
			} else if (tmpA & 0x04) {
				state = player_pressReset;
			} else {
				state = player_wait;
			}
			break;
		case player_pressLeft:
			if (tmpA & 0x01){
				state = player_waitLeft;
			} else if (tmpA & 0x02){
				state = player_pressRight;
			} else {
				state  = player_wait;
			}
			break;
		case player_waitLeft:
			if (tmpA & 0x01){
				state = player_waitLeft;
			} else if (tmpA & 0x02) {
				state = player_pressRight;
			} else {
				state = player_wait;
			}
			break;
		case player_pressRight:
			if (tmpA & 0x01){
				state = player_pressLeft;
			} else if (tmpA & 0x02){
				state = player_waitRight;
			} else {
				state  = player_wait;
			}
			break;
		case player_waitRight:
			if (tmpA & 0x01){
				state = player_pressLeft;
			} else if (tmpA & 0x02) {
				state = player_waitRight;
			} else {
				state = player_wait;
			}
			break;
		case player_pressReset:
				state = player_waitReset;
				break;
		case player_waitReset:
			if (tmpA & 0x04){
				state = player_waitReset;
			} else {
				state = player_wait;
			}
			break;
	}


	switch(state){
		case player_pressLeft:
			if (playerPosition <= 5){
				playerPosition++;
			}
			break;
		case player_pressRight:
			if (playerPosition >= 2){
				playerPosition--;
			}
			break;
		case player_pressReset:
			playerPosition = 4; AIPosition = 3; ballRow = 0x03; ballRowDisplay = 0x10; ballCol = 4; ballVector = 0x00;
	}


	unsigned char mask = 0x01;
	for (int i=0; i <= playerPosition+1; i++){
		if (i >= playerPosition-1){
			tmpDisplay |= mask;
		}
		mask *= 2;
	}
	rowDisplays[4] = tmpDisplay;
	return state;
}


enum AI_States {init};

int AI_Tick(int state){

	unsigned char tmpDisplay = 0x00;



	int num = rand() % 10;

	int difference = AIPosition - ballCol;
	if (num < 7){
		if (difference > 0 && AIPosition >= 2){
			AIPosition--;
		} else if (difference < 0 && AIPosition <= 5){
			AIPosition++;
		}
	} else {
		if (difference > 0 && AIPosition <= 5){
			AIPosition++;
		} else if (difference < 0 && AIPosition >= 2){
			AIPosition--;
		} else {
			if (AIPosition <= 5){
				AIPosition++;
			} else {
				AIPosition--;
			}
		}
	}

	unsigned char mask = 0x01;
	for (int i=0; i <= AIPosition+1; i++){
		if (i >= AIPosition-1){
			tmpDisplay |= mask;
		}
		mask *= 2;
	}


	rowDisplays[0] = tmpDisplay;

	unsigned char tmpB = AIPosition;
	PORTB &= 0x0F;
	PORTB |= tmpB;

	return state;
}


enum Ball_States {ball_init, ball_active};

void ToggleX(){
	if (ballVector & 0x01){
		ballVector &= 0xFE;
	} else {
		ballVector |= 0x01;
	}
}

void ToggleY(){
	if (ballVector & 0x02){
		ballVector &= 0xFD;
	} else {
		ballVector |= 0x02;
	}
}


int Ball_Tick(int state){
	switch(state){
		case ball_init:
			state = ball_active;
			break;
		case ball_active:
			break;
	}

	unsigned char tmpB = ballCol << 4;
	PORTB &= 0xF0;
	PORTB |= tmpB;

	switch(state){

		case ball_active:
			if (ballVector & 0x02){
				//moving down
				if (ballRow < 3){
					ballRow++;
				} else {
					//at bottom row, check for collision
					if (playerPosition-1 == ballCol) {
						ToggleY();
						ToggleX();
						ballRow--;
					} else if (playerPosition+1 == ballCol){
						ToggleY();
						ToggleX();
						ballRow--;
					} else if (playerPosition == ballCol){
						ToggleY();
						ballRow--;
					} else {
						ballVector = 0x03, ballRow = 0x01, ballRowDisplay = 0x08, ballCol = 3;
						//end game
					}
				}
			} else {
				//moving up
				if (ballRow > 1){
					ballRow--;
				} else {
					if (AIPosition-1 == ballCol) {
						ToggleY();
						ToggleX();
						ballRow++;
					} else if (AIPosition+1 == ballCol){
						ToggleY();
						ToggleX();
						ballRow++;
					} else if (AIPosition == ballCol){
						ToggleY();
						ballRow++;
					} else {
						//end game
						ballVector = 0x00, ballRow = 0x03, ballRowDisplay = 0x10, ballCol = 4;
					}
				}
			}

			//handle left/right movement
			if (ballVector & 0x01){
				//going left
				if (ballRowDisplay <= 0x40){
					ballRowDisplay <<= 1;
					ballCol++;
				} else {
					//if col 7, change directions
					ToggleX();
					ballRowDisplay >>= 1;
					ballCol--;
				}
			} else {
				if (ballRowDisplay >= 0x02){
					ballRowDisplay >>= 1;
					ballCol--;
				} else {
					//if col 0, change directions
					ToggleX();
					ballRowDisplay <<= 1;
					ballCol++;
				}
			}
			break;
		default:
			break;
	}


	for (int i=1; i<=3;i++){
		if (i == ballRow){
			rowDisplays[i] = ballRowDisplay;
		} else {
			rowDisplays[i] = 0;
		}
	}

	return state;
}



int main(void) {
    /* Insert DDR and PORT initializations */
		DDRA = 0x00; PORTA = 0xFF;
		DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    static task task1, task2, task3, task4;
    task *tasks[] = {&task1, &task2, &task3, &task4};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    const char start = 0;

    task1.state = start;
    task1.period = 20;
    task1.elapsedTime = task1.period;
    task1.TickFct = &Player_Tick;

		task2.state = start;
		task2.period = 350;
		task2.elapsedTime = task2.period;
		task2.TickFct = &AI_Tick;

		task3.state = start;
		task3.period = 1000;
		task3.elapsedTime = task3.period;
		task3.TickFct = &Ball_Tick;

		task4.state = start;
		task4.period = 1;
		task4.elapsedTime = task4.period;
		task4.TickFct = &Display_Tick;

    unsigned short i;

    unsigned long GCD = tasks[0]->period;
    for (i = 1;i<numTasks;i++){
      GCD = findGCD(GCD, tasks[i]->period);
    }

    TimerSet(GCD);
    TimerOn();

    /* Insert your solution below */
    while (1) {
      for (i=0; i<numTasks; i++) {
        if (tasks[i]->elapsedTime == tasks[i]->period){
          tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
          tasks[i]->elapsedTime = 0;
        }
        tasks[i]->elapsedTime += GCD;
      }
      while(!TimerFlag);
      TimerFlag = 0;
    }
    return 1;
}
