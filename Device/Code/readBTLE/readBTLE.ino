/*
     Sixth Sense Project Wearable Device

    This code reads messages sent from the Adafruit UART app via Bluetooth Low Energy
    using callbacks to the event of a received message

    Written by Julia Booth (jb1613@imperial.ac.uk)

    NOTE: this code uses the Adafruit_BLE_UART library available from the Adafruit
    examples from the Adafruit nRF8001 library
*/

#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define RDY 2     // RDY pin on the Arduino board
#define RST 9     // RST pin on the Arduino board
#define REQ 10    // REQ pin on the Arduino board
#define TOPLEFT 3
#define TOPCENTRE 4
#define TOPRIGHT 5
#define MIDDLELEFT 6
#define MIDDLECENTRE 7
#define MIDDLERIGHT 8
#define BOTTOMLEFT A0
#define BOTTOMCENTRE A1
#define BOTTOMRIGHT A2
#define ENABLE A3

Adafruit_BLE_UART uart = Adafruit_BLE_UART(REQ, RDY, RST);    // initialise the uart to be polled
int period = 200;
int pwm = 255;
int type = 2;

// called when an ACI event occurs
void aciCallback(aci_evt_opcode_t event) {
  // print the type of event that has occurred to the serial output
  /*switch(event){
    case ACI_EVT_DEVICE_STARTED:
      Serial.println(F("Advertising started"));
      break;
    case ACI_EVT_CONNECTED:
      Serial.println(F("Connected!"));
      break;
    case ACI_EVT_DISCONNECTED:
      Serial.println(F("Disconnected or advertising timed out"));
      break;
    default:
      break;
    }*/
}

// called when data arrives on RX channel
void rxCallback(uint8_t *buffer, uint8_t len) {
  // print the motor name to the serial output

  if (len == 3) {
    if ((char)buffer[2] == '1') {
      // fast
      period = 200;
    }
    else if ((char)buffer[2] == '2') {
      // slow
      period = 500;
    }
    if (((int)buffer[1] < 4) && ((int)buffer[1] > 0)) {
      type = (int)buffer[1];
    }

    Serial.print(period);
    Serial.print("\n");
    Serial.print(type);
    Serial.print("\n");

    switch((char)buffer[0]){
      case '1':
        sweepUp();
        break;
      case '2':
        sweepRight();
        break;
      case '3':
        sweepDown();
        break;
      case '4':
        sweepLeft();
        break;
      default:
        Serial.print("unrecognised command\n");
      }
  }
  else {
    Serial.print("incorrect length\n");
  }

}

