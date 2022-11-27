// Adafruit IO Publish & Subscribe Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"


/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch

int count = 0;


#define IO_LOOP_DELAY 5000
unsigned long lastUpdate = 0;

// set up the 'counter' feed
AdafruitIO_Feed *counter_yixin = io.feed("yixin", "mony_nam"); //to receive from mony
AdafruitIO_Feed *counter_mony = io.feed("mony", "ychen78"); //to save for mony

int buttonState = 0;
int swingState = 0;
int prv_swingState = 0;
const int buttonPin = 12;
int ledPin = 13;


void setup() {

  // start the serial connection
  //pinMode(speaker,OUTPUT);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  // Define inputs and outputs:
  pinMode(ledPin, OUTPUT);
  // wait for serial monitor to open
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  //set up a message handler for the count feed.
  //the handleMessage function (defined below)
  //will be called whenever a message is
  //received from adafruit io.
  counter_yixin->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  counter_yixin->get();


}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  //button input
  //  buttonState = digitalRead(buttonPin);
  //  if (buttonState == HIGH){
  //    Serial.print("Hitting back -> ");
  //    Serial.println(buttonState);
  //    counter_mony->save(buttonState);
  //  //Serial.println(analogRead(KNOB));
  //    delay(3000);
  //    }

  //light inout/swing
  // reads the input on analog pin A3 (value between 0 and 1023)
  int analogValue = analogRead(A3);

  Serial.print("Analog reading: ");
  Serial.println(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 2150) {
    swingState = 1;
    Serial.print("hitting back");
    //Serial.println(swingState);
  } else {
    swingState = 0;
  }

    if (swingState == 1) {
      for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
        // sets the value (range from 0 to 255):
        analogWrite(ledPin, fadeValue);
        // wait for 30 milliseconds to see the dimming effect
        delay(100);
      }
    }
    else {
      analogWrite(ledPin, 0);
    }


  counter_mony->save(swingState);
  prv_swingState = swingState;
  delay(3000);





}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {


  // ball coming
  if (data->toPinLevel() == HIGH) {
    Serial.print("ball coming <- ");
    Serial.println(data->value());
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(100);
    }
    delay(5000);
  }
  else {
    analogWrite(ledPin, 0);
  }


}
