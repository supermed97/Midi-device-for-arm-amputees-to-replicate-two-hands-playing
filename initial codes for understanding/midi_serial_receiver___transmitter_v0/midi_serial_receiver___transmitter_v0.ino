#include <SoftwareSerial.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
SoftwareSerial mySerial(0, 1); // RX, TX
// MIDI commands

int noteON = 144;//144 = 10010000 in binary, note on command
 int noteOFF = 128;//128 = 10000000 in binary, note off command
 byte arry[3]; byte chord[4];byte noteoff[4];byte pitch[4]; byte velocity[4];

void setup() {
    Serial.begin(31250);
    mySerial.begin(31250);
    
    //delay(100);
    //state = STATE_NONE;
    //actionOn = false;   
    }

void loop () {
    int i =0; int j=0;
    // Is there any MIDI waiting to be read?
    if (mySerial.available() > 0 ) {
      byte k =mySerial.read();
        while(i<=3 && k==144){
          mySerial.readBytes(arry,2);
          chord[i]=arry[0]; // to delete
          i++;
          } // end of while
      if(k==144){    
      Serial.println("out of loop"); // to delete
     byte bass=chord[0]-24;
     noteoff[0]=144; noteoff[1]=bass; noteoff[2]=110;
     Serial.write(noteoff,3); // to delete
     }      
     noteoff[0]=128;
     Serial.write(noteoff,3);
     //delay(100);
     
          
    } // end of if

} // end of void loop()
void ledon(){
  digitalWrite(13,HIGH);
  }
  void ledoff(){
    digitalWrite(13,LOW);
    }
  
byte noteONcheck(){

 while (mySerial.available() > 0 && mySerial.read()==144  ) {
        mySerial.readBytes(arry,3); }
  return arry[0];      
        
  }    
  
