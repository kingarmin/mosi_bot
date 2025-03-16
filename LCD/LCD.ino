//We always have to include the library
#include "LedControlMS.h"

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
void face_talk() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(2, i, open_eye[i]);
    // lc.setRow(3, 7 - i, open_eye[i]);
    // lc.setRow(5, i, open_eye[i]);
    // lc.setRow(6, 7 - i, open_eye[i]);
  }
  // for (int i = 0; i < 8; i++) {
  //   lc.setRow(4, i, open_month[i]);
  //   lc.setRow(3, 7 - i, open_month[i]);
  // }
  // delay(100);
  // for (int i = 0; i < 8; i++) {
  //   lc.setRow(1, i, close_eye[i]);
  //   lc.setRow(3, 7 - i, close_eye[i]);
  //   lc.setRow(5, i, close_eye[i]);
  //   lc.setRow(6, 7 - i, close_eye[i]);
  // }
  // delay(1000);
  // for (int i = 0; i < 8; i++) {
  //   lc.setRow(1, i, open_eye[i]);
  //   lc.setRow(3, 7 - i, open_eye[i]);
  //   lc.setRow(5, i, open_eye[i]);
  //   lc.setRow(6, 7 - i, open_eye[i]);
  // }
  // for (int i = 0; i < 8; i++) {
  //   lc.setRow(4, i, close_mounth[i]);
  //   lc.setRow(3, 7 - i, close_mounth[i]);
  // }
  // delay(1000);
  // for (int i = 0; i < 8; i++) {
  //   lc.setRow(4, i, open_month[i]);
  //   lc.setRow(3, 7 - i, open_month[i]);
  // }
}
void free_face() {
  delay(500);
  for (int i = 0; i < 8; i++) {
    lc.setRow(4, i, close_mounth[i]);
    lc.setRow(3, 7 - i, close_mounth[i]);
  }
  for (int i = 0; i < 8; i++) {
    lc.setRow(1, i, close_eye[i]);
    lc.setRow(2, 7 - i, close_eye[i]);
    lc.setRow(5, i, close_eye[i]);
    lc.setRow(6, 7 - i, close_eye[i]);
  }
  delay(1000);
  for (int i = 0; i < 8; i++) {
    lc.setRow(1, i, open_eye[i]);
    lc.setRow(2, 7 - i, open_eye[i]);
    lc.setRow(5, i, open_eye[i]);
    lc.setRow(6, 7 - i, open_eye[i]);
  }
}
void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  // for (int i = 0; i < NBR_MTX; i++) {
  //   lc.shutdown(i, false);
  //   /* Set the brightness to a low value */
  //   lc.setIntensity(i, 1);
  //   /* and clear the display */
  //   lc.clearDisplay(i);
  // }
  // face_talk();
  // free_face();
  face_talk();
}

void loop() {
}
