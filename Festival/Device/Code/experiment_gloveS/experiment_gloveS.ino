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
#define RST 9     // RST pin on the Arduino board
#define REQ 10    // REQ pin on the Arduino board
#define TOPLEFT A0
#define TOPCENTRE 8
#define TOPRIGHT 5
#define MIDDLELEFT A2
#define MIDDLECENTRE 7
#define MIDDLERIGHT 4
#define BOTTOMLEFT A1
#define BOTTOMCENTRE 6
#define BOTTOMRIGHT 3
#define ENABLE A3

Adafruit_BLE_UART uart = Adafruit_BLE_UART(REQ, RDY, RST);    // initialise the uart to be polled
int period = 400;
int pwm = 150;
int type;

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
      period = 400;
    }

    if((char)buffer[1] == '1'){
      type = 1;
    }
    else if((char)buffer[1] == '2'){
      type = 2;
    }
    else if((char)buffer[1] == '3'){
      type = 3;
    }
    else if((char)buffer[1] == '4'){
      type = 4;
    }

    Serial.print(period);
    Serial.print("\n");
    Serial.print(type);
    Serial.print("\n");

    switch((char)buffer[0]){
      case '1':
        if(type == 1){
          Serial.print("21 detected\n");
          sweepUpFullOverlap();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          sweepUpFull();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
          sweepUpSingleOverlap();
        }
        else{
          Serial.print("24 detected\n");
          sweepUpSingle();
        }
        break;
      case '2':
        if(type == 1){
          Serial.print("21 detected\n");
          sweepRightFullOverlap();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          sweepRightFull();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
          sweepRightSingleOverlap();
        }
        else{
          Serial.print("24 detected\n");
          sweepRightSingle();
        }
        break;
      case '3':
        if(type == 1){
          Serial.print("21 detected\n");
          sweepDownFullOverlap();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          sweepDownFull();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
          sweepDownSingleOverlap();
        }
        else{
          Serial.print("24 detected\n");
          sweepDownSingle();
        }
        break;
      case '4':
        if(type == 1){
          Serial.print("21 detected\n");
          sweepLeftFullOverlap();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          sweepLeftFull();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
          sweepLeftSingleOverlap();
        }
        else{
          Serial.print("24 detected\n");
          sweepLeftSingle();
        }
        break;
      case '5':
        if(type == 1){
          Serial.print("21 detected\n");
          diagUpRightFullOverlap();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          diagUpRightFull();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
         diagUpRightSingleOverlap();
        }
        else{
          Serial.print("24 detected\n");
          diagUpRightSingle();
        }
        break;
      case '6':
        if(type == 1){
          Serial.print("21 detected\n");
          diagDownRightFullOverlap();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          diagDownRightFull();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
          diagDownRightSingleOverlap();
        }
        else{
          Serial.print("24 detected\n");
          diagDownRightSingle();
        }
        break;
      case '7':
        if(type == 1){
          Serial.print("21 detected\n");
          diagDownLeftFullOverlap();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          diagDownLeftFull();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
          diagDownLeftSingleOverlap();
        }
        else{
          Serial.print("24 detected\n");
          diagDownLeftSingle();
        }
        break;
      case '8':
        if(type == 1){
          Serial.print("21 detected\n");
          diagUpLeftFullOverlap();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          diagUpLeftFull();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
          diagUpLeftSingleOverlap();
        }
        else{
          Serial.print("24 detected\n");
          diagUpLeftSingle();
        }
        break;
      case '9':
        if(type == 1){
          Serial.print("21 detected\n");
          blinkFull();
        }
        else if(type == 2){
          Serial.print("22 detected\n");
          blinkSingle();
        }
        else if(type == 3){
          Serial.print("23 detected\n");
          randomSquare();
        }
        else{
          Serial.print("24 detected\n");
          randomDiag();
        }
        break;
      default:
        Serial.print("unrecognised command\n");
      }
  }
  else if(len == 1){
    if((char)buffer[0] == '0'){
      digitalWrite(A3, LOW);
    }
    else{
      digitalWrite(A3, HIGH);
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
  period = 400;
  pwm = 150;
  type = 2;

  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("Adafruit Bluefruit 0 Energy nRF8001 Callback Echo demo"));

  uart.setRXcallback(rxCallback);
  uart.setACIcallback(aciCallback);
  // uart.setDeviceName("NEWNAME"); /* 7 characters max! */
  uart.begin();
}

void sweepRightFull() {
  Serial.print("full\n");
  analogWrite(TOPLEFT, pwm);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(TOPRIGHT, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMRIGHT, 0);
}

void sweepRightFullOverlap() {
  Serial.print("full overlap\n");
  analogWrite(TOPLEFT, pwm);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(TOPRIGHT, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(BOTTOMLEFT, 0);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMCENTRE, 0);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMRIGHT, 0);
}

void sweepRightSingle() {
  Serial.print("single\n");
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
}

void sweepRightSingleOverlap() {
  Serial.print("single overlap\n");
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
}

