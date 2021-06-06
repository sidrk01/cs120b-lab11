#ifndef __BALL_MOVE_H__
#define __BALL_MOVE_H__

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
                        rowSwitch();
                        ballRow -= 1;
                    } else if (playerpos + 1 == ballCol ){
                        colSwitch();
                        rowSwitch();
                        ballRow -= 1;
                    } else if (playerpos == ballCol){
                        colSwitch(); 
                        ballRow -= 1;
                    } else {
                        ballRow = 0x01;
                        ballCol = 4;
                        rowDispl = 0x08;
                        ballVal = 0x03;
                        
                    }
                }
            } else {
                if (ballRow > 1){
                    ballRow -= 1;
                } else {
                    if (aipos - 1 == ballCol){
                        colSwitch();
                        rowSwitch();
                        ballRow += 1;
                    } else if (aipos + 1 == ballCol){
                        colSwitch();
                        rowSwitch();
                        ballRow += 1;
                    } else if (aipos == ballCol){
                        colSwitch();
                        ballRow += 1;
                    } else {
                        ballRow = 0x03;
                        ballCol = 4;
                        rowDispl = 0x10;
                        ballVal = 0x00;
                        
                    }
                }
            }
            
            if (ballVal & 0x01){
                if (rowDispl <= 0x40){
                    rowDispl = rowDispl << 1;
                    ballCol += 1;
                } else {
                    rowSwitch();
                    rowDispl = rowDispl >> 1;
                    ballCol -= 1;
                }
            } else {
                if (rowDispl >= 0x02){
                    rowDispl = rowDispl >> 1;
                    ballCol -= 1;
                } else {
                    rowSwitch();
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

#endif __BALL_MOVE_H__
