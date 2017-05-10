/*
  This code was for the demonstration at the Imperial Festival

  The code repeatedly runs through different vibration patterns

  Written by Julia Booth
  02/05/2017
 */

#define TOPLEFT 27
#define TOPMIDDLE1 33
#define TOPMIDDLE2 39
#define TOPRIGHT 45
#define CENTERLEFT 29
#define CENTERMIDDLE1 35
#define CENTERMIDDLE2 37
#define CENTERRIGHT 43
#define BOTTOMLEFT 49
#define BOTTOMMIDDLE1 31
#define BOTTOMMIDDLE2 41
#define BOTTOMRIGHT 47


void setup() {
  // initialize pins as outputs
  pinMode(TOPLEFT, OUTPUT);
  pinMode(TOPMIDDLE1, OUTPUT);
  pinMode(TOPMIDDLE2, OUTPUT);
  pinMode(TOPRIGHT, OUTPUT);
  pinMode(CENTERLEFT, OUTPUT);
  pinMode(CENTERMIDDLE1, OUTPUT);
  pinMode(CENTERMIDDLE2, OUTPUT);
  pinMode(CENTERRIGHT, OUTPUT);
  pinMode(BOTTOMLEFT, OUTPUT);
  pinMode(BOTTOMMIDDLE1, OUTPUT);
  pinMode(BOTTOMMIDDLE2, OUTPUT);
  pinMode(BOTTOMRIGHT, OUTPUT);
}

// loops over the different vibration patterns
void loop() {
  digitalWrite(27, HIGH);
  delay(2000);
  digitalWrite(27, LOW);
  digitalWrite(29, HIGH);
  delay(2000);
  digitalWrite(29, LOW);
  digitalWrite(31, HIGH);
  delay(2000);
  digitalWrite(31, LOW);
  digitalWrite(33, HIGH);
  delay(2000);
  digitalWrite(33, LOW);
  digitalWrite(35, HIGH);
  delay(2000);
  digitalWrite(35, LOW);
  digitalWrite(37, HIGH);
  delay(2000);
  digitalWrite(37, LOW);
  digitalWrite(39, HIGH);
  delay(2000);
  digitalWrite(39, LOW);
  digitalWrite(41, HIGH);
  delay(2000);
  digitalWrite(41, LOW);
  digitalWrite(43, HIGH);
  delay(2000);
  digitalWrite(43, LOW);
  digitalWrite(45, HIGH);
  delay(2000);
  digitalWrite(45, LOW);
  digitalWrite(47, HIGH);
  delay(2000);
  digitalWrite(47, LOW);
  digitalWrite(49, HIGH);
  delay(2000);
  digitalWrite(49, LOW);
  
  /*sweepRight();
  delay(2000);
  sweepLeft();
  delay(2000);
  sweepDown();
  delay(2000);
  sweepUp();*/
  delay(2000);
  randomFlash();
  delay(1000);
}

