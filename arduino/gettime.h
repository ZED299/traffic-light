/*******************************************************************************
** Include
*******************************************************************************/

#include <DFRobot_DS1307.h>

/*******************************************************************************
** Global Variable
*******************************************************************************/

DFRobot_DS1307 DS1307;
uint16_t getTimeBuff[7] = {0};
long gettime = 0;

/*******************************************************************************
** Function
*******************************************************************************/

void get_time() {
  if (millis() - gettime > 500) {
    DS1307.getTime(getTimeBuff);
    char outputarr[128];
    sprintf(outputarr, "time: %d/%d/%d-%d %d:%d:%d\r\n",
            getTimeBuff[6],
            getTimeBuff[5],
            getTimeBuff[4],
            getTimeBuff[3],
            getTimeBuff[2],
            getTimeBuff[1],
            getTimeBuff[0]
           );
    Serial.print(outputarr);

    if (getTimeBuff[2] <=  23 && getTimeBuff[2] >= 4) {
      if (digitalRead(cbq) == 0) {
        digitalWrite(dd1, 1);
        digitalWrite(dd2, 1);
      }
      else {
        digitalWrite(dd1, 0);
        digitalWrite(dd2, 0);
      }
    }
    if (getTimeBuff[2] > 23 || getTimeBuff[2] < 4) {
      digitalWrite(dd1, 1);
      digitalWrite(dd2, 0);
    }

    gettime = millis();
  }
}

/*******************************************************************************
** EOF
*******************************************************************************/