/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-light-sensor
 */

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // reads the input on analog pin A3 (value between 0 and 1023)
  int analogValue = analogRead(A3);

  Serial.print("Analog reading: ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue <500) {
    Serial.println(" dark");
  } else if (analogValue < 2000) {
    Serial.println(" - swing2");
  } else if (analogValue < 2500) {
    Serial.println(" - Light");
  } else if (analogValue < 4000) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
}
