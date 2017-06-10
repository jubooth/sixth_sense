/*
     Sixth Sense Project Wearable Device

    This code reads messages sent from the Adafruit UART app via Bluetooth 0 Energy
    using callbacks to the event of a received message

    Written by Julia Booth (jb1613@imperial.ac.uk)

    NOTE: this code uses the Adafruit_BLE_UART library available from the Adafruit
    examples from the Adafruit nRF8001 library
*/

#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define RDY 2     // RDY pin on the Arduino board
#define RST 40     // RST pin on the Arduino board
#define REQ 46    // REQ pin on the Arduino board
#define TOPLEFT 29
#define TOPCENTRELEFT 35
#define TOPCENTRERIGHT 41
#define TOPRIGHT 47
#define MIDDLELEFT 31
#define MIDDLECENTRELEFT 37
#define MIDDLECENTRERIGHT 39
#define MIDDLERIGHT 45
#define BOTTOMLEFT 27
#define BOTTOMCENTRELEFT 33
#define BOTTOMCENTRERIGHT 43
#define BOTTOMRIGHT 49

Adafruit_BLE_UART uart = Adafruit_BLE_UART(REQ, RDY, RST);    // initialise the uart to be polled
int period = 300;
int pwm = 150;

// called when an ACI event occurs
void aciCallback(aci_evt_opcode_t event) {
  // print the type of event that has occurred to the serial output
  switch(event){
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
    }
}

// called when data arrives on RX channel
void rxCallback(uint8_t *buffer, uint8_t len) {
  // print the motor name to the serial output

  if (len == 1) {
    switch((char)buffer[0]){
      case '1':
        up();
        break;
      case '2':
        upRight();
        break;
      case '3':
        right();
        break;
      case '4':
        downRight();
        break;
      case '5':
        down();
        break;
      case '6':
        downLeft();
        break;
      case '7':
        left();
        break;
      case '8':
        upLeft();
        break;
      case '0':
        warning();
        break;
      case 'a':
        analogWrite(TOPLEFT, pwm);
        delay(4*period);
        analogWrite(TOPLEFT, 0);
        break;
      case 'b':
        analogWrite(TOPCENTRELEFT, pwm);
        delay(4*period);
        analogWrite(TOPCENTRELEFT, 0);
        break;
      case 'c':
        analogWrite(TOPCENTRERIGHT, pwm);
        delay(4*period);
        analogWrite(TOPCENTRERIGHT, 0);
        break;
      case 'd':
        analogWrite(TOPRIGHT, pwm);
        delay(4*period);
        analogWrite(TOPRIGHT, 0);
        break;
      case 'e':
        analogWrite(MIDDLELEFT, pwm);
        delay(4*period);
        analogWrite(MIDDLELEFT, 0);
        break;
      case 'f':
        analogWrite(MIDDLECENTRELEFT, pwm);
        delay(4*period);
        analogWrite(MIDDLECENTRELEFT, 0);
        break;
      case 'g':
        analogWrite(MIDDLECENTRERIGHT, pwm);
        delay(4*period);
        analogWrite(MIDDLECENTRERIGHT, 0);
        break;
      case 'h':
        analogWrite(MIDDLERIGHT, pwm);
        delay(4*period);
        analogWrite(MIDDLERIGHT, 0);
        break;
      case 'i':
        analogWrite(BOTTOMLEFT, pwm);
        delay(4*period);
        analogWrite(BOTTOMLEFT, 0);
        break;
      case 'j':
        analogWrite(BOTTOMCENTRELEFT, pwm);
        delay(4*period);
        analogWrite(BOTTOMCENTRELEFT, 0);
        break;
      case 'k':
        analogWrite(BOTTOMCENTRERIGHT, pwm);
        delay(4*period);
        analogWrite(BOTTOMCENTRERIGHT, 0);
        break;
      case 'l':
        analogWrite(BOTTOMRIGHT, pwm);
        delay(4*period);
        analogWrite(BOTTOMRIGHT, 0);
        break;
      default:
        break;
    }
  }
  else if(len == 3){
    char zero = (char)buffer[0];
    char one = (char)buffer[1];
    char two = (char)buffer[2];
    String output = (String)zero + (String)one + (String)two;
    if(output.toInt() < 256){
      pwm = output.toInt();
    }
    Serial.print(pwm);
    Serial.print("\n");
  }
  else {
    Serial.print("incorrect length\n");
  }

}

// sets up the connection
void setup(void) {
  pinMode(TOPLEFT, OUTPUT);
  pinMode(TOPRIGHT, OUTPUT);
  pinMode(TOPCENTRELEFT, OUTPUT);
  pinMode(TOPCENTRERIGHT, OUTPUT);
  pinMode(MIDDLELEFT, OUTPUT);
  pinMode(MIDDLERIGHT, OUTPUT);
  pinMode(MIDDLECENTRELEFT, OUTPUT);
  pinMode(MIDDLECENTRERIGHT, OUTPUT);
  pinMode(BOTTOMLEFT, OUTPUT);
  pinMode(BOTTOMRIGHT, OUTPUT);
  pinMode(BOTTOMCENTRELEFT, OUTPUT);
  pinMode(BOTTOMCENTRERIGHT, OUTPUT);

  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("Adafruit Bluefruit 0 Energy nRF8001 Callback Echo demo"));

  uart.setRXcallback(rxCallback);
  uart.setACIcallback(aciCallback);
  uart.setDeviceName("6SENSE"); /* 7 characters max! */
  uart.begin();
}

void up() {
  Serial.print("up\n");
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(TOPLEFT, pwm);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(TOPRIGHT, 0);
}

void down() {
  Serial.print("down\n");
  analogWrite(TOPCENTRELEFT, pwm);
  analogWrite(TOPCENTRERIGHT, pwm);
  delay(period);
  analogWrite(TOPCENTRELEFT, 0);
  analogWrite(TOPCENTRERIGHT, 0);
  analogWrite(MIDDLECENTRELEFT, pwm);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRELEFT, 0);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(BOTTOMCENTRELEFT, pwm);
  analogWrite(BOTTOMCENTRERIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRELEFT, 0);
  analogWrite(BOTTOMCENTRERIGHT, 0);
}

void right() {
  Serial.print("right\n");
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLECENTRELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRELEFT, 0);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
}

void left() {
  Serial.print("left\n");
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(MIDDLECENTRELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRELEFT, 0);
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
}

void upRight() {
  Serial.print("upright\n");
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(MIDDLECENTRELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRELEFT, 0);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
}

void downRight() {
  Serial.print("downright\n");
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLECENTRELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRELEFT, 0);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
}

void upLeft() {
  Serial.print("upleft\n");
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(MIDDLECENTRELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRELEFT, 0);
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
}

void downLeft() {
  Serial.print("downleft\n");
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(MIDDLECENTRELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRELEFT, 0);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
}

void warning() {
  Serial.print("warning\n");
  analogWrite(TOPRIGHT, pwm);
  analogWrite(TOPLEFT, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(TOPLEFT, 0);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  analogWrite(MIDDLECENTRELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(MIDDLECENTRELEFT, 0);
  delay((1.5*period));
  analogWrite(TOPRIGHT, pwm);
  analogWrite(TOPLEFT, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(TOPLEFT, 0);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(MIDDLECENTRERIGHT, pwm);
  analogWrite(MIDDLECENTRELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRERIGHT, 0);
  analogWrite(MIDDLECENTRELEFT, 0);
}

// polls for new events on the nRF8001
void loop() {
  uart.pollACI();
}
