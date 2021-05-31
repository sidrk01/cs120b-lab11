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

#include "../header/timer.h"
#include "../header/paddleinput.h"
#include "../header/ledmatrix.h"

typedef struct _task {
        signed char state;
        unsigned long int period;
        unsigned long elapsedTime;
        int (*TickFct) (int);
} task;

        static task task1, task2;
        task* tasks[] = {&task1, &task2};

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
	task1.period = 100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &Demo_Tick;
	
	task2.state = start;
	task2.period = 300;
	task2.elapsedTime = task2.period;
	task2.TickFct = &Paddle_Input;
	
	TimerSet(task1.period);
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
