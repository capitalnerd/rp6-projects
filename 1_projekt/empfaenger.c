#include "RP6RobotBaseLib.h"
#define BYTEBEFEHLE
#define   MEINEADRESSE 2
#include "transmitLib.c"



void ausweichen(uint8_t richtung) {
    move(50,BWD,DIST_CM (15),true);
    rotate(50,richtung,60,true);
}


int main(void) {
     initRobotBase();
     initByteReception();
     task_RP6System();
     powerON();
     moveAtSpeed(150,150);   
     int speed = 150;
     while(true) {
         changeDirection(FWD);
         if(isByteDa()){
             uint8_t byte=getByte();
             byteDa = false;
             switch(byte){
                case 1:
                    writeString_P("Signal 1 empfangen!\n"); 
                    moveAtSpeed(speed,30);  
                    break;
                case 2:
                    writeString_P("Signal 2 empfangen!\n");
                    moveAtSpeed(30,speed);  
                    break;
                case 3:
                    writeString_P("Signal 3 empfangen!\n");
                    moveAtSpeed(speed,speed);  
                    break;
                case 4:
                    writeString_P("Signal 4 empfangen!\n");
                    speed = 50 ; 
                    writeString_P("Signal 1 empfangen!\n");
                    moveAtSpeed(speed,speed);  
                    break;
                case 5:
                    writeString_P("Signal 5 empfangen!\n");
                    speed = 150 ; 
                    moveAtSpeed(speed,speed);  
                    break;
                case 6 :
                    writeString_P("Signal 6 empfangen!\n");
                    speed = 0 ;
                    moveAtSpeed(speed,speed);  
                    break;
                case 7 :   
                    writeString_P("Signal 7 empfangen!\n");
                    changeDirection(BWD);  
                    break; 
            }    
        }
        if(bumper_left)
        { 
          ausweichen(RIGHT);
          speed = 150 ;
          moveAtSpeed(speed,speed);
        }  
        if(bumper_right)
        {
          ausweichen(LEFT);
          speed = 150 ;
          moveAtSpeed(speed,speed);
        }
        if(bumper_left && bumper_right)
        {
          move(50,BWD,DIST_CM (10),true);
          speed = 150 ;
          moveAtSpeed(speed,speed);
        }
        task_ACS();
        task_RP6System();
     }
     
     
}
