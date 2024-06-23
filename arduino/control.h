/*******************************************************************************
** Function
*******************************************************************************/

void serial_control()
{
  if (Serial.available())
  {
    String str = Serial.readString();
    if (str.indexOf("mode1") != -1)
    {
      mode = 0;
      pip();
    }
    else
    {
      if (str.indexOf("mode2") != -1)
      {
        mode = 1;
        pip();
        delay(500);
        pip();
      }
    }
    String a = Serial.readString();
  }
}

void display()
{
  if (millis() - time_display_led > 50)
  {
    //t1 = t2 = t3 = t4 = t++;
    // làn đỏ vàng xanh
    digit14 = digit6 = (t1 / 10) % 10 ;
    digit13 = digit5 = t1 % 10 ;
    digit10 = digit2 = (t2 / 10) % 10 ;
    digit9 = digit1 = t2 % 10 ;
    // rẽ trái
    digit16 = digit8 = (t3 / 10) % 10 ;
    digit15 = digit7 = t3 % 10 ;
    digit12 = digit4 = (t4 / 10) % 10 ;
    digit11 = digit3 = t4 % 10 ;

    uint8_t numberToPrint1[] = {numberB[digit16], numberB[digit15], \
                                numberB[digit14], numberB[digit13], \
                                numberB[digit12], numberB[digit11], \
                                numberB[digit10], numberB[digit9]}; //8led trc
    uint8_t numberToPrint2[] = {numberB[digit8], numberB[digit7], \
                                numberB[digit6], numberB[digit5], \
                                numberB[digit4], numberB[digit3], \
                                numberB[digit2], numberB[digit1]}; //8led sau

    sr1.setAll(numberToPrint1);
    sr2.setAll(numberToPrint2);
    time_display_led = millis();
  }
}

void blink()
{
  for (int i = 0; i < 2; i++)
  {
    sr1.setAllLow(); // set all pins Low (off)
    sr2.setAllLow(); // set all pins Low (off)
    delay(500);
    sr1.setAllHigh(); // set all pins High (on)
    sr2.setAllHigh(); // set all pins High (on)
    delay(500);
  }
}

void read_btn()
{
  if (digitalRead(btn1) == 0)
  {
    if (d < 50)
    {
      d++;
    }
    if (d == 10)
    {
      pip();
      run = 1;
    }
  }
  else 
  {
    if (digitalRead(btn2) == 0)
    {
      if (d < 50)
      {
        d++;
      }
      if (d == 10)
      {
        pip();
        run = 0; t1 = 0; t2 = 0;
        blink();
      }
    }
    else
    {
      if (digitalRead(btc1) == 0)
      {
        if (d < 50)
        {
          d++;
        }
        if (d == 10)
        {
          pip();
          ndb1 = 1;
          time_ndb1 = millis();
        }
      }
      else
      {
        if (digitalRead(btc2) == 0)
        {
          if (d < 50)
          {
            d++;
          }
          if (d == 10)
          {
            pip();
            ndb2 = 1;
            time_ndb2 = millis();
          }
        }
        else
        {
          if (digitalRead(btc3) == 0)
          {
            if (d < 50)
            {
              d++;
            }
            if (d == 10)
            {
              pip();
              ndb3 = 1;
              time_ndb3 = millis();
            }
          }
          else
          {
            if (digitalRead(btc4) == 0)
            {
              if (d < 50)
              {
                d++;
              }
              if (d == 10)
              {
                pip();
                ndb4 = 1;
                time_ndb4 = millis();
              }
            }
            else
            {
              d = 0;
            }
          }
        }
      }
    }
  }
}

void rst_time_ndb()
{
  if (millis() - time_ndb1 > 10000)
  {
    ndb1 = 0;
  }
  if (millis() - time_ndb2 > 10000)
  {
    ndb2 = 0;
  }
  if (millis() - time_ndb3 > 10000)
  {
    ndb3 = 0;
  }
  if (millis() - time_ndb4 > 10000)
  {
    ndb4 = 0;
  }
}

void run_rt()
{
  if (digitalRead(r4) == 1)
  {
    t3 = t2;
    digitalWrite(t1x, 1);
    digitalWrite(t1d, 0);
    digitalWrite(t3x, 1);
    digitalWrite(t3d, 0);
  }
  else
  {
    if (digitalRead(g4) == 1)
    {
      t3 = t2;
      digitalWrite(t1x, 0);
      digitalWrite(t1d, 1);
      digitalWrite(t3x, 0);
      digitalWrite(t3d, 1);
    }
    else
    {
      t3 = 0;
      digitalWrite(t1x, 0);
      digitalWrite(t1d, 1);
      digitalWrite(t3x, 0);
      digitalWrite(t3d, 1);
    }
  }
  if (digitalRead(r1) == 1)
  {
    t4 = t1;
    digitalWrite(t2x, 1);
    digitalWrite(t2d, 0);
    digitalWrite(t4x, 1);
    digitalWrite(t4d, 0);
  }
  else
  {
    if (digitalRead(g1) == 1)
    {
      t4 = t1;
      digitalWrite(t2x, 0);
      digitalWrite(t2d, 1);
      digitalWrite(t4x, 0);
      digitalWrite(t4d, 1);
    }
    else
    {
      t4 = 0;
      digitalWrite(t2x, 0);
      digitalWrite(t2d, 1);
      digitalWrite(t4x, 0);
      digitalWrite(t4d, 1);
    }
  }
}

