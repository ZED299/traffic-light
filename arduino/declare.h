/*******************************************************************************
** Include
*******************************************************************************/

#include <ShiftRegister74HC595.h>

/*******************************************************************************
** Definition
*******************************************************************************/

#define    btn1    6
#define    btn2    7
#define    btn3    8
#define    btn4    9
#define    btn5    10
#define    btn6    11
#define    btn7    12
#define    btn8    13
#define    cbq     A0
#define    btc1    A6
#define    btc2    A7
#define    btc3    A8
#define    btc4    A9

#define    spk     53

#define    r1      23
#define    y1      25
#define    g1      27
#define    r2      29
#define    y2      31
#define    g2      33
#define    r3      35
#define    y3      37
#define    g3      39
#define    r4      41
#define    y4      43
#define    g4      45

#define    t1d     14
#define    t1x     15
#define    t2d     16
#define    t2x     17
#define    t3d     18
#define    t3x     19
#define    t4d     A1
#define    t4x     A2

#define    dd1     A3
#define    dd2     A4

/*******************************************************************************
** Global Variable
*******************************************************************************/

ShiftRegister74HC595<8> sr1(47, 49, 51);
ShiftRegister74HC595<8> sr2(A13, A14, A15);

int value, digit1, digit2, digit3, digit4, digit5, digit6, digit7, digit8, \
    digit9, digit10, digit11, digit12, digit13, digit14, digit15, digit16;
int d, run, ndb, t;
long time_led, time_display_led;
int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
int ndb1, ndb2, ndb3, ndb4;
long time_ndb1, time_ndb2, time_ndb3, time_ndb4;
int time_ndb = 10;
/*
  t1: thời gian đèn làn 1
  t2: thời gian đèn làn 2
  t3: thời gian đèn rẽ trái 1
  t4: thời gian đèn rẽ trái 2
*/
int mode = 0;
uint8_t  numberB[] = {
  B11000000, //0
  B11111001, //1
  B10100100, //2
  B10110000, //3
  B10011001, //4
  B10010010, //5
  B10000010, //6
  B11111000, //7
  B10000000, //8
  B10010000 //9
};

/*******************************************************************************
** Function
*******************************************************************************/

void pinmode() {
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btn5, INPUT_PULLUP);
  pinMode(btn6, INPUT_PULLUP);
  pinMode(btn7, INPUT_PULLUP);
  pinMode(btn8, INPUT_PULLUP);
  pinMode(cbq, INPUT_PULLUP);
  pinMode(btc1, INPUT_PULLUP);
  pinMode(btc2, INPUT_PULLUP);
  pinMode(btc3, INPUT_PULLUP);
  pinMode(btc4, INPUT_PULLUP);

  pinMode(spk, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(y1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(y2, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(y3, OUTPUT);
  pinMode(g3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(y4, OUTPUT);
  pinMode(g4, OUTPUT);

  pinMode(t1d, OUTPUT);
  pinMode(t1x, OUTPUT);
  pinMode(t2d, OUTPUT);
  pinMode(t2x, OUTPUT);
  pinMode(t3d, OUTPUT);
  pinMode(t3x, OUTPUT);
  pinMode(t4d, OUTPUT);
  pinMode(t4x, OUTPUT);
  pinMode(dd1, OUTPUT);
  pinMode(dd2, OUTPUT);

  digitalWrite(spk, 1);

  digitalWrite(r1, 0);
  digitalWrite(y1, 0);
  digitalWrite(g1, 0);
  digitalWrite(r2, 0);
  digitalWrite(y2, 0);
  digitalWrite(g2, 0);
  digitalWrite(r3, 0);
  digitalWrite(y3, 0);
  digitalWrite(g3, 0);
  digitalWrite(r4, 0);
  digitalWrite(y4, 0);
  digitalWrite(g4, 0);
  digitalWrite(t1d, 0);
  digitalWrite(t1x, 0);
  digitalWrite(t2d, 0);
  digitalWrite(t2x, 0);
  digitalWrite(t3d, 0);
  digitalWrite(t3x, 0);
  digitalWrite(t4d, 0);
  digitalWrite(t4x, 0);
  digitalWrite(dd1, 1);
  digitalWrite(dd2, 1);
}

void pip() {
  digitalWrite(spk, 0);
  delay(100);
  digitalWrite(spk, 1);
}
void check_btn() {
  Serial.print(digitalRead(btn1));
  Serial.print(digitalRead(btn2));
  Serial.print(digitalRead(btn3));
  Serial.print(digitalRead(btn4));
  Serial.print(digitalRead(btn5));
  Serial.print(digitalRead(btn6));
  Serial.print(digitalRead(btn7));
  Serial.print(digitalRead(btn8));
  Serial.print(digitalRead(btc1));
  Serial.print(digitalRead(btc2));
  Serial.print(digitalRead(btc3));
  Serial.println(digitalRead(btc4));
}

/*******************************************************************************
** EOF
*******************************************************************************/