void sweepLeftFull() {
  analogWrite(TOPRIGHT, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(TOPLEFT, pwm);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(BOTTOMLEFT, 0);
}

void sweepLeftFullOverlap() {
  analogWrite(TOPRIGHT, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(TOPLEFT, pwm);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMRIGHT, 0);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMCENTRE, 0);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(BOTTOMLEFT, 0);
}

void sweepLeftSingle() {
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
}

void sweepLeftSingleOverlap() {
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
}

void sweepDownFull() {
  analogWrite(TOPLEFT, pwm);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(TOPCENTRE, 0);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(BOTTOMRIGHT, 0);
}

void sweepDownFullOverlap() {
  analogWrite(TOPLEFT, pwm);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(TOPCENTRE, 0);
  analogWrite(TOPRIGHT, 0);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(BOTTOMRIGHT, 0);
}

void sweepDownSingle() {
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
}

void sweepDownSingleOverlap() {
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
}

void sweepUpFull() {
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(TOPLEFT, pwm);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(TOPCENTRE, 0);
  analogWrite(TOPRIGHT, 0);
}

void sweepUpFullOverlap() {
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, pwm);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(BOTTOMRIGHT, 0);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(TOPCENTRE, 0);
  analogWrite(TOPRIGHT, 0);
}

void sweepUpSingle() {
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(TOPCENTRE, 0);
}

void sweepUpSingleOverlap() {
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(TOPCENTRE, 0);
}

void diagUpRightFull(){
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(TOPLEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
}

void diagUpRightFullOverlap(){
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(TOPLEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMRIGHT, 0);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  delay(period);
  analogWrite(TOPRIGHT, 0);
}

void diagUpRightSingle(){
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
}

void diagUpRightSingleOverlap(){
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(TOPRIGHT, 0);
}

void diagDownRightFull(){
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(TOPCENTRE, 0);
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(TOPRIGHT, 0);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
}

void diagDownRightFullOverlap(){
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(TOPCENTRE, 0);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(TOPRIGHT, 0);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
}

void diagDownRightSingle(){
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
}

void diagDownRightSingleOverlap(){
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
}

void diagDownLeftFull(){
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(TOPCENTRE, 0);
  analogWrite(BOTTOMRIGHT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(TOPLEFT, 0);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
}

void diagDownLeftFullOverlap(){
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(TOPCENTRE, 0);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(TOPLEFT, 0);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(MIDDLELEFT, 0);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
}

void diagDownLeftSingle(){
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
}

void diagDownLeftSingleOverlap(){
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(BOTTOMLEFT, 0);
}

void diagUpLeftFull(){
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(TOPRIGHT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
}

void diagUpLeftFullOverlap(){
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(TOPRIGHT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  delay(period);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(BOTTOMLEFT, 0);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLELEFT, 0);
  delay(period);
  analogWrite(TOPLEFT, 0);
}

void diagUpLeftSingle(){
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
}

void diagUpLeftSingleOverlap(){
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(TOPLEFT, 0);
}

void blinkFull(){
  analogWrite(TOPLEFT, pwm);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(TOPRIGHT, pwm);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(TOPCENTRE, 0);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(BOTTOMRIGHT, 0);
  delay(period);
  analogWrite(TOPLEFT, pwm);
  analogWrite(TOPCENTRE, pwm);
  analogWrite(TOPRIGHT, pwm);
  analogWrite(MIDDLELEFT, pwm);
  analogWrite(MIDDLECENTRE, pwm);
  analogWrite(MIDDLERIGHT, pwm);
  analogWrite(BOTTOMLEFT, pwm);
  analogWrite(BOTTOMCENTRE, pwm);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(TOPCENTRE, 0);
  analogWrite(TOPRIGHT, 0);
  analogWrite(MIDDLELEFT, 0);
  analogWrite(MIDDLECENTRE, 0);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMLEFT, 0);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(BOTTOMRIGHT, 0);
}

void blinkSingle(){
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
  delay(period);
  analogWrite(MIDDLECENTRE, pwm);
  delay(period);
  analogWrite(MIDDLECENTRE, 0);
}

void randomDiag(){
  analogWrite(TOPCENTRE, pwm);
  delay(period);
  analogWrite(TOPCENTRE, 0);
  analogWrite(MIDDLERIGHT, pwm);
  delay(period);
  analogWrite(MIDDLERIGHT, 0);
  analogWrite(BOTTOMCENTRE, pwm);
  delay(period);
  analogWrite(BOTTOMCENTRE, 0);
  analogWrite(MIDDLELEFT, pwm);
  delay(period);
  analogWrite(MIDDLELEFT, 0);
}

void randomSquare(){
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
  analogWrite(TOPRIGHT, pwm);
  delay(period);
  analogWrite(TOPRIGHT, 0);
  analogWrite(BOTTOMRIGHT, pwm);
  delay(period);
  analogWrite(BOTTOMRIGHT, 0);
  analogWrite(TOPLEFT, pwm);
  delay(period);
  analogWrite(TOPLEFT, 0);
}

// polls for new events on the nRF8001
void loop() {
  uart.pollACI();
}
