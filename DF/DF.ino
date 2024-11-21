#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_MP3_TX = 11; 
static const uint8_t PIN_MP3_RX = 12;

SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini MP3player;

void setup()

{
  Serial.begin(9600);
  softwareSerial.begin(9600);
  if (MP3player.begin(softwareSerial))
  {
  Serial.println("MP3 Player ready");
  }
  else
  {
  Serial.println("MP3 Player NOT READY");
  }
  MP3player.volume(30);
  delay(500);
  MP3player.play(1);
  delay(30000);
  MP3player.stop();
}

void loop()
{
 // MP3player.play(1);

}