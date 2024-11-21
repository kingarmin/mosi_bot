/*    
   * Ultrasonic Sensor HC-SR05/4 and Arduino
    * by Hanie Kiani
*  https://electropeak.com/learn
    */

const int trig = 7;
const int echo = 6;


void setup() {

  Serial.begin(9600);  // Starts the serial communication
  pinMode(trig,OUTPUT);
}
void loop() {
  Serial.println(SRF());
}

int SRF() {
  int distance = 0;
  long duration;
  for (int i = 0; i < 10; i++) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
    distance += (duration * 0.034 / 2);
  }
  distance=distance/10;
  return distance;
}