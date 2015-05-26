#include <Wire.h>
#include "nunchuck_funcs.h"

int loop_cnt=0;

byte joyx,joyy,zbut,cbut;
int ledPinX = 6;
int ledPinY = 9;

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

int melodyC[] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4 //CHARGE
};
 
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurationsC[] = {
  8, 8, 8, 8, 16, 2
};

void setup() {
  // put your setup code here, to run once:
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake
  pinMode(ledPinX, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly: 
    if( loop_cnt > 100 ) { // every 100 msecs get new data
        loop_cnt = 0;

        nunchuck_get_data();

        joyx  = map(nunchuck_joyx(), 37, 233, 0, 255); 
        // ranges from approx 37 - 233
        joyy  = map(nunchuck_joyy(), 25, 213, 0, 255); 
        // ranges from approx 25 - 213
        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton();
            
        analogWrite(ledPinX,joyx);
        analogWrite(ledPinY,joyy);
        if (zbut==1){
          shave();
        }
        if (cbut==1){
          charge();
        }
    }
    loop_cnt++;
    delay(1);
}
void shave() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
void charge() {
  // iterate over the notes of the melody:
  for (int thisNoteC = 0; thisNoteC < 8; thisNoteC++) {
 
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDurationC = 1000 / noteDurationsC[thisNoteC];
    tone(8, melodyC[thisNoteC], noteDurationC);
 
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotesC = noteDurationC * 1.30;
    delay(pauseBetweenNotesC);
    // stop the tone playing:
    noTone(8);
  }
}
