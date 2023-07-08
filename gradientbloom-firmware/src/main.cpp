/*
GradientBloom Firmware
Stephen Hawes
GNU GPL v3
2022
*/

#include "define.h"
#include <Arduino.h>

int mode = 1;
int modeCount = 2;

int rPotVal = 0;
int gPotVal = 0;
int bPotVal = 0;

inline void handleModeChange();
inline void handleLightingExecution();
void killAllLights();
void updatePots();

void led(int, int, int, int);

// Mode cycle execution
void spectrabloomCycle();
void lampCycle();

void setup() {
  // setting up pin modes
  pinMode(LED0_R, OUTPUT);
  pinMode(LED0_G, OUTPUT);
  pinMode(LED0_B, OUTPUT);

  pinMode(LED1_R, OUTPUT);
  pinMode(LED1_G, OUTPUT);
  pinMode(LED1_B, OUTPUT);

  pinMode(LED2_R, OUTPUT);
  pinMode(LED2_G, OUTPUT);
  pinMode(LED2_B, OUTPUT);

  pinMode(MODE, INPUT);
  pinMode(LED, INPUT);

}

void loop() {
  handleModeChange();
  handleLightingExecution();
}

// MODE 1 - SPECTRABLOOM
void spectrabloomCycle(){
  updatePots();

  led(0, rPotVal, 0, 0);
  led(1, 0, gPotVal, 0);
  led(2, 0, 0, bPotVal);

}

// MODE 2 - LAMP
void lampCycle(){
  // update values from pots
  updatePots();

  led(0, rPotVal, gPotVal, bPotVal);
  led(1, rPotVal, gPotVal, bPotVal);
  led(2, rPotVal, gPotVal, bPotVal);
}

void handleLightingExecution(){
  switch(mode) {
    case 1:
      spectrabloomCycle();
      break;
    case 2:
      lampCycle();
      break;
    default:
      // something weird is happening, reset mode to 1 to get to known state
      mode = 1;
      break;
  }
}

// run every loop. handles checking mode button and changing mode flag
void handleModeChange(){
  // if mode button pressed
  if(digitalRead(MODE)){
    // immediately kill all lights 
    killAllLights();
    // wait for button to come up
    while(digitalRead(MODE)){
      // do nothing while waiting to debounce
    }
    // small delay for debounce
    delay(10);
    // increment mode
    if(mode >= modeCount){
      mode = 1;
    }
    else{
      mode++;
    }
    // blink led the mode number
    for(int i = 0; i < mode; i++){
      digitalWrite(LED, HIGH);
      delay(250);
      digitalWrite(LED, LOW);
      delay(250);
    }
  }
}

void killAllLights(){
  digitalWrite(LED0_R, LOW);
  digitalWrite(LED0_G, LOW);
  digitalWrite(LED0_B, LOW);
  digitalWrite(LED1_R, LOW);
  digitalWrite(LED1_G, LOW);
  digitalWrite(LED1_B, LOW);
  digitalWrite(LED2_R, LOW);
  digitalWrite(LED2_G, LOW);
  digitalWrite(LED2_B, LOW);
}

void led(int index, int red, int green, int blue){
  if(index == 0){
    analogWrite(LED0_R, red);
    analogWrite(LED0_G, green);
    analogWrite(LED0_B, blue);
  }
  else if(index == 1){
    analogWrite(LED1_R, red);
    analogWrite(LED1_G, green);
    analogWrite(LED1_B, blue);
  }
  else if(index == 2){
    analogWrite(LED2_R, red);
    analogWrite(LED2_G, green);
    analogWrite(LED2_B, blue);
  }
}

void updatePots(){
  rPotVal = analogRead(R_POT);
  gPotVal = analogRead(G_POT);
  bPotVal = analogRead(B_POT);
}