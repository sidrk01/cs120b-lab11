#ifndef __BALL_MOVE_H__
#define __BALL_MOVE_H__

enum Ball_Movement { ball_init, ball_start, ball_wait, ball_move, ball_bounce };

int Ball_Tick(int state){
//  if (i == 999){
    //state = ball_init;
  //  i = 0; 
  //}
  
  switch (state){
    case ball_init:
      state = ball_start;
    break;
      
    case ball_start:
      state = ball_wait;
    break;
      
    case ball_wait:
        if (b4){
          state = ball_wait;
          paddlepos = 0x10;
          enemypaddlepos = 0x10;
        }
      
      if (paddlepos == 0x20){
        state = ball_move;
        x_pos_left = 0x01;
        x_pos_right = 0x00;
        
      } else if (paddlepos == 0x04){
        state = ball_move;
        x_pos_left = 0x00;
        x_pos_right = 0x01;
      
      } else if (b5){
        state = ball_move;
        if (paddlepos == 0x10){
          x_pos_left = 0x01;
          x_pos_right = 0x00;
        } else {
          x_pos_left = 0x00;
          x_pos_right = 0x01;
        }
        
      } else {
        state = ball_wait;
      }
      
      break;
      
    case ball_move:
        if (b4){
          state = ball_start;
          paddlepos = 0x10;
          enemypaddlepos = 0x10;
        } else {
          state = ball_move;
        }
      break;
      
    case ball_bounce:
        state = ball_move;
    break;
      
    default:
    break;
  }
  
  switch (state){
    case ball_init:
    break;
      
    case ball_start:
        ypos = 0x02;
        xpos = 0x08;
        x_pos_left = 0x01;
        x_pos_right = 0x00;
        xpos_index = xpos;
        paddlepos = 0x10;
        enemypaddlepos = 0x10;
    break;
      
    case ball_wait:
    break;
     
    case ball_move:
      if (x_pos_left == 0x01){
        if (xpos != 0x80){
          xpos = xpos << 1;
        } else {
          x_pos_left = 0x00;
          x_pos_right = 0x01;
        }
      }
      
      if (x_pos_right == 0x01){
        if (xpos != 0x01){
          xpos = xpos >> 1;
        } else {
          xpos = xpos << 1;
          x_pos_left = 0x01;
          x_pos_right = 0x00;
        }
      }
      
      if (y_pos_up == 0x01){
        if (ypos != 0x80){
          ypos = ypos << 1;
        }
        
        if (ypos == 0x80){
          
            if (enemypaddlepos == xpos){
              ypos = ypos >> 1;
              y_pos_down = 0x01;
              y_pos_up = 0x00;
              
            } else if (enemypaddlepos == (xpos << 1)){
              if (x_pos_left == 0x01){
                if (enemypaddlepos == (xpos >> 1)){
                  ypos = ypos >> 1;
                  y_pos_down = 0x01;
                  y_pos_up = 0x00;
                }
           } else {
                ypos = ypos >> 1;
                y_pos_down = 0x01;
                y_pos_up = 0x00;
              }
          
        } else if (enemypaddlepos == (xpos >> 1)){
            if (x_pos_right == 0x01){
              if (enemypaddlepos == (xpos << 1)){
                ypos = ypos >> 1;
                y_pos_down = 0x01;
                y_pos_up = 0x00;
              }
            } else {
              ypos = ypos >> 1;
              y_pos_down = 0x01;
              y_pos_up = 0x00;
            }
          } else {
             state = ball_init;
              enemypaddlepos = 0x10;
              y_pos_up = 0x00;
              y_pos_down = 0x01;
            }
      }
  }
     
     if (y_pos_down == 0x01){
      if (ypos != 0x01){
        ypos = ypos >> 1;
      }
       
      if (ypos == 0x01){
        if (paddlepos == xpos){
          ypos = ypos << 2;
          y_pos_down = 0x00;
          y_pos_up = 0x01;
        } else if (paddlepos == (xpos << 1)){
          if (x_pos_left == 0x01){
            if (paddlepos == (xpos >> 1)){
              ypos = ypos << 3;
              y_pos_down = 0x00;
              y_pos_up = 0x01;
            }
          } else {
            ypos = ypos << 2;
            y_pos_down = 0x00;
            y_pos_up = 0x01;
          }
        } else if (paddlepos == (xpos >> 1)){
          if (x_pos_right == 0x01){
            if (paddlepos == (xpos << 1)){
              ypos = ypos << 3;
              y_pos_down = 0x00;
              y_pos_up = 0x01;
            }
          } else {
            ypos = ypos << 2;
            y_pos_down = 0x00;
            y_pos_up = 0x01;
          }
        } else {
         state = ball_init;
        paddlepos = 0x10;
          y_pos_up = 0x01;
          y_pos_down = 0x00;
        }
      }
     }
     break;
      
    case ball_bounce:
      break;
      
  }
  
  return state;
      
}

#endif __BALL_MOVE_H__
