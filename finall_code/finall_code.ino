#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
//#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include "LedControl.h"
#define trig 11
#define echo 12
LedControl lc = LedControl(7, 9, 8, 4);
unsigned long current = 0 , old = 0 , old2 = 0 , duration = 0 , distance = 0 ;
//trig pin , echo pin
int last_srf=0;
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
  B00011000,+
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
};
void face_talk () {
  for ( int p = 0 ; p < 7 ; p++ ) {
    if ( p == 0 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 1 :
              lc.setRow(j, i, openeye[i]);
              break ;
            case 2 :
              lc.setRow(j, 7 - i, openeye[i]);
              break ;
          }
        }
      }
    }
    delay(50);
    if ( p == 1 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 0 :
              lc.setRow(j, i, openmouth[i]);
              break;
            case 3 :
              lc.setRow(j, 7 - i, openmouth[i]);
              break;
          }
        }
      }
    }

    delay(100);
    if ( p == 2 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 0  :
              lc.setRow(j, i, closemouth[i]);
              break ;
            case 3 :
              lc.setRow(j, 7 - i, closemouth[i]);
              break ;
          }
        }
      }
    }
    delay(200);
    if ( p == 3 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 1 :
              lc.setRow(j, i, closeeye[i]);
              break ;
            case 2 :
              lc.setRow(j, 7 - i, closeeye[i]);
              break ;

          }
        }
      }
    }
    delay(10);
    if ( p == 4 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 1 :
              lc.setRow(j, i, openeye[i]);
              break ;
            case 2 :
              lc.setRow(j, 7 - i, openeye[i]);
              break ;
          }
        }
      }
    }
    delay(50);
    if ( p == 5 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 0 :
              lc.setRow(j, i, openmouth[i]);
              break;
            case 3 :
              lc.setRow(j, 7 - i, openmouth[i]);
              break;
          }
        }
      }
    }

    delay(100);
    if ( p == 6 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 0  :
              lc.setRow(j, i, closemouth[i]);
              break ;
            case 3 :
              lc.setRow(j, 7 - i, closemouth[i]);
              break ;
          }
        }
      }
    }
  }
}
void face_free() {
  for ( int p = 0 ; p < 3 ; p++ ) {
    if ( p == 0 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 1 :
              lc.setRow(j, i, closeeye[i]);
              break ;
            case 2 :
              lc.setRow(j, 7 - i, closeeye[i]);
              break ;
          }
        }
      }
    }
    delay(10);
    if ( p == 1 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 0 :
              lc.setRow(j, i, mouth[i]);
              break;
            case 3 :
              lc.setRow(j, 7 - i, mouth[i]);
              break;
          }
        }
      }
    }
    delay(10);
    if ( p == 2 ) {
      for (int j = 0 ; j < 9 ; j++) {
        for (int i = 0 ; i < 9 ; i++) {
          switch (j) {
            case 1 :
              lc.setRow(j, i, openeye[i]);
              break ;
            case 2 :
              lc.setRow(j, 7 - i, openeye[i]);
              break ;
          }
        }
      }
    }
    delay(600);
  }
}
int srf(){
  digitalWrite(trig, LOW);// set trig to LOW
  delayMicroseconds(2);// wait 2 microseconds
  digitalWrite(trig, HIGH);// set trig to HIGH
  delayMicroseconds(10);// wait 10 microseconds
  digitalWrite(trig, LOW);// set trig to LOW
  duration = pulseIn(echo, HIGH);// use the function pulsein to detect the time of the echo when it is in a high state
  distance = duration * 0.0343 / 2;// divide the time by 2 then multiply it by 0.0343
  return distance;
}
void setup() {
  // put your setup code here, to run once:
  int devices = lc.getDeviceCount();
  for (int address = 0; address < devices; address++) {
    lc.shutdown(address, false);
    lc.setIntensity(address, 4);
    lc.clearDisplay(address);
  }
    Serial.begin(9600);
  face_free();
   pinMode(trig, OUTPUT);// initialize trig as an output
   pinMode(echo, INPUT);// initialize echo as an input

   for (int i=0 ; i<=20 ; i++){
      last_srf+=srf();
   }
   Serial.println(last_srf);
   last_srf=last_srf/21;
   Serial.print("last: ");
   Serial.print(last_srf);
   softwareSerial.begin(9600);
  if (player.begin(softwareSerial, PIN_MP3_TX, PIN_MP3_RX)) {
    Serial.println("OK");
    player.volume(70);
    //player.play(1);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int ultra=srf();
  Serial.println(ultra);
  if(ultra<last_srf-10){
    int time=millis();
    //delay(500);
    player.play(1);
    face_talk();
    while(millis()-time<3500);
    delay(200);
    //face_free();
  }
  else{
    face_free();
  }
}
