#include "RP6RobotBaseLib.h" 
#define MEINEADRESSE 8
#define BYTEBEFEHLE
#include "transmitLib.c"

// TODO: Doppelklick hinzufügen


// +======+=========================+=========================+
// | Code | Befehl                  | Wenn                    |
// +======+=========================+=========================+
// | 1    | Nach rechts drehen      | Bumper rechts gedrückt  |
// | 2    | Nach links drehen       | Bumper links gedrückt   |
// | 3    | Geradeaus fahren        | -- Nach drehen --       |
// | 4    | Langsamer fahren        | Obstacle left/right     |
// | 5    | Normale Geschwindigkeit | Nach langsamer/stop     |
// | 6    | Motor stoppen           | Beide Bumper gerdückt   |
// | 7    | Rückwärts fahren        | Bumper doppelklick      |
// |      |                         |                         |
// +------+-------------------------+-------------------------+

int main(void) {
    initRobotBase();
    task_RP6System();
    task_ACS();
    setACSPwrHigh();
    powerON();
    while (true) {
        task_Bumpers();
        task_ACS();
        
        if(bumper_right) {
            writeString_P("bumper_right : 1\n");
            sendByte(2, 1);
            while (bumper_right) {
                task_RP6System();
            }
            writeString_P("bumper_right END : 3\n");
            sendByte(2, 3);
        } else if(bumper_left) {
            writeString_P("bumper_left : 2\n");
            sendByte(2, 2);
            while (bumper_left) {
                task_RP6System();
            }
            writeString_P("bumper_left END : 3\n");
            sendByte(2, 3);
        }
        
        if(obstacle_left || obstacle_right) {
            writeString_P("obstacle : 4\n");
            sendByte(2, 4);
            while (obstacle_left || obstacle_right) {
                task_RP6System();
            }
            writeString_P("obstacle END : 5\n");
	        sendByte(2, 5);
	    }
    }
}