void runbt()
{
  if (mode == 0) {// r25 x20 v5
    //làn 1A
    if (t >= 0 && t < 25)
    {
      if (ndb1 == 0)
      {
        digitalWrite(r1, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }
      else
      {
        digitalWrite(r1, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }

      if (ndb3 == 0)
      {
        digitalWrite(r3, 1); digitalWrite(y3, 0); digitalWrite(g3, 0);
      }
      else
      {
        digitalWrite(r3, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }
      t1 = 25 - t;
    }
    if (t >= 25 && t < 45)
    {
      if (ndb1 == 0)
      {
        digitalWrite(r1, 0); digitalWrite(y1, 0); digitalWrite(g1, 1);
      }
      else
      {
        digitalWrite(r1, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }

      if (ndb3 == 0)
      {
        digitalWrite(r3, 0); digitalWrite(y3, 0); digitalWrite(g3, 1);
      }
      else
      {
        digitalWrite(r3, 1); digitalWrite(y3, 0); digitalWrite(g3, 0);
      }
      t1 = 45 - t;
    }
    if (t >= 45 && t < 50)
    {
      if (ndb1 == 0)
      {
        digitalWrite(r1, 0); digitalWrite(y1, 1); digitalWrite(g1, 0);
      }
      else
      {
        digitalWrite(r1, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }

      if (ndb3 == 0)
      {
        digitalWrite(r3, 0); digitalWrite(y3, 1); digitalWrite(g3, 0);
      }
      else
      {
        digitalWrite(r3, 1); digitalWrite(y3, 0); digitalWrite(g3, 0);
      }
      t1 = 50 - t;
    }
    //làn 2A
    if (t >= 0 && t < 20)
    {
      if (ndb2 == 0)
      {
        digitalWrite(r2, 0); digitalWrite(y2, 0); digitalWrite(g2, 1);
      }
      else
      {
        digitalWrite(r2, 1); digitalWrite(y2, 0); digitalWrite(g2, 0);
      }

      if (ndb4 == 0)
      {
        digitalWrite(r4, 0); digitalWrite(y4, 0); digitalWrite(g4, 1);
      }
      else
      {
        digitalWrite(r4, 1); digitalWrite(y4, 0); digitalWrite(g4, 0);
      }
      t2 = 20 - t;
    }
    if (t >= 20 && t < 25)
    {
      if (ndb2 == 0)
      {
        digitalWrite(r2, 0); digitalWrite(y2, 1); digitalWrite(g2, 0);
      }
      else
      {
        digitalWrite(r2, 1); digitalWrite(y2, 0); digitalWrite(g2, 0);
      }

      if (ndb4 == 0)
      {
        digitalWrite(r4, 0); digitalWrite(y4, 1); digitalWrite(g4, 0);
      }
      else
      {
        digitalWrite(r4, 1); digitalWrite(y4, 0); digitalWrite(g4, 0);
      }
      t2 = 25 - t;
    }
    if (t >= 25 && t < 50)
    {
      if (ndb2 == 0)
      {
        digitalWrite(r2, 1); digitalWrite(y2, 0); digitalWrite(g2, 0);
      }
      else
      {
        digitalWrite(r2, 1); digitalWrite(y2, 0); digitalWrite(g2, 0);
      }

      if (ndb4 == 0)
      {
        digitalWrite(r4, 1); digitalWrite(y4, 0); digitalWrite(g4, 0);
      }
      else
      {
        digitalWrite(r4, 1); digitalWrite(y4, 0); digitalWrite(g4, 0);
      }
      t2 = 50 - t;
    }
  }
  else
  {
    // r25 x23 v2
    //làn 1B
    if (t >= 0 && t < 25)
    {
      if (ndb1 == 0)
      {
        digitalWrite(r1, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }
      else
      {
        digitalWrite(r1, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }

      if (ndb3 == 0)
      {
        digitalWrite(r3, 1); digitalWrite(y3, 0); digitalWrite(g3, 0);
      }
      else
      {
        digitalWrite(r3, 1); digitalWrite(y3, 0); digitalWrite(g3, 0);
      }
      t1 = 25 - t;
    }
    if (t >= 25 && t < 48)
    {
      if (ndb1 == 0)
      {
        digitalWrite(r1, 0); digitalWrite(y1, 0); digitalWrite(g1, 1);
      }
      else
      {
        digitalWrite(r1, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }

      if (ndb3 == 0)
      {
        digitalWrite(r3, 0); digitalWrite(y3, 0); digitalWrite(g3, 1);
      }
      else
      {
        digitalWrite(r3, 1); digitalWrite(y3, 0); digitalWrite(g3, 0);
      }
      t1 = 48 - t;
    }
    if (t >= 48 && t < 50)
    {
      if (ndb1 == 0)
      {
        digitalWrite(r1, 0); digitalWrite(y1, 1); digitalWrite(g1, 0);
      }
      else
      {
        digitalWrite(r1, 1); digitalWrite(y1, 0); digitalWrite(g1, 0);
      }

      if (ndb3 == 0)
      {
        digitalWrite(r3, 0); digitalWrite(y3, 1); digitalWrite(g3, 0);
      }
      else
      {
        digitalWrite(r3, 1); digitalWrite(y3, 0); digitalWrite(g3, 0);
      }
      t1 = 50 - t;
    }
    //làn 2B
    if (t >= 0 && t < 23)
    {
      if (ndb2 == 0)
      {
        digitalWrite(r2, 0); digitalWrite(y2, 0); digitalWrite(g2, 1);
      }
      else
      {
        digitalWrite(r2, 1); digitalWrite(y2, 0); digitalWrite(g2, 0);
      }

      if (ndb4 == 0)
      {
        digitalWrite(r4, 0); digitalWrite(y4, 0); digitalWrite(g4, 1);
      }
      else
      {
        digitalWrite(r4, 1); digitalWrite(y4, 0); digitalWrite(g4, 0);
      }
      t2 = 23 - t;
    }
    if (t >= 23 && t < 25)
    {
      if (ndb2 == 0)
      {
        digitalWrite(r2, 0); digitalWrite(y2, 1); digitalWrite(g2, 0);
      }
      else
      {
        digitalWrite(r2, 1); digitalWrite(y2, 0); digitalWrite(g2, 0);
      }

      if (ndb4 == 0)
      {
        digitalWrite(r4, 0); digitalWrite(y4, 1); digitalWrite(g4, 0);
      }
      else
      {
        digitalWrite(r4, 1); digitalWrite(y4, 0); digitalWrite(g4, 0);
      }
      t2 = 25 - t;
    }
    if (t >= 25 && t < 50)
    {
      if (ndb2 == 0)
      {
        digitalWrite(r2, 1); digitalWrite(y2, 0); digitalWrite(g2, 0);
      }
      else
      {
        digitalWrite(r2, 1); digitalWrite(y2, 0); digitalWrite(g2, 0);
      }

      if (ndb4 == 0)
      {
        digitalWrite(r4, 1); digitalWrite(y4, 0); digitalWrite(g4, 0);
      }
      else
      {
        digitalWrite(r4, 1); digitalWrite(y4, 0); digitalWrite(g4, 0);
      }
      t2 = 50 - t;
    }
  }
}

void nhay_vang()
{
  if (t % 2 == 1)
  {
    digitalWrite(r1, 0); digitalWrite(y1, 1); digitalWrite(g1, 0);
    digitalWrite(r2, 0); digitalWrite(y2, 1); digitalWrite(g2, 0);
    digitalWrite(r3, 0); digitalWrite(y3, 1); digitalWrite(g3, 0);
    digitalWrite(r4, 0); digitalWrite(y4, 1); digitalWrite(g4, 0);
    digitalWrite(t1d, 0); digitalWrite(t1x, 0);
    digitalWrite(t2d, 0); digitalWrite(t2x, 0);
    digitalWrite(t3d, 0); digitalWrite(t3x, 0);
    digitalWrite(t4d, 0); digitalWrite(t4x, 0);
  }
  else
  {
    digitalWrite(r1, 0); digitalWrite(y1, 0); digitalWrite(g1, 0);
    digitalWrite(r2, 0); digitalWrite(y2, 0); digitalWrite(g2, 0);
    digitalWrite(r3, 0); digitalWrite(y3, 0); digitalWrite(g3, 0);
    digitalWrite(r4, 0); digitalWrite(y4, 0); digitalWrite(g4, 0);
    digitalWrite(t1d, 0); digitalWrite(t1x, 0);
    digitalWrite(t2d, 0); digitalWrite(t2x, 0);
    digitalWrite(t3d, 0); digitalWrite(t3x, 0);
    digitalWrite(t4d, 0); digitalWrite(t4x, 0);
  }
  t1 = t2 = 99;
  t3 = t4 = 99;
}

void runled()
{
  if (run == 1)
  {
    if (millis() - time_led > 500)
    {
      t++;
      if (ndb == 0)
      {
        if (t > 50)
        {
          t = 0;
          serial_control();
        }
      }
      else
      {
        if (t > 10)
        {
          t = 0;
          ndb = 0;
          serial_control();
        }
      }
      time_led = millis();
    }
    if (getTimeBuff[2] <=  23 && getTimeBuff[2] >= 4)
    {
      runbt();
      run_rt();
    }
    else
    {
      if (getTimeBuff[2] > 23 || getTimeBuff[2] < 4) {
        nhay_vang();
      }
    }
  }
  else
  {
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
    t = 0;
  }
}

/*******************************************************************************
** EOF
*******************************************************************************/