/*******************************************************************************
** Function
*******************************************************************************/

void serial_control() {
  if (Serial.available()) {
    String str = Serial.readString();
    if (str.indexOf("mode1") != -1) {
      mode = 0;
      pip();
    } else {
      if (str.indexOf("mode2") != -1) {
        mode = 1;
        pip();
        delay(500);
        pip();
      }
    }
    String a = Serial.readString();
  }
}

void display() {
  if (millis() - time_display_led > 50) {
    //t1 = t2 = t3 = t4 = t++;
    // làn đỏ vàng xanh
    digit14 = digit6 = (t1 / 10) % 10;
    digit13 = digit5 = t1 % 10;
    digit10 = digit2 = (t2 / 10) % 10;
    digit9 = digit1 = t2 % 10;
    // rẽ trái
    digit16 = digit8 = (t3 / 10) % 10;
    digit15 = digit7 = t3 % 10;
    digit12 = digit4 = (t4 / 10) % 10;
    digit11 = digit3 = t4 % 10;

    uint8_t numberToPrint1[] = { numberB[digit16], numberB[digit15],
                                 numberB[digit14], numberB[digit13],
                                 numberB[digit12], numberB[digit11],
                                 numberB[digit10], numberB[digit9]
                               };  //8led trc
    uint8_t numberToPrint2[] = { numberB[digit8], numberB[digit7],
                                 numberB[digit6], numberB[digit5],
                                 numberB[digit4], numberB[digit3],
                                 numberB[digit2], numberB[digit1]
                               };  //8led sau

    sr1.setAll(numberToPrint1);
    sr2.setAll(numberToPrint2);
    time_display_led = millis();
  }
}

void blink() {
  for (int i = 0; i < 2; i++) {
    sr1.setAllLow();  // set all pins Low (off)
    sr2.setAllLow();  // set all pins Low (off)
    delay(500);
    sr1.setAllHigh();  // set all pins High (on)
    sr2.setAllHigh();  // set all pins High (on)
    delay(500);
  }
}

void read_btn() {
  if (digitalRead(btn1) == 0) {
    if (d < 50) {
      d++;
    }
    if (d == 10) {
      pip();
      run = 1;
    }
  } else {
    if (digitalRead(btn2) == 0) {
      if (d < 50) {
        d++;
      }
      if (d == 10) {
        pip();
        run = 0;
        t1 = 0;
        t2 = 0;
        blink();
      }
    } else {
      if (digitalRead(btc1) == 0) {
        if (d < 50) {
          d++;
        }
        if (d == 10) {
          pip();
          ndb1 = 1;
          time_ndb1 = millis();
        }
      } else {
        if (digitalRead(btc2) == 0) {
          if (d < 50) {
            d++;
          }
          if (d == 10) {
            pip();
            ndb2 = 1;
            time_ndb2 = millis();
          }
        } else {
          if (digitalRead(btc3) == 0) {
            if (d < 50) {
              d++;
            }
            if (d == 10) {
              pip();
              ndb3 = 1;
              time_ndb3 = millis();
            }
          } else {
            if (digitalRead(btc4) == 0) {
              if (d < 50) {
                d++;
              }
              if (d == 10) {
                pip();
                ndb4 = 1;
                time_ndb4 = millis();
              }
            } else {
              d = 0;
            }
          }
        }
      }
    }
  }
}

void rst_time_ndb() {
  if (millis() - time_ndb1 > 2000) {
    ndb1 = 0;
  }
  if (millis() - time_ndb2 > 2000) {
    ndb2 = 0;
  }
  if (millis() - time_ndb3 > 2000) {
    ndb3 = 0;
  }
  if (millis() - time_ndb4 > 2000) {
    ndb4 = 0;
  }
  //  Serial.print(ndb1);Serial.print("  ");
  //  Serial.print(ndb2);Serial.print("  ");
  //  Serial.print(ndb3);Serial.print("  ");
  //  Serial.print(ndb4);Serial.println("  ");
}

