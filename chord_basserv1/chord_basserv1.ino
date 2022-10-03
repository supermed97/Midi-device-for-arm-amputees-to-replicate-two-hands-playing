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

void setup() {
  Serial.begin(31250);
    mySerial.begin(31250);
}

void loop() {
 if (mySerial.available() > 0) {  
  
    a=mySerial.read();
  while(a==144 ){
    mySerial.readBytes(temp,2);   /**Serial.println(n);  Serial.print("I AM note "); Serial.println(temp[0]);  Serial.print("I AM vel "); Serial.println(temp[1]);Serial.println("___________________"); **/   
      chord[n]=temp[0];
     // Serial.println("________________________PHASE  1___________________________________________");
    vel[n]=temp[1]; 
    //sendMsg(a,temp[0],temp[1]);
    n++; // n doesn't update continuosly when key is left pressed on meaning when key is being pressed on its out of loop 
    //Serial.print(" I am N ----> ");  Serial.println(n); Serial.println("-------------------------------------------------> ");
  chordcheck(10,n);  
       if (n>2 && state ==0){
       bass=chord[0]-48;  
       sendMsg(on,bass,vel[0]);
       state=1;     
      } // end of if   
     if(state==1){
        n=0;}
        invchordcheck(8,n);
     // Serial.print(" I am state ----> ");  Serial.println(state);
      //Serial.println("after-------------------------------------------------------------------------------------------> ");
     // Serial.print(" I am N ----> ");  Serial.println(n);
      
    a=mySerial.read(); 
    } // end of while
led(9,state);

/**if(n>5){
   blink(8);
  }**/
    while(a==128){
      mySerial.readBytes(temp1,2);
      if(temp1[0]-48 == bass && state==1){
       sendMsg(a,bass,temp1[1]) ;
       led(9,n);
       state=0; // end of if
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
  
 
