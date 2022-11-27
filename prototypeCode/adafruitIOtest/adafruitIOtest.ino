#include "config.h"


#define KNOB A2
//int knob = A2;

AdafruitIO_Feed *potFeed = io.feed("potentiometer0");


void setup() {
  // put your setup code here, to run once:
  pinMode(KNOB,INPUT);
  Serial.begin(9600);

    // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();

  float val = analogRead(KNOB);
  Serial.print("saving:");
  Serial.print(val);
  potFeed->save(val);
  Serial.println(analogRead(KNOB));
  delay(3000);
}
