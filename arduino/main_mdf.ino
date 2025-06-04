/*******************************************************************************
** Includes
*******************************************************************************/

#include "declare.h"
#include "gettime.h"
#include "control.h"

/*******************************************************************************
** Function
*******************************************************************************/

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  pinmode();

  DS1307.begin();
  DS1307.stop();
  /*uint16_t setTimeBuff[7] = {40, 59, 20, 7, 12, 1, 2025};// giây, phút , giờ, thứ, ngày , tháng , năm
  DS1307.setTime(setTimeBuff);
  DS1307.saveTimeToEEPROM();
  DS1307.setTimeFromEEPROM();
  DS1307.start();*/
  DS1307.setSqwPinMode(DS1307.eSquareWave_1Hz);

  blink();
}

void loop() {
  read_btn();
  runled();
  display();
  get_time();
  //check_btn();
}

/*******************************************************************************
** EOF
*******************************************************************************/
