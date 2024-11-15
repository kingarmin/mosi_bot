/*    
   * Ultrasonic Sensor HC-SR05/4 and Arduino
    * by Hanie Kiani
*  https://electropeak.com/learn
    */
long duration;
int distance;

const int trig = 7;
const int echo = 6;


void setup() {

  Serial.begin(9600);  // Starts the serial communication
}
void loop() {
  distance = calculateDistance();
  Serial.println(distance);
}