void runbt() {
  if (mode == 0) {  // r25 x20 v5
    //làn 1A
    if (t >= 0 && t < 25) {
      // đèn làn chính --- đèn đỏ cột 1,3
      if (ndb1 == 0) {
        digitalWrite(r1, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      } else {
        digitalWrite(r1, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      }

      if (ndb3 == 0) {
        digitalWrite(r3, 1);
        digitalWrite(y3, 0);
        digitalWrite(g3, 0);
      } else {
        digitalWrite(r3, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      }
      t1 = 25 - t;
      // đèn rẽ trái --- đèn xanh cột 2,4
      if (ndb2 == 1) {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      else {
        digitalWrite(t2x, 1);
        digitalWrite(t2d, 0);
      }
      if (ndb4 == 1) {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      else {
        digitalWrite(t4x, 1);
        digitalWrite(t4d, 0);
      }
      t4 = 25 - t;
    }
    if (t >= 25 && t < 45) {
      // đèn làn chính--- đèn xanh cột 1,3
      if (ndb1 == 0) {
        digitalWrite(r1, 0);
        digitalWrite(y1, 0);
        digitalWrite(g1, 1);
      } else {
        digitalWrite(r1, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      }
      if (ndb3 == 0) {
        digitalWrite(r3, 0);
        digitalWrite(y3, 0);
        digitalWrite(g3, 1);
      } else {
        digitalWrite(r3, 1);
        digitalWrite(y3, 0);
        digitalWrite(g3, 0);
      }
      t1 = 45 - t;
      // đèn rẽ trái --- đèn đỏ cột 2,4
      if (ndb2 == 1) {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      else {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      if (ndb4 == 1) {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      else {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      t4 = 45 - t;
    }
    if (t >= 45 && t < 50) {
      // đèn làn chính --- đèn vàng cột 1,3
      if (ndb1 == 0) {
        digitalWrite(r1, 0);
        digitalWrite(y1, 1);
        digitalWrite(g1, 0);
      } else {
        digitalWrite(r1, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      }

      if (ndb3 == 0) {
        digitalWrite(r3, 0);
        digitalWrite(y3, 1);
        digitalWrite(g3, 0);
      } else {
        digitalWrite(r3, 1);
        digitalWrite(y3, 0);
        digitalWrite(g3, 0);
      }
      t1 = 50 - t;
      // đèn rẽ trái --- đèn đỏ cột 2,4
      if (ndb2 == 1) {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      else {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      if (ndb4 == 1) {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      else {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      t4 = 0;
    }
    //làn 2A
    if (t >= 0 && t < 23) {
      // đèn làn chính --- đèn xanh cột 2,4
      if (ndb2 == 0) {
        digitalWrite(r2, 0);
        digitalWrite(y2, 0);
        digitalWrite(g2, 1);
      } else {
        digitalWrite(r2, 1);
        digitalWrite(y2, 0);
        digitalWrite(g2, 0);
      }

      if (ndb4 == 0) {
        digitalWrite(r4, 0);
        digitalWrite(y4, 0);
        digitalWrite(g4, 1);
      } else {
        digitalWrite(r4, 1);
        digitalWrite(y4, 0);
        digitalWrite(g4, 0);
      }
      t2 = 23 - t;
      // đèn rẽ trái --- đèn đỏ cột 1,3
      if (ndb1 == 1) {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      else {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      if (ndb3 == 1) {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      else {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      t3 = 23 - t;
    }
    if (t >= 23 && t < 25) {
      // đèn làn chính --- đèn vàng cột 2,4
      if (ndb2 == 0) {
        digitalWrite(r2, 0);
        digitalWrite(y2, 1);
        digitalWrite(g2, 0);
      } else {
        digitalWrite(r2, 1);
        digitalWrite(y2, 0);
        digitalWrite(g2, 0);
      }

      if (ndb4 == 0) {
        digitalWrite(r4, 0);
        digitalWrite(y4, 1);
        digitalWrite(g4, 0);
      } else {
        digitalWrite(r4, 1);
        digitalWrite(y4, 0);
        digitalWrite(g4, 0);
      }
      t2 = 25 - t;
      // đèn rẽ trái --- đèn đỏ cột 1,3
      if (ndb1 == 1) {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      else {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      if (ndb3 == 1) {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      else {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      t3 = 0;
    }
    if (t >= 25 && t < 50) {
      // đèn làn chính --- đèn đỏ cột 2,4
      if (ndb2 == 0) {
        digitalWrite(r2, 1);
        digitalWrite(y2, 0);
        digitalWrite(g2, 0);
      } else {
        digitalWrite(r2, 1);
        digitalWrite(y2, 0);
        digitalWrite(g2, 0);
      }

      if (ndb4 == 0) {
        digitalWrite(r4, 1);
        digitalWrite(y4, 0);
        digitalWrite(g4, 0);
      } else {
        digitalWrite(r4, 1);
        digitalWrite(y4, 0);
        digitalWrite(g4, 0);
      }
      t2 = 50 - t;
      // đèn rẽ trái --- đèn xanh cột 1,3
      if (ndb1 == 1) {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      else {
        digitalWrite(t1x, 1);
        digitalWrite(t1d, 0);
      }
      if (ndb3 == 1) {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      else {
        digitalWrite(t3x, 1);
        digitalWrite(t3d, 0);
      }
      t3 = 50 - t;
    }
  }
  else {
    // r25 x23 v2
    //làn 1B
    if (t >= 0 && t < 25) {
      // đèn làn chính --- đèn đỏ cột 1,3
      if (ndb1 == 0) {
        digitalWrite(r1, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      } else {
        digitalWrite(r1, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      }

      if (ndb3 == 0) {
        digitalWrite(r3, 1);
        digitalWrite(y3, 0);
        digitalWrite(g3, 0);
      } else {
        digitalWrite(r3, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      }
      t1 = 25 - t;
      // đèn rẽ trái --- đèn xanh cột 2,4
      if (ndb2 == 1) {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      else {
        digitalWrite(t2x, 1);
        digitalWrite(t2d, 0);
      }
      if (ndb4 == 1) {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      else {
        digitalWrite(t4x, 1);
        digitalWrite(t4d, 0);
      }
      t4 = 25 - t;
    }
    if (t >= 25 && t < 48) {
      // đèn làn chính--- đèn xanh cột 1,3
      if (ndb1 == 0) {
        digitalWrite(r1, 0);
        digitalWrite(y1, 0);
        digitalWrite(g1, 1);
      } else {
        digitalWrite(r1, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      }
      if (ndb3 == 0) {
        digitalWrite(r3, 0);
        digitalWrite(y3, 0);
        digitalWrite(g3, 1);
      } else {
        digitalWrite(r3, 1);
        digitalWrite(y3, 0);
        digitalWrite(g3, 0);
      }
      t1 = 45 - t;
      // đèn rẽ trái --- đèn đỏ cột 2,4
      if (ndb2 == 1) {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      else {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      if (ndb4 == 1) {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      else {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      t4 = 45 - t;
    }
    if (t >= 48 && t < 50) {
      // đèn làn chính --- đèn vàng cột 1,3
      if (ndb1 == 0) {
        digitalWrite(r1, 0);
        digitalWrite(y1, 1);
        digitalWrite(g1, 0);
      } else {
        digitalWrite(r1, 1);
        digitalWrite(y1, 0);
        digitalWrite(g1, 0);
      }

      if (ndb3 == 0) {
        digitalWrite(r3, 0);
        digitalWrite(y3, 1);
        digitalWrite(g3, 0);
      } else {
        digitalWrite(r3, 1);
        digitalWrite(y3, 0);
        digitalWrite(g3, 0);
      }
      t1 = 50 - t;
      // đèn rẽ trái --- đèn đỏ cột 2,4
      if (ndb2 == 1) {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      else {
        digitalWrite(t2x, 0);
        digitalWrite(t2d, 1);
      }
      if (ndb4 == 1) {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      else {
        digitalWrite(t4x, 0);
        digitalWrite(t4d, 1);
      }
      t4 = 0;
    }
    //làn 2B
    if (t >= 0 && t < 23) {
      // đèn làn chính --- đèn xanh cột 2,4
      if (ndb2 == 0) {
        digitalWrite(r2, 0);
        digitalWrite(y2, 0);
        digitalWrite(g2, 1);
      } else {
        digitalWrite(r2, 1);
        digitalWrite(y2, 0);
        digitalWrite(g2, 0);
      }

      if (ndb4 == 0) {
        digitalWrite(r4, 0);
        digitalWrite(y4, 0);
        digitalWrite(g4, 1);
      } else {
        digitalWrite(r4, 1);
        digitalWrite(y4, 0);
        digitalWrite(g4, 0);
      }
      t2 = 23 - t;
      // đèn rẽ trái --- đèn đỏ cột 1,3
      if (ndb1 == 1) {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      else {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      if (ndb3 == 1) {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      else {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      t3 = 23 - t;
    }
    if (t >= 23 && t < 25) {
      // đèn làn chính --- đèn vàng cột 2,4
      if (ndb2 == 0) {
        digitalWrite(r2, 0);
        digitalWrite(y2, 1);
        digitalWrite(g2, 0);
      } else {
        digitalWrite(r2, 1);
        digitalWrite(y2, 0);
        digitalWrite(g2, 0);
      }

      if (ndb4 == 0) {
        digitalWrite(r4, 0);
        digitalWrite(y4, 1);
        digitalWrite(g4, 0);
      } else {
        digitalWrite(r4, 1);
        digitalWrite(y4, 0);
        digitalWrite(g4, 0);
      }
      t2 = 25 - t;
      // đèn rẽ trái --- đèn đỏ cột 1,3
      if (ndb1 == 1) {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      else {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      if (ndb3 == 1) {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      else {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      t3 = 0;
    }
    if (t >= 25 && t < 50) {
      // đèn làn chính --- đèn đỏ cột 2,4
      if (ndb2 == 0) {
        digitalWrite(r2, 1);
        digitalWrite(y2, 0);
        digitalWrite(g2, 0);
      } else {
        digitalWrite(r2, 1);
        digitalWrite(y2, 0);
        digitalWrite(g2, 0);
      }

      if (ndb4 == 0) {
        digitalWrite(r4, 1);
        digitalWrite(y4, 0);
        digitalWrite(g4, 0);
      } else {
        digitalWrite(r4, 1);
        digitalWrite(y4, 0);
        digitalWrite(g4, 0);
      }
      t2 = 50 - t;
      // đèn rẽ trái --- đèn xanh cột 1,3
      if (ndb1 == 1) {
        digitalWrite(t1x, 0);
        digitalWrite(t1d, 1);
      }
      else {
        digitalWrite(t1x, 1);
        digitalWrite(t1d, 0);
      }
      if (ndb3 == 1) {
        digitalWrite(t3x, 0);
        digitalWrite(t3d, 1);
      }
      else {
        digitalWrite(t3x, 1);
        digitalWrite(t3d, 0);
      }
      t3 = 50 - t;
    }
  }
}

void nhay_vang() {
  if (t % 2 == 1) {
    digitalWrite(r1, 0);
    digitalWrite(y1, 1);
    digitalWrite(g1, 0);
    digitalWrite(r2, 0);
    digitalWrite(y2, 1);
    digitalWrite(g2, 0);
    digitalWrite(r3, 0);
    digitalWrite(y3, 1);
    digitalWrite(g3, 0);
    digitalWrite(r4, 0);
    digitalWrite(y4, 1);
    digitalWrite(g4, 0);
    digitalWrite(t1d, 0);
    digitalWrite(t1x, 0);
    digitalWrite(t2d, 0);
    digitalWrite(t2x, 0);
    digitalWrite(t3d, 0);
    digitalWrite(t3x, 0);
    digitalWrite(t4d, 0);
    digitalWrite(t4x, 0);
  } else {
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
  }
  t1 = t2 = 99;
  t3 = t4 = 99;
}

void runled() {
  if (run == 1) {
    if (millis() - time_led > 500) {
      t++;
      if (t > 50) {
        t = 0;
        String a = Serial.readString();
        delay(500);
        serial_control();
      }
      time_led = millis();
    }
    if (getTimeBuff[2] < 23 && getTimeBuff[2] >= 4) {
      rst_time_ndb();
      runbt();
    } else {
      if (getTimeBuff[2] >= 23 || getTimeBuff[2] < 4) {
        nhay_vang();
      }
    }
  } else {
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
