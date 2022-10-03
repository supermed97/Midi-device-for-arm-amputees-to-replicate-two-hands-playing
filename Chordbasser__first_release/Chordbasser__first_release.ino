#include <SoftwareSerial.h>
#include <ArduinoSort.h>
SoftwareSerial mySerial(0, 1); 
byte a;
byte b;
int siz;
byte on =144;
byte off =128;
byte temp[2];
byte temp1[2];
byte residue[2];
byte chord[3];
byte vel[3];
int state =0; int n =0;
byte msg[3]; byte bass;
int index; int state2 =0;
void setup() {
  Serial.begin(31250);
    mySerial.begin(31250);
}

void loop() {
 if (mySerial.available() > 0) {  
  
    a=mySerial.read();
  while(a==144 ){
    digitalWrite(3, LOW);
    mySerial.readBytes(temp,2);   
      chord[n]=temp[0];
    vel[n]=temp[1]; 
    n++; // n doesn't update continuosly when key is left pressed on meaning when key is being pressed on it's out of loop 
          if (n>2 && state ==0){
       
        sortArray(chord, 3);
          index =chordId(chord);
          
       bass=chord[index]-24;  
       sendMsg(on,bass,vel[0]);
       state=1;     
      } // end of if   
     if(state==1){
        n=0;}      
    a=mySerial.read(); 
    } // end of while
led(9,state);

    while(a==128){
      digitalWrite(3, HIGH);
      mySerial.readBytes(temp1,2);
      if(temp1[0]-24 == bass){
        digitalWrite(2, LOW);}
        else{
         digitalWrite(2, HIGH); }
      if(temp1[0]-24 == bass && state==1){
       sendMsg(a,bass,temp1[1]) ;
       led(9,n);
       state=0; // end of if
       state2=1;
      }
      if(state2==0){
        sendMsg(a,bass,temp1[1]) ;
        state=0; }
        if (state ==0 && state2==1){
          state2=0;
          }
      a=mySerial.peek();
     /** 
      b=a;
      if(b==144){ mySerial.readBytes(residue,2);
                    
                  //sendMsg(b,residue[0],residue[2]);
                 // blink(10); blink(10);blink(10);  Last modifier made because delays interrupts real time midi sending  
                  }**/
         }// end of while 
      led(9,state);
      
  } // end of if myserial.available()
}// end of void







    ////////////////////////////////////////////////////////////////////////// FUNCTIONS DECLARATIONS ///////////////////////////////////////////////////////////////////////////
void sendMsg(byte command, byte note, byte vel){
  msg[0]=command; msg[1]=note; msg[2]=vel;
  Serial.write(msg,3);
  Serial.flush();
  }
void blink(int pin){

    digitalWrite(pin,HIGH);
    delay(10);
    digitalWrite(pin,LOW); delay(10);
    
  }  
  void led(int pin,int n){
  if(state==1){
    digitalWrite(pin,HIGH);
    }
    if(state==0){
    digitalWrite(pin,LOW);  }
  }  
  void chordcheck(int pin,int x){
  if(x>2){
    digitalWrite(pin,HIGH);
    //delay(1);
    }
    else{
    digitalWrite(pin,LOW);  }
  }  
   void invchordcheck(int pin,int x){
  if(x<=2){
    digitalWrite(pin,HIGH);
    //delay(1);
    }
    else{
    digitalWrite(pin,LOW);  }
  }  
int chordId(byte* param){
  byte dist= param[1]-param[0];
  switch(dist){
    case 3:
    if ((param[2]-param[1])==4){
      return 0;}
      else if ((param[2]-param[1])==5){ return 2; 
    }
    break;
    case 4:
if ((param[2]-param[1])==3){
      return 0;}
      else if ((param[2]-param[1])==5){ return 2; 
    }
    break;
    case 5:
  return 1;
    break;
    
    
    
    
    
    }
  
  }  
 