// sets up the connection
void setup(void) {
  pinMode(TOPLEFT, OUTPUT);
  pinMode(TOPRIGHT, OUTPUT);
  pinMode(TOPCENTRE, OUTPUT);
  pinMode(MIDDLELEFT, OUTPUT);
  pinMode(MIDDLERIGHT, OUTPUT);
  pinMode(MIDDLECENTRE, OUTPUT);
  pinMode(BOTTOMLEFT, OUTPUT);
  pinMode(BOTTOMRIGHT, OUTPUT);
  pinMode(BOTTOMCENTRE, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  digitalWrite(ENABLE, HIGH);

  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Callback Echo demo"));

  uart.setRXcallback(rxCallback);
  uart.setACIcallback(aciCallback);
  // uart.setDeviceName("NEWNAME"); /* 7 characters max! */
  uart.begin();
}

void sweepRight() {
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(MIDDLELEFT, HIGH);
  digitalWrite(BOTTOMLEFT, HIGH);
  delay(period);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(MIDDLELEFT, LOW);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(TOPCENTRE, HIGH);
  digitalWrite(MIDDLECENTRE, HIGH);
  digitalWrite(BOTTOMCENTRE, HIGH);
  delay(period);
  digitalWrite(TOPCENTRE, LOW);
  digitalWrite(MIDDLECENTRE, LOW);
  digitalWrite(BOTTOMCENTRE, LOW);
  digitalWrite(TOPRIGHT, HIGH);
  digitalWrite(MIDDLERIGHT, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(period);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(MIDDLERIGHT, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
}

void sweepLeft() {
  digitalWrite(TOPRIGHT, HIGH);
  digitalWrite(MIDDLERIGHT, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(period);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(MIDDLERIGHT, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
  digitalWrite(TOPCENTRE, HIGH);
  digitalWrite(MIDDLECENTRE, HIGH);
  digitalWrite(BOTTOMCENTRE, HIGH);
  delay(period);
  digitalWrite(TOPCENTRE, LOW);
  digitalWrite(MIDDLECENTRE, LOW);
  digitalWrite(BOTTOMCENTRE, LOW);
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(MIDDLELEFT, HIGH);
  digitalWrite(BOTTOMLEFT, HIGH);
  delay(period);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(MIDDLELEFT, LOW);
  digitalWrite(BOTTOMLEFT, LOW);
}

void sweepDown() {
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(TOPCENTRE, HIGH);
  digitalWrite(TOPRIGHT, HIGH);
  delay(period);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(TOPCENTRE, LOW);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(MIDDLELEFT, HIGH);
  digitalWrite(MIDDLECENTRE, HIGH);
  digitalWrite(MIDDLERIGHT, HIGH);
  delay(period);
  digitalWrite(MIDDLELEFT, LOW);
  digitalWrite(MIDDLECENTRE, LOW);
  digitalWrite(MIDDLERIGHT, LOW);
  digitalWrite(BOTTOMLEFT, HIGH);
  digitalWrite(BOTTOMCENTRE, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(period);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(BOTTOMCENTRE, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
}

void sweepUp() {
  digitalWrite(BOTTOMLEFT, HIGH);
  digitalWrite(BOTTOMCENTRE, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(period);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(BOTTOMCENTRE, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
  digitalWrite(MIDDLELEFT, HIGH);
  digitalWrite(MIDDLECENTRE, HIGH);
  digitalWrite(MIDDLERIGHT, HIGH);
  delay(period);
  digitalWrite(MIDDLELEFT, LOW);
  digitalWrite(MIDDLECENTRE, LOW);
  digitalWrite(MIDDLERIGHT, LOW);
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(TOPCENTRE, HIGH);
  digitalWrite(TOPRIGHT, HIGH);
  delay(period);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(TOPCENTRE, LOW);
  digitalWrite(TOPRIGHT, LOW);
}

/*void sweepDown() {
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(TOPMIDDLE1, HIGH);
  digitalWrite(TOPMIDDLE2, HIGH);
  digitalWrite(TOPRIGHT, HIGH);
  delay(500);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(TOPMIDDLE1, LOW);
  digitalWrite(TOPMIDDLE2, LOW);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(CENTERLEFT, HIGH);
  digitalWrite(CENTERMIDDLE1, HIGH);
  digitalWrite(CENTERMIDDLE2, HIGH);
  digitalWrite(CENTERRIGHT, HIGH);
  delay(500);
  digitalWrite(CENTERLEFT, LOW);
  digitalWrite(CENTERMIDDLE1, LOW);
  digitalWrite(CENTERMIDDLE2, LOW);
  digitalWrite(CENTERRIGHT, LOW);
  digitalWrite(BOTTOMLEFT, HIGH);
  digitalWrite(BOTTOMMIDDLE1, HIGH);
  digitalWrite(BOTTOMMIDDLE2, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(500);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(BOTTOMMIDDLE1, LOW);
  digitalWrite(BOTTOMMIDDLE2, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
}

void sweepUp() {
  digitalWrite(BOTTOMLEFT, HIGH);
  digitalWrite(BOTTOMMIDDLE1, HIGH);
  digitalWrite(BOTTOMMIDDLE2, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(500);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(BOTTOMMIDDLE1, LOW);
  digitalWrite(BOTTOMMIDDLE2, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
  digitalWrite(CENTERLEFT, HIGH);
  digitalWrite(CENTERMIDDLE1, HIGH);
  digitalWrite(CENTERMIDDLE2, HIGH);
  digitalWrite(CENTERRIGHT, HIGH);
  delay(500);
  digitalWrite(CENTERLEFT, LOW);
  digitalWrite(CENTERMIDDLE1, LOW);
  digitalWrite(CENTERMIDDLE2, LOW);
  digitalWrite(CENTERRIGHT, LOW);
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(TOPMIDDLE1, HIGH);
  digitalWrite(TOPMIDDLE2, HIGH);
  digitalWrite(TOPRIGHT, HIGH);
  delay(500);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(TOPMIDDLE1, LOW);
  digitalWrite(TOPMIDDLE2, LOW);
  digitalWrite(TOPRIGHT, LOW);
}

void sweepBottomRight() {
  digitalWrite(TOPLEFT, HIGH);
  delay(500);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(TOPMIDDLE1, HIGH);
  digitalWrite(CENTERLEFT, HIGH);
  delay(500);
  digitalWrite(TOPMIDDLE1, LOW);
  digitalWrite(CENTERLEFT, LOW);
  digitalWrite(TOPMIDDLE2, HIGH);
  digitalWrite(CENTERMIDDLE1, HIGH);
  digitalWrite(BOTTOMLEFT, HIGH);
  delay(500);
  digitalWrite(TOPMIDDLE2, LOW);
  digitalWrite(CENTERMIDDLE1, LOW);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(TOPRIGHT, HIGH);
  digitalWrite(CENTERMIDDLE2, HIGH);
  digitalWrite(BOTTOMMIDDLE1, HIGH);
  delay(500);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(CENTERMIDDLE2, LOW);
  digitalWrite(BOTTOMMIDDLE1, LOW);
  digitalWrite(CENTERRIGHT, HIGH);
  digitalWrite(BOTTOMMIDDLE2, HIGH);
  delay(500);
  digitalWrite(CENTERRIGHT, LOW);
  digitalWrite(BOTTOMMIDDLE2, LOW);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(500);
  digitalWrite(BOTTOMRIGHT, LOW);
}

void sweepBottomLeft() {
  digitalWrite(TOPRIGHT, HIGH);
  delay(500);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(TOPMIDDLE2, HIGH);
  digitalWrite(CENTERRIGHT, HIGH);
  delay(500);
  digitalWrite(TOPMIDDLE2, LOW);
  digitalWrite(CENTERRIGHT, LOW);
  digitalWrite(TOPMIDDLE1, HIGH);
  digitalWrite(CENTERMIDDLE2, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(500);
  digitalWrite(TOPMIDDLE1, LOW);
  digitalWrite(CENTERMIDDLE2, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(CENTERMIDDLE1, HIGH);
  digitalWrite(BOTTOMMIDDLE2, HIGH);
  delay(500);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(CENTERMIDDLE1, LOW);
  digitalWrite(BOTTOMMIDDLE2, LOW);
  digitalWrite(CENTERLEFT, HIGH);
  digitalWrite(BOTTOMMIDDLE1, HIGH);
  delay(500);
  digitalWrite(CENTERLEFT, LOW);
  digitalWrite(BOTTOMMIDDLE1, LOW);
  digitalWrite(BOTTOMLEFT, HIGH);
  delay(500);
  digitalWrite(BOTTOMLEFT, LOW);
}

void sweepTopRight() {
  digitalWrite(BOTTOMLEFT, HIGH);
  delay(500);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(BOTTOMMIDDLE1, HIGH);
  digitalWrite(CENTERLEFT, HIGH);
  delay(500);
  digitalWrite(BOTTOMMIDDLE1, LOW);
  digitalWrite(CENTERLEFT, LOW);
  digitalWrite(BOTTOMMIDDLE2, HIGH);
  digitalWrite(CENTERMIDDLE1, HIGH);
  digitalWrite(TOPLEFT, HIGH);
  delay(500);
  digitalWrite(BOTTOMMIDDLE2, LOW);
  digitalWrite(CENTERMIDDLE1, LOW);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(BOTTOMRIGHT, HIGH);
  digitalWrite(CENTERMIDDLE2, HIGH);
  digitalWrite(TOPMIDDLE1, HIGH);
  delay(500);
  digitalWrite(BOTTOMRIGHT, LOW);
  digitalWrite(CENTERMIDDLE2, LOW);
  digitalWrite(TOPMIDDLE1, LOW);
  digitalWrite(CENTERRIGHT, HIGH);
  digitalWrite(TOPMIDDLE2, HIGH);
  delay(500);
  digitalWrite(CENTERRIGHT, LOW);
  digitalWrite(TOPMIDDLE2, LOW);
  digitalWrite(TOPRIGHT, HIGH);
  delay(500);
  digitalWrite(TOPRIGHT, LOW);
}

void sweepTopRight() {
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(500);
  digitalWrite(BOTTOMRIGHT, LOW);
  digitalWrite(BOTTOMMIDDLE2, HIGH);
  digitalWrite(CENTERRIGHT, HIGH);
  delay(500);
  digitalWrite(BOTTOMMIDDLE2, LOW);
  digitalWrite(CENTERRIGHT, LOW);
  digitalWrite(BOTTOMMIDDLE1, HIGH);
  digitalWrite(CENTERMIDDLE2, HIGH);
  digitalWrite(TOPRIGHT, HIGH);
  delay(500);
  digitalWrite(BOTTOMMIDDLE1, LOW);
  digitalWrite(CENTERMIDDLE2, LOW);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(BOTTOMLEFT, HIGH);
  digitalWrite(CENTERMIDDLE1, HIGH);
  digitalWrite(TOPMIDDLE2, HIGH);
  delay(500);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(CENTERMIDDLE1, LOW);
  digitalWrite(TOPMIDDLE2, LOW);
  digitalWrite(CENTERLEFT, HIGH);
  digitalWrite(TOPMIDDLE1, HIGH);
  delay(500);
  digitalWrite(CENTERLEFT, LOW);
  digitalWrite(TOPMIDDLE1, LOW);
  digitalWrite(TOPLEFT, HIGH);
  delay(500);
  digitalWrite(TOPLEFT, LOW);
}

void doubleFlash() {
  for (int x = 0; x < 2; x++) {
    digitalWrite(TOPLEFT, HIGH);
    digitalWrite(TOPMIDDLE1, HIGH);
    digitalWrite(TOPMIDDLE2, HIGH);
    digitalWrite(TOPRIGHT, HIGH);
    digitalWrite(CENTERLEFT, HIGH);
    digitalWrite(CENTERRIGHT, HIGH);
    digitalWrite(BOTTOMLEFT, HIGH);
    digitalWrite(BOTTOMMIDDLE1, HIGH);
    digitalWrite(BOTTOMMIDDLE2, HIGH);
    digitalWrite(BOTTOMRIGHT, HIGH);
    delay(1000);
    digitalWrite(TOPLEFT, LOW);
    digitalWrite(TOPMIDDLE1, LOW);
    digitalWrite(TOPMIDDLE2, LOW);
    digitalWrite(TOPRIGHT, LOW);
    digitalWrite(CENTERLEFT, LOW);
    digitalWrite(CENTERRIGHT, LOW);
    digitalWrite(BOTTOMLEFT, LOW);
    digitalWrite(BOTTOMMIDDLE1, LOW);
    digitalWrite(BOTTOMMIDDLE2, LOW);
    digitalWrite(BOTTOMRIGHT, LOW);
    digitalWrite(CENTERMIDDLE1, HIGH);
    digitalWrite(CENTERMIDDLE2, HIGH);
    delay(1000);
    digitalWrite(CENTERMIDDLE1, LOW);
    digitalWrite(CENTERMIDDLE2, LOW);
  }
}*/

// polls for new events on the nRF8001
void loop() {
  uart.pollACI();
}
