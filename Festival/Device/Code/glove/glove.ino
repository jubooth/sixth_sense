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
#define TOPLEFT 8  // digital pin driving top left
#define TOPCENTRE A0
#define TOPRIGHT 6
#define MIDDLELEFT A2
#define MIDDLECENTRE 7
#define MIDDLERIGHT 4
#define BOTTOMLEFT A1
#define BOTTOMCENTRE 5
#define BOTTOMRIGHT 3

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
  if(len == 4){
    char instruction = (char)buffer[0];
    char type = (char)buffer[1];
    char period = (char)buffer[2];
    char strength = (char)buffer[3];

    switch(instruction){
      case '1':
      switch(type){
        case '1':
        switch(period){
          case '1':
            switch(strength){
              case '1':
                Serial.print("sweep up full overlap fast strong/n");
                break;
              case '2':
                Serial.print("sweep up full overlap fast weak/n");
                break;
              default:
                Serial.print("unknown\n");
            }
            break;
          case '2':
            Serial.print("sweep up full overlap slow strong/n");
            break;
          default:
            Serial.print("unknown");
            break;
        }
        break;
      default:
        Serial.print("unknown");
        break;
      }
      break;
    default:
      Serial.print("unknown");
      break;
    }
    
    /*if(instruction == '1'){          // sweep up
      if(type == '1'){               // full overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep up full overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep up full overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep up full overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep up full overlap slow weak/n");
          }
        }
      }
      else if(type == '2'){          // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep up full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep up full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep up full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep up full slow weak/n");
          }
        }
      }
      else if(type == '3'){        // single overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep up single overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep up single overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep up single overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep up single overlap slow weak/n");
          }
        }
      }
      else if(type == '4'){        // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep up single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep up single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep up single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep up single slow weak/n");
          }
        }
      }
    }

    if(instruction == '2'){          // sweep right
      if(type == '1'){               // full overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep right full overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep right full overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep right full overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep right full overlap slow weak/n");
          }
        }
      }
      else if(type == '2'){          // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep right full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep right full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep right full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep right full slow weak/n");
          }
        }
      }
      else if(type == '3'){        // single overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep right single overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep right single overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep right single overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep right single overlap slow weak/n");
          }
        }
      }
      else if(type == '4'){        // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep right single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep right single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep right single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep right single slow weak/n");
          }
        }
      }
    }

    if(instruction == '3'){          // sweep down
      if(type == '1'){               // full overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep down full overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep down full overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep down full overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep down full overlap slow weak/n");
          }
        }
      }
      else if(type == '2'){          // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep down full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep down full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep down full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep down full slow weak/n");
          }
        }
      }
      else if(type == '3'){        // single overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep down single overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep down single overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep down single overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep down single overlap slow weak/n");
          }
        }
      }
      else if(type == '4'){        // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep down single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep down single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep down single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep down single slow weak/n");
          }
        }
      }
    }

    if(instruction == '4'){          // sweep left
      if(type == '1'){               // full overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep left full overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep left full overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep left full overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep left full overlap slow weak/n");
          }
        }
      }
      else if(type == '2'){          // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep left full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep left full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep left full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep left full slow weak/n");
          }
        }
      }
      else if(type == '3'){        // single overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep left single overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep left single overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep left single overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep left single overlap slow weak/n");
          }
        }
      }
      else if(type == '4'){        // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("sweep left single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("sweep left single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("sweep left single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("sweep left single slow weak/n");
          }
        }
      }
    }

    if(instruction == '5'){          // diagonal top right
      if(type == '1'){               // full overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal top right full overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal top right full overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal top right full overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal top right full overlap slow weak/n");
          }
        }
      }
      else if(type == '2'){          // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal top right full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal top right full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal top right full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal top right full slow weak/n");
          }
        }
      }
      else if(type == '3'){        // single overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal top right single overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal top right single overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal top right single overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal top right single overlap slow weak/n");
          }
        }
      }
      else if(type == '4'){        // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal top right single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal top right single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal top right single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal top right single slow weak/n");
          }
        }
      }
    }

    if(instruction == '6'){          // diagonal bottom right
      if(type == '1'){               // full overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal bottom right full overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal bottom right full overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal bottom right full overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal bottom right full overlap slow weak/n");
          }
        }
      }
      else if(type == '2'){          // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal bottom right full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal bottom right full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal bottom right full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal bottom right full slow weak/n");
          }
        }
      }
      else if(type == '3'){        // single overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal bottom right single overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal bottom right single overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal bottom right single overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal bottom right single overlap slow weak/n");
          }
        }
      }
      else if(type == '4'){        // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal bottom right single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal bottom right single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal bottom right single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal bottom right single slow weak/n");
          }
        }
      }
    }

    if(instruction == '7'){          // diagonal bottom left
      if(type == '1'){               // full overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal bottom left full overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal bottom left full overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal bottom left full overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal bottom left full overlap slow weak/n");
          }
        }
      }
      else if(type == '2'){          // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal bottom left full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal bottom left full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal bottom left full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal bottom left full slow weak/n");
          }
        }
      }
      else if(type == '3'){        // single overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal bottom left single overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal bottom left single overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal bottom left single overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal bottom left single overlap slow weak/n");
          }
        }
      }
      else if(type == '4'){        // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal bottom left single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal bottom left single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal bottom left single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal bottom left single slow weak/n");
          }
        }
      }
    }

    if(instruction == '8'){          // diagonal top left
      if(type == '1'){               // full overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal top left full overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal top left full overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal top left full overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal top left full overlap slow weak/n");
          }
        }
      }
      else if(type == '2'){          // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal top left full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal top left full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal top left full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal top left full slow weak/n");
          }
        }
      }
      else if(type == '3'){        // single overlap
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal top left single overlap fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal top left single overlap fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal top left single overlap slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal top left single overlap slow weak/n");
          }
        }
      }
      else if(type == '4'){        // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("diagonal top left single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("diagonal top left single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("diagonal top left single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("diagonal top left single slow weak/n");
          }
        }
      }
    }

    if(instruction == '9'){          // blink
      if(type == '1'){               // full
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("blink full fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("blink full fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("blink full slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("blink full slow weak/n");
          }
        }
      }
      else if(type == '2'){          // single
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("blink single fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("blink single fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("blink single slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("blink single slow weak/n");
          }
        }
      }
      else if(type == '3'){        // random square
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("random square fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("random square fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("random square slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("random square slow weak/n");
          }
        }
      }
      else if(type == '4'){        // random diagonal
        if(period == '1'){           // fast
          if(strength == '1'){       // strong
            Serial.print("random diagonal fast strong/n");
          }
          else if(strength == '2'){  // weak
            Serial.print("random diagonal fast weak/n");
          }
        }
        else if(period == '2'){     // slow
          if(strength == '1'){      // strong
            Serial.print("random diagonal slow strong/n");
          }
          else if(strength == '2'){ // weak
            Serial.print("random diagonal slow weak/n");
          }
        }
      }
    }
    else{
      Serial.print("unrecognised characters\n");
    }
  }
  else{
    Serial.print("unrecognised length\n");
  }*/
  }
  Serial.print("received\n");
}

// sets up the connection
void setup(void){ 
  pinMode(TOPLEFT, OUTPUT);
  pinMode(TOPCENTRE, OUTPUT);
  pinMode(TOPRIGHT, OUTPUT);
  pinMode(MIDDLELEFT, OUTPUT);
  pinMode(MIDDLECENTRE, OUTPUT);
  pinMode(MIDDLERIGHT, OUTPUT);
  pinMode(BOTTOMLEFT, OUTPUT);
  pinMode(BOTTOMCENTRE, OUTPUT);
  pinMode(BOTTOMRIGHT, OUTPUT);
  
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
