#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
//#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include "LedControl.h"
#define trig 11
#define echo 12
#define reciver 7
LedControl lc = LedControl(2, 4, 3, 4);
unsigned long current = 0, old = 0, old2 = 0, duration = 0, distance = 0;
//trig pin , echo pin
int last_srf = 0;
static const uint8_t PIN_MP3_TX = 5;
static const uint8_t PIN_MP3_RX = 6;
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;
//-------------------------------------------------------------------- bytes
byte openeye[] = {
  B00000000,
  B01111110,
  B10000001,
  B10011001,
  B10011001,
  B10000001,
  B01111110,
  B00000000
};
byte closeeye[] = {
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00000000,
  B00000000
};
byte openmouth[] = {
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B00111100,
  B00000000,
  B00000000,
  B00000000
};
byte closemouth[] = {
  B00100100,
  B00100100,
  B00100100,
  B00100100,
  B00011100,
  B00000000,
  B00000000,
  B00000000
};
byte mouth[] = {
  B00011000,
  B00011000,
  B00011000, +B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
};
void face_talk() {
  for (int p = 0; p < 7; p++) {
    if (p == 0) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
            // case 1:
            //   lc.setRow(j, i, openeye[i]);
            //   break;
            case 2:
              lc.setRow(j, 7 - i, openeye[i]);
              break;
          }
        }
      }
    }
    delay(50);
    if (p == 1) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
            case 0:
              lc.setRow(j, 7 - i, openmouth[i]);
              break;
              // case 3:
              //   lc.setRow(j, 7 - i, openmouth[i]);
              //   break;
          }
        }
      }
    }

    delay(100);
    if (p == 2) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
            case 0:
              lc.setRow(j, 7 - i, closemouth[i]);
              break;
              // case 3:
              //   lc.setRow(j, 7 - i, closemouth[i]);
              //   break;
          }
        }
      }
    }
    delay(200);
    if (p == 3) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
            // case 1:
            //   lc.setRow(j, i, closeeye[i]);
            //   break;
            case 2:
              lc.setRow(j, 7 - i, closeeye[i]);
              break;
          }
        }
      }
    }
    delay(10);
    if (p == 4) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
            // case 1:
            //   lc.setRow(j, i, openeye[i]);
            //   break;
            case 2:
              lc.setRow(j, 7 - i, openeye[i]);
              break;
          }
        }
      }
    }
    delay(50);
    if (p == 5) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
            case 0:
              lc.setRow(j, 7 - i, openmouth[i]);
              break;
              // case 3:
              //   lc.setRow(j, 7 - i, openmouth[i]);
              //   break;
          }
        }
      }
    }
  }
}
void face_free() {
  for (int p = 0; p < 3; p++) {
    if (p == 0) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
            // case 1:
            //   lc.setRow(j, i, closeeye[i]);
            //   break;
            case 2:
              lc.setRow(j, 7 - i, closeeye[i]);
              break;
          }
        }
      }
    }
    delay(10);
    if (p == 1) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
            case 0:
              lc.setRow(j, 7 - i, mouth[i]);
              break;
              // case 3:
              //   lc.setRow(j, 7 - i, mouth[i]);
              //   break;
          }
        }
      }
    }
    delay(10);
    if (p == 2) {
      for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
          switch (j) {
              //  case 1:
              //    lc.setRow(j, i, openeye[i]);
              //    break;
            case 2:
              lc.setRow(j, 7 - i, openeye[i]);
              break;
          }
        }
      }
    }
    delay(600);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(reciver, INPUT);
  int devices = lc.getDeviceCount();
  for (int address = 0; address < devices; address++) {
    lc.shutdown(address, false);
    lc.setIntensity(address, 4);
    lc.clearDisplay(address);
  }
  Serial.begin(9600);
  face_free();
  face_talk();
  delay(5000);
}
bool MODE = 0;
void loop() {
  // put your main code here, to run repeatedly:
  int reciver_val = digitalRead(reciver);
  Serial.println(reciver_val);
  if (reciver_val == 1 and MODE == 1) {
    int time = millis();
    //delay(500);
    face_talk();
    while (millis() - time < 20500)
      ;
    MODE = 0;
    //face_free();
  } else if (MODE == 0) {
    face_free();
    MODE = 1;
  }
}
