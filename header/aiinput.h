#ifndef __AI_INPUT_H__
#define __AI_INPUT_H__

enum paddleCheck2 { enemy_init, enemy_start, enemy_wait, enemy_press, enemy_release };

int Enemy_Input (int state) {
  switch (state){
    case enemy_init:
        state = enemy_start;
    break;
      
    case enemy_start:
        state = enemy_wait;
    break;
      
    case enemy_wait:
      if (b6){
        if (enemypaddlepos != 0x40){
        state = enemy_press;
        } else {
        state = enemy_wait;
      }
  } else if (b7){
    if (paddlepos != 0x20){
      state = enemy_press;
    } else {
      state = enemy_wai;
    }
  }
 break;
      
    case enemy_press:
      state = enemy_release;
    break;
      
    case enemy_release:
       if (b6){
        state = enemy_release;
       } else if (b7){
        state = enemy_release;
       } else {
        state = enemy_wait;
       }
    break;
  }
  
  switch (state){
    case enemy_init:
    case enemy_start:
    case enemy_wait:
    break;
      
    case enemy_press:
      if (b6){
        if (enemypaddlepos != 0x40){
          enemypaddlepos = enemypaddlepos << 1;
        } 
      } else if (b7){
        if (enemypaddlepos != 0x02){
          enemypaddlepos = enemypaddlepos >> 1;
        } 
      }
    break;
  }
  
  return state;
}
#endif __AI_INPUT_H__
