#include "SoftwareSerial.h"
#include <king_armin_ultra.h>
#include "DFRobotDFPlayerMini.h"
//#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include "LedControl.h"
//---------------------------------------------------------------------motor
#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 10
//-------------------------------------------------------------------- SRF-05
#define trig 11
#define echo 12

//-------------------------------------------------------------------- DF player
static const uint8_t PIN_MP3_TX = 4;
static const uint8_t PIN_MP3_RX = 5;
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;
//-------------------------------------------------------------------- matrix
LedControl lc = LedControl(7, 9, 8, 4);
//-------------------------------------------------------------------- servo
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  100
#define SERVOMAX  600
#define hand_angle 70   // maximum angle of hands
#define arm_angle 40   // maximum angle of arms
#define slow 5         //delay betwen servo motion
#define RH 3            // Right Hand
#define LH 0            // Left Hand
#define RA 2            // Right Arm
#define LA 1            // Left Arm
#define SPACE 270
#define SPACE_2 300
#define SPACE_3 300
//-------------------------------------------------------------------- variable
unsigned long current = 0 , old = 0 , old2 = 0 , duration = 0 , distance = 0 ;
//trig pin , echo pin
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
//---------------------------------------------------------------------- setup
void setup() {
  //------------------------------------------------------------------ LED.martix
  int devices = lc.getDeviceCount();
  for (int address = 0; address < devices; address++) {
    lc.shutdown(address, false);
    lc.setIntensity(address, 4);
    lc.clearDisplay(address);
  }
  //------------------------------------------------------------------ DF player
  Serial.begin(9600);
  softwareSerial.begin(9600);
  if (player.begin(softwareSerial, PIN_MP3_TX, PIN_MP3_RX)) {
    Serial.println("OK");
    player.volume(30);
    player.play(1);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
  //------------------------------------------------------------------ servo
  //pwm.begin();
  //pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  yield();
  //------------------------------------------------------------------ srf

  \
  //------------------------------------------------------------------ motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  motor(220, 170);
  motor(0, 0);
  face_free();
}
//---------------------------------------------------------------------- loop
int state = 1 ;
int number = 0 ;
void loop() {
  Serial.println(srf());
  if(srf()<10){
    player.play(1);
    act();
  }
  else{
    face_free();
  }
  

}
//---------------------------------------------------------------------- actions
void arm(String side , String mode) {
  if (side == "left") {
    if (mode == "up") {
      for (int i = SERVOMAX ; i >= SERVOMIN + SPACE_3 ; i--) {
        //pwm.setPWM(LA, 0, i);
        delay(slow);
      }
    } else {
      for (int i = SERVOMIN + SPACE_3 ; i <= SERVOMAX; i++) {
        //pwm.setPWM(LA, 0, i);
        delay(slow);
      }
    }
  } else if (side == "right") {
    if (mode == "up") {
      for (int i = SERVOMIN ; i <= SERVOMAX - SPACE_3 ; i++) {
        //pwm.setPWM(RA, 0, i);
        delay(slow);
      }
    } else {
      for (int i = SERVOMAX - SPACE_3 ; i >= SERVOMIN; i--) {
        //pwm.setPWM(RA, 0, i);
        delay(slow);
      }
    }
  } else if (side == "all") {
    if (mode == "up") {
      for (int i = SERVOMAX , j = SERVOMIN + SPACE_3; i >= SERVOMIN + SPACE_3 ; i-- , j++) {
        //pwm.setPWM(LA, 0, i);
        //pwm.setPWM(RA, 0, j);
        delay(slow);
      }
    } else {
      for (int i = SERVOMIN + SPACE_3 , j = SERVOMAX; i <= SERVOMAX; i++ , j--) {
        //pwm.setPWM(LA, 0, i);
        //pwm.setPWM(RA, 0, j);
        delay(slow);
      }
    }
  }
}
void hand(String side , String mode) {
  if (side == "left") {
    if (mode == "up") {
      for (int i = SERVOMAX - SPACE ; i >=  SERVOMIN ; i--) {
        //pwm.setPWM(LH, 0, i);
        delay(slow + 5);
      }
    } else {
      for (int i = SERVOMIN ; i <= SERVOMAX - SPACE ; i++) {
        //pwm.setPWM(LH, 0, i);
        delay(slow + 5);
      }
    }
  } else if (side == "right") {
    if (mode == "up") {
      for (int i = SERVOMIN ; i <=  SERVOMAX - SPACE ; i++) {
        //pwm.setPWM(RH, 0, i);
        delay(slow + 5);
      }
    } else {
      for (int i = SERVOMAX - SPACE ; i >= SERVOMIN ; i--) {
        //pwm.setPWM(RH, 0, i);
        delay(slow + 5);
      }
    }
  } else if (side == "all") {
    if (mode == "up") {
      for (int i = SERVOMIN , j = SERVOMAX - SPACE; i <=  SERVOMAX - SPACE ; i++ , j--) {
        //pwm.setPWM(LH, 0, j);
        //pwm.setPWM(RH, 0, i);
        delay(slow);
      }
    } else {
      for (int i = SERVOMAX - SPACE , j = SERVOMIN ; i >= SERVOMIN ; i-- , j++) {
        //pwm.setPWM(LH, 0, j);
        //pwm.setPWM(RH, 0, i);
        delay(slow);

      }
    }
  }
}
//---------------------------------------------------------------------- srf
//---------------------------------------------------------------------- motor
void motor (int right , int left) {
  if (right >= 0) {
    analogWrite(IN1, right);
    analogWrite(IN2, LOW );
  }
  else {
    right = right * -1;
    analogWrite(IN1, LOW);
    analogWrite(IN2, right);
  }

  if (left >= 0) {
    analogWrite(IN3, left);
    analogWrite(IN4, LOW);
  }
  else {
    left = left * -1;
    analogWrite(IN3, LOW);
    analogWrite(IN4, left);
  }
}
//---------------------------------------------------------------------- face
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
void act () {

  face_talk();

  arm("left", "down");
  arm("right", "up");
  delay(5);
  arm("right", "down");

  face_talk();

  delay(5);
  arm("right", "up");
  delay(5);
  arm("right", "down");
  arm("left", "up");

  face_talk();

  delay(5);
  arm("left", "down");
  delay(5);
  arm("left", "up");

  face_talk();

  delay(5);
  arm("left", "down");
  delay(5);
  arm("left", "up");
  arm("right", "up");

  face_talk();

  delay(5);
  arm("left", "down");
  arm("right", "down");
  delay(5);
  arm("left", "up");
  arm("right", "up");

  face_talk();

  delay(5);
  arm("left", "down");
  arm("right", "down");
  delay(5);
}
int srf(){
  king_ultra x(echo,trig);
  x.update_ultra_value();
  return x.out_cm;
}