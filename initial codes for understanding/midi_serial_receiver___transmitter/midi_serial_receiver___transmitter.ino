#include <SoftwareSerial.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
SoftwareSerial mySerial(0, 1); // RX, TX
// MIDI commands

int noteON = 144;//144 = 10010000 in binary, note on command
 int noteOFF = 128;//128 = 10000000 in binary, note off command
 byte arry[4]; byte noteon[4]; byte noteoff[4];byte pitch[4]; byte velocity[4];

void setup() {
    Serial.begin(31250);
    mySerial.begin(31250);
    
    //delay(100);
    //state = STATE_NONE;
    //actionOn = false;   
    }

void loop () {

    // Is there any MIDI waiting to be read?
    if (mySerial.available() > 0) {
        mySerial.readBytes(arry,3);
        Serial.write(arry,3);
       mySerial.readBytes(noteoff,3);
       if (noteoff[0]==128){
       Serial.write(noteoff,3);}
    } 

} 
void ledon(){
  digitalWrite(13,HIGH);
  }
  void ledoff(){
    digitalWrite(13,LOW);
    }
  
    
  
