/*  
 *   Sixth Sense Project Wearable Device
 *  
 *  This code reads messages sent from the Adafruit UART app via Bluetooth Low Energy
 *  using callbacks to the event of a received message
 *  
 *  Written by Julia Booth (jb1613@imperial.ac.uk)
 * 
 *  NOTE: this code uses the Adafruit_BLE_UART library available from the Adafruit
 *  examples from the Adafruit nRF8001 library
 */

#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define RDY 2     // RDY pin on the Arduino board
#define RST 9     // RST pin on the Arduino board
#define REQ 10    // REQ pin on the Arduino board
#define TOPLEFT 48  // digital pin driving top left

Adafruit_BLE_UART uart = Adafruit_BLE_UART(REQ, RDY, RST);    // initialise the uart to be polled

// called when an ACI event occurs
void aciCallback(aci_evt_opcode_t event){
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
void rxCallback(uint8_t *buffer, uint8_t len){
  // print the motor name to the serial output
  if(len == 1){
    switch((char)buffer[0]){
      case '1':
        Serial.print("top left\n");
        digitalWrite(TOPLEFT, HIGH);
        delay(5000);
        digitalWrite(TOPLEFT, LOW);
        break;
      case '2':
        Serial.print("top centre 1\n");
        break;
      case '3':
        Serial.print("top centre 2\n");
        break;
      case '4':
        Serial.print("top right\n");
        break;
      case '5':
        Serial.print("middle left\n");
        break;
      case '6':
        Serial.print("middle centre 1\n");
        break;
      case '7':
        Serial.print("middle centre 2\n");
        break;
      case '8':
        Serial.print("middle right\n");
        break;
      case '9':
        Serial.print("bottom left\n");
        break;
      default:
        Serial.print("unrecognised character\n");
        break;
    }
  }
  else if(len == 2){
    if((char)buffer[0] == '1'){
      switch((char)buffer[1]){
        case '0':
          Serial.print("bottom centre 1\n");
          break;
        case '1':
          Serial.print("bottom centre 2\n");
          break;
        case '2':
          Serial.print("bottom right\n");
          break;
        default:
          Serial.print("unrecognised characters\n");
          break;
      }
    }
    else{
      Serial.print("unrecognised characters\n");
    }
  }
  else{
    Serial.print("unrecognised command: ");
    for(int i=0; i<len; i++){
      Serial.print((char)buffer[i]);
    }
    Serial.print("\n");
  }
}

// sets up the connection
void setup(void){ 
  pinMode(TOPLEFT, OUTPUT);
  
  Serial.begin(9600);
  while(!Serial);
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Callback Echo demo"));

  uart.setRXcallback(rxCallback);
  uart.setACIcallback(aciCallback);
  // uart.setDeviceName("NEWNAME"); /* 7 characters max! */
  uart.begin();
}

// polls for new events on the nRF8001
void loop(){
  uart.pollACI();
}
