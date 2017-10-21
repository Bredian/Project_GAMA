/*
  keyboard

 Plays a pitch that changes based on a changing analog input

 circuit:
 * 3 force-sensing resistors from +5V to analog in 0 through 5
 * 3 10K resistors from analog in 0 through 5 to ground
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 9 Apr 2012
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone3

 */

#include "pitches.h"
#include <PS2Keyboard.h>

const int DataPin = 4;
const int IRQpin =  3;

PS2Keyboard keyboard;

#define KEYS 29

// notes to play, corresponding to the 3 sensors:
int notes[2][KEYS] = {
  {'q','2','w','3','e','r','5','t','6','y','7','u','i','9','o','0','p','z','s','x','d','c','f','v','b','h','n','j','m'},
  {NOTE_C3,NOTE_CS3,NOTE_D3,NOTE_DS3,NOTE_E3,NOTE_F3,NOTE_FS3,NOTE_G3,NOTE_GS3,NOTE_A3,NOTE_AS3,NOTE_B3,NOTE_C4,NOTE_CS4,NOTE_D4,NOTE_DS4,NOTE_E4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_A4,NOTE_AS4,NOTE_B4,NOTE_C5,NOTE_CS5,NOTE_D5,NOTE_DS5,NOTE_E5}
};

char keys[10];

int S = 0;

void piano_play() {
  int qa[10];
  
  for(int j = 0; j < S; j++) {
    for(int i = 0; i < KEYS; i++) {
      if(keys[j]==notes[0][i])
       qa[i] = i;
    }
  }
  
  if(S==1)
   tone(7, notes[1][qa[0]], 20);
  else if( S > 0 ) {
    for(int i = 0; i < S; i++) {
      tone(7, notes[1][qa[i]], 20);
      delay(20);
      noTone(7);
    }
  }
}


void setup() {
  for(int i = 0; i < 10; i++) {
    keys[i]=' ';
  }
  keyboard.begin(DataPin, IRQpin);
}


void loop() {
  int q = 0;
  char c = ' ';

  if( keyboard.available() ) {

    c = keyboard.read();
    keys[0] = c;
    S++;
     
  }
  
  piano_play();
  
  for(int i = 0; i < 10; i++) {
   keys[i]=' ';
  }

  S=0;
 }

