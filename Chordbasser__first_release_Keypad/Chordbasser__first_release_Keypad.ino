#include <Key.h>
#include <Keypad.h>

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
byte msg[3]; byte bass; byte shift;
int index;int state2 =0; char modesig=0;
//////////////////////// keypad variables ////////////////////////////////////
const byte ROWS = 4; 
const byte COLS = 4; 
char keyp; char mode; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char inizio =0; char count =0; char count1= 0; char octave; char oct=0;
char keycontrol;
byte rowPins[ROWS] = {10,11,12,13}; 
byte colPins[COLS] = {4,5,6,7}; 
//byte shft[6]={0,1,2,3,4,5}

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Keypad customKeypad1 = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(31250);
    mySerial.begin(31250);
}

void loop() {
   signaler(2,inizio); // blink connected to pin 2 with inizio=0 , blinking means start button hasnt been clicked
  if(count==0){  // count is set to 0 it is the flag that lets me get keyp value just once
   keyp = customKeypad.getKey(); //keyp is the start button acquired, keyp should be 'A' to make it begin
   }
   ///////////_________________________________________________________________________________________________////////////////
   
   if(keyp == 'A' && count ==0){ // if keyp is A and count hasnt incremented, I set start flag to 1 
      inizio=1; // set start flag to 1
      count++; // increase count so arduino only scans for start button ONCE when in its infinite loop
    }
    //////////////_____________________________________________________________///////////////////
    
    if(inizio==1 && count1==0){  // code for button to decide which mode and control flag is 'count1' to make sure its ran only ONCE after a mode button has been pressed
   signaler(2,inizio); // turn off the blinking led to indicate start has now been pressed
   mode=customKeypad.getKey(); // get button
   signaler(3,keypadchk(mode)); // blink led connected to pin 3 to signify no button has been pressed
   char st= keypadchk(mode); // see if the arduino got an input
      if(st==1){ // if it's a valid input
    signaler(3,1); // turn off led
    count1++; // increment flag so the initial if block is not ran again and mode button is not overwritten
    }
    }
 //////////////////////////////////// FIRST MODE OF OPERATION //////////////////////////////////
   if(inizio==1 && mode=='B'){ // if start has been pressed and mode selected is 'B', THIS IF  INCLUDES IF MYSERIAL.AVAILABLE !!!
    if(oct==0){ // oct is a flag so that I dont run this if block infinitely in the arduino's infinite loop
      octave=customKeypad1.getKey(); // get desired octave, using customkeypad1 object not customkeypad !! customkeypad wasn't working !!
      signaler(8,keypadchkoct(octave));   // blink led to indicate nothing valid has been pressed
      char st1= keypadchkoct(octave); // see if valid octave number has been pressed, st1 is either 1 OR 0
          if(st1==1){
    signaler(8,1); // SINCE st1 is 1 meaning a valid octave has been pressed turn off blinking led
    oct++;  // increment flag so main if is ran only once and the octave is acquired only once and not overwritten
    }
    shift =cast(octave); // used my cast function to map numeric button inputs to number
    //Serial.print("I AM SHIFT--> "); Serial.println(shift*2);
      }
 if (mySerial.available() > 0) {  
  
    a=mySerial.read();
  while(a==144 ){
    mySerial.readBytes(temp,2);   
      chord[n]=temp[0];
    vel[n]=temp[1]; 
    n++; // n doesn't update continuosly when key is left pressed on meaning when key is being pressed on it's out of loop 
          if (n>2 && state ==0){
       
        sortArray(chord, 3);
          index =chordId(chord);
          
       bass=chord[index]-(shift*12); 
       
       sendMsg(on,bass,vel[0]);
       state=1;     
      } // end of if   
     if(state==1){
        n=0;}      
    a=mySerial.read(); 
    } // end of while
led(9,state);

    while(a==128){
      mySerial.readBytes(temp1,2);
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
  char resetoctave=customKeypad.getKey();
  if(resetoctave=='#'){
    oct=0;
  }
   } //END OF MODE B
}// end of void

void sendMsg(byte command, byte note, byte vel){
  msg[0]=command; msg[1]=note; msg[2]=vel;
  Serial.write(msg,3);
  Serial.flush();
  }
void blink(int pin){

    digitalWrite(pin,HIGH);
    delay(75);
    digitalWrite(pin,LOW); delay(75);
    
  }  
  void led(int pin,int n){
  if(state==1){
    digitalWrite(pin,HIGH);
    }
    if(state==0){
    digitalWrite(pin,LOW);  }
  }  
  void signaler(int pin,int n){
  if(n==0){
    digitalWrite(pin,HIGH);
    delay(75);digitalWrite(pin,LOW); delay(75);
    }
    if(n==1){
    digitalWrite(pin,LOW);  }
  }    /**
   void invchordcheck(int pin,int x){
  if(x<=2){
    digitalWrite(pin,HIGH);
    //delay(1);
    }
    else{
    digitalWrite(pin,LOW);  }
  }  **/
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
  char keypadchk(char x)
    {
        if (x =='1'|| x== '2'|| x== '3' || x== 'A'|| x=='4'|| x== '5' || x== '6' || x== 'B' || x=='7' || x== '8'|| x== '9'||x== 'C'|| x== '*' || x== '0' || x== '#' || x== 'D'){
    return 1;
    }
 else { return 0;}
  }
  char keypadchkoct(char x)
    {
        if (x =='1'|| x== '2'|| x== '3' || x=='4'|| x== '5' || x=='0'){
    return 1;
    }
 else { return 0;}
  }
  byte cast(char v){
     if (v=='0'){
      return 0;}
    if (v=='1'){
      return 1;
    }
    if (v=='2'){
      return 2;
    }if (v=='3'){
      return 3;
    }if (v=='4'){
      return 4;
    }if (v=='5'){
      return 5;
    }
    }
  /** if(keyp == 'A'){
    
    }**/
  /**  
  if (keycontrol ==0 && g<9){
   blink(3); }
    else if (keycontrol ==1){
      g++;
      Serial.println(keyp);
      Serial.println(g);
    }
    if(g>9){
      digitalWrite(3,LOW);
      g=0;
      }**/
