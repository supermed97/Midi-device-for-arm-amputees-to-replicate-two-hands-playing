#include <SoftwareSerial.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
SoftwareSerial mySerial(0, 1); // RX, TX
// MIDI commands

int noteON = 144;//144 = 10010000 in binary, note on command
 int noteOFF = 128;//128 = 10000000 in binary, note off command
 byte arry[3]; byte chord[4]; // byte noteoff[4];byte pitch[4]; byte velocity[4];

void setup() {
    Serial.begin(9600);
    mySerial.begin(31250);
    
    //delay(100);
    //state = STATE_NONE;
    //actionOn = false;   
    }

void loop () {
    int i =0;
    // Is there any MIDI waiting to be read?
    if (mySerial.available() > 0 ) {
        while(i<=3){
          chord[i]=noteONcheck();
          Serial.println(chord[i]); // to delete
          i++;
          } // end of while
      Serial.println("out of loop"); // to delete
     byte bass=chord[0]-24;
     Serial.println(bass); // to delete
     
          
    } // end of if

} // end of void loop()
void ledon(){
  digitalWrite(13,HIGH);
  }
  void ledoff(){
    digitalWrite(13,LOW);
    }
  
byte noteONcheck(){

  if (mySerial.available() > 0 && mySerial.read()==144  ) {
        mySerial.readBytes(arry,3); }
  return arry[0];      
        
  }    
  