void sweepRight(){
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(CENTERLEFT, HIGH);
  digitalWrite(BOTTOMLEFT, HIGH);
  delay(500);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(CENTERLEFT, LOW);
  digitalWrite(BOTTOMLEFT, LOW);
  digitalWrite(TOPMIDDLE1, HIGH);
  digitalWrite(CENTERMIDDLE1, HIGH);
  digitalWrite(BOTTOMMIDDLE1, HIGH);
  delay(500);
  digitalWrite(TOPMIDDLE1, LOW);
  digitalWrite(CENTERMIDDLE1, LOW);
  digitalWrite(BOTTOMMIDDLE1, LOW);
  digitalWrite(TOPMIDDLE2, HIGH);
  digitalWrite(CENTERMIDDLE2, HIGH);
  digitalWrite(BOTTOMMIDDLE2, HIGH);
  delay(500);
  digitalWrite(TOPMIDDLE2, LOW);
  digitalWrite(CENTERMIDDLE2, LOW);
  digitalWrite(BOTTOMMIDDLE2, LOW);
  digitalWrite(TOPRIGHT, HIGH);
  digitalWrite(CENTERRIGHT, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(500);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(CENTERRIGHT, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
}

void sweepLeft(){
  digitalWrite(TOPRIGHT, HIGH);
  digitalWrite(CENTERRIGHT, HIGH);
  digitalWrite(BOTTOMRIGHT, HIGH);
  delay(500);
  digitalWrite(TOPRIGHT, LOW);
  digitalWrite(CENTERRIGHT, LOW);
  digitalWrite(BOTTOMRIGHT, LOW);
  digitalWrite(TOPMIDDLE2, HIGH);
  digitalWrite(CENTERMIDDLE2, HIGH);
  digitalWrite(BOTTOMMIDDLE2, HIGH);
  delay(500);
  digitalWrite(TOPMIDDLE2, LOW);
  digitalWrite(CENTERMIDDLE2, LOW);
  digitalWrite(BOTTOMMIDDLE2, LOW);
  digitalWrite(TOPMIDDLE1, HIGH);
  digitalWrite(CENTERMIDDLE1, HIGH);
  digitalWrite(BOTTOMMIDDLE1, HIGH);
  delay(500);
  digitalWrite(TOPMIDDLE1, LOW);
  digitalWrite(CENTERMIDDLE1, LOW);
  digitalWrite(BOTTOMMIDDLE1, LOW);
  digitalWrite(TOPLEFT, HIGH);
  digitalWrite(CENTERLEFT, HIGH);
  digitalWrite(BOTTOMLEFT, HIGH);
  delay(500);
  digitalWrite(TOPLEFT, LOW);
  digitalWrite(CENTERLEFT, LOW);
  digitalWrite(BOTTOMLEFT, LOW);
}

void sweepDown(){
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

void sweepUp(){
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

void sweepBottomRight(){
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

void sweepBottomLeft(){
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

void sweepTopRight(){
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

void sweepTopLeft(){
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

void tripleFlash(){
  for(int x=0; x<3; x++){
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
}

void randomFlash(){
  for(int x=0; x<2; x++){
    digitalWrite(TOPLEFT, HIGH);
    delay(1000);
    digitalWrite(TOPLEFT, LOW);
    digitalWrite(BOTTOMRIGHT, HIGH);
    delay(1000);
    digitalWrite(BOTTOMRIGHT, LOW);
    digitalWrite(CENTERMIDDLE1, HIGH);
    delay(1000);
    digitalWrite(CENTERMIDDLE1, LOW);
    digitalWrite(TOPRIGHT, HIGH);
    delay(1000);
    digitalWrite(TOPRIGHT, LOW);
    digitalWrite(BOTTOMMIDDLE2, HIGH);
    delay(1000);
    digitalWrite(BOTTOMMIDDLE2, LOW);
    digitalWrite(CENTERLEFT, HIGH);
    delay(1000);
    digitalWrite(CENTERLEFT, LOW);
    digitalWrite(TOPMIDDLE2, HIGH);
    delay(1000);
    digitalWrite(TOPMIDDLE2, LOW);
    digitalWrite(BOTTOMLEFT, HIGH);
    delay(1000);
    digitalWrite(BOTTOMLEFT, LOW);
    digitalWrite(CENTERMIDDLE2, HIGH);
    delay(1000);
    digitalWrite(CENTERMIDDLE2, LOW);
    digitalWrite(TOPMIDDLE1, HIGH);
    delay(1000);
    digitalWrite(TOPMIDDLE1, LOW);
    digitalWrite(BOTTOMMIDDLE1, HIGH);
    delay(1000);
    digitalWrite(BOTTOMMIDDLE1, LOW);
    digitalWrite(CENTERRIGHT, HIGH);
    delay(1000);
    digitalWrite(CENTERRIGHT, LOW);
  }
}
