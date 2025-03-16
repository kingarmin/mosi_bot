int SRF() {
  int distance = 0;
  long duration;
  for (int i = 0; i < 200; i++) {
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
  Serial.println(distance);
  return distance;
}