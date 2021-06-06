/*	Author: Sidharth Ramkumar (sramk002)
 *  Partner(s) Name: none
 *	Lab Section: 022
 *	Assignment: Lab #11  Exercise #0
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	:wqcode, is my own original work.
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
    /* Insert DDR and PORT initializations */
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
	
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
	task4.elapsedTime = task4_period;
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
