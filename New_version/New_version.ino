//We always have to include the library
#include "LedControlMS.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_MP3_TX = 5;
static const uint8_t PIN_MP3_RX = 6;

SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini MP3player;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
#define NBR_MTX 8
LedControl lc = LedControl(2, 3, 4, NBR_MTX);
uint8_t open_eye[] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b111100,
  0b1000010,
  0b1011010
};
uint8_t open_month[] = {
  0b0,
  0b0,
  0b0,
  0b111100,
  0b1000010,
  0b1000010,
  0b1000010,
  0b1000010
};
uint8_t close_eye[] = {
  0b0,
  0b0,
  0b0,
  0b0,
  0b0,
  0b11000,
  0b11000,
  0b11000
};
uint8_t close_mounth[] = {
  0b0,
  0b0,
  0b0,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000
};
int avg = 0, mode = 0;
const int trig = 11;
const int echo = 12;
void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin(9600);
  Serial.print("ok");
  for (int i = 0; i < NBR_MTX; i++) {
    lc.shutdown(i, false);
    /* Set the brightness to a low value */
    lc.setIntensity(i, 1);
    /* and clear the display */
    lc.clearDisplay(i);
  }
  pinMode(trig, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echo, INPUT);   // Sets the echoPin as an Input
  for (int i = 0; i < 5; i++) {
    avg += SRF();
  }
  avg = avg / 5;
  face_talk();
  free_face();
  softwareSerial.begin(9600);
  if (MP3player.begin(softwareSerial)) {
    Serial.println("MP3 Player ready");
  } else {
    Serial.println("MP3 Player NOT READY");
  }
  MP3player.volume(13);
  delay(500);
  // MP3player.play(1);
  // delay(10000);
  // MP3player.stop();
}

void loop() {
  int dis = SRF();
  Serial.println(dis);
  if (dis < avg - 20 and mode == 0) {
    face_talk();
    MP3player.play(1);
    delay(5000);
    mode = 1;
  } else if (mode == 1) {
    mode = 0;
    free_face();
    MP3player.stop();
  }
}
