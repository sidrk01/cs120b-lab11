#ifndef __AI_INPUT_H__
#define __AI_INPUT_H__

#include <stdlib.h>

enum paddleCheck2 { enemy_init };

int Enemy_Input (int state) {
     

  unsigned char tmpDispl = 0x00;
  unsigned char bitmask = 0x01;
  
 int numRand = rand() % 10;
 int posLoc = aipos - ballCol;
 
 switch(state){
  default:
  
  if (numRand < 7){
    if (posLoc > 0){
      if (aipos >= 2){
        aipos -= 1;
      }
    } else if (posLoc < 0){
      if (aipos <= 5){
        aipos += 1;
      }
    }
  } else {
    if (posLoc > 0 && aipos <= 5){
      aipos += 1;
    } else if (posLoc < 0 && aipos >= 2){
      aipos -= 1;
    } else {
      if (aipos <= 5){
        aipos += 1;
      } else {
        aipos -= 1;
      }
    }
  }
  
  for (unsigned int i = 0; i <= aipos + 1; i++){
    if ( i >= aipos - 1){
      tmpDispl |= bitmask;
    }
    bitmask = bitmask << 1;
  }
  
  displVal[0] = tmpDispl;
  
  break;
      
  }
  
  return state;
}
#endif __AI_INPUT_H__
