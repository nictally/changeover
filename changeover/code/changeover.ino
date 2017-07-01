int relay1=A2;
int relay2=A3;

int manauto=A0;
int ecgsolar=A1;

int manualled=3;
int autoled=2;
int ecgled=4;
int solarled=5;

int input1=9;  //ECG
int input2=8;  //SOLAR
boolean automanualstatus=true;
boolean ecgsolarstatus=false;

void systeminit(){
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  digitalWrite(relay1,HIGH);
   digitalWrite(relay2,HIGH);
  pinMode(manualled,OUTPUT);
  pinMode(autoled,OUTPUT);
  pinMode(ecgled,OUTPUT);
  pinMode(solarled,OUTPUT);
  pinMode(manauto,INPUT_PULLUP);
  pinMode(ecgsolar,INPUT_PULLUP);
  pinMode(input1,INPUT);
  pinMode(input2,INPUT);
  Serial.begin(9600);
  Serial.println("started");
  
}

void setup() {
  systeminit();
}

void loop() {
  checkautomanual();
  checkecgsolar();
  //automanualstatus false manual mode
  //ecgsolarstatus true   ecg mode
  //ecgsolarstatus false  solar mode
  if(!automanualstatus){
    delay(100); Serial.println("manual status");
    autoledoff();
    manledon();
    if(ecgsolarstatus)
    {
      delay(100); Serial.println("ECG");
     relay1off();
     relay2on();
     ecgledon();
     solarledoff();
      
    }
     if(!ecgsolarstatus)
    {
      delay(100); Serial.println("SOLAR");
      relay1on();
      relay2off(); 
      solarledon();
      ecgledoff();
    }
    
  }

  
  //automanualstatus true  automode
  if(automanualstatus){
    checkinputauto();
    delay(100); Serial.println("auto mode");
    autoledon();
    manledoff();
    
  }
  
  // put your main code here, to run repeatedly:

}
void manledon(){
  digitalWrite(manualled,HIGH);
}
void manledoff(){
  digitalWrite(manualled,LOW);
}
void autoledon(){
  digitalWrite(autoled,HIGH);
}
void autoledoff(){
  digitalWrite(autoled,LOW);
}
void ecgledon(){
  digitalWrite(ecgled,HIGH);
}
void ecgledoff(){
  digitalWrite(ecgled,LOW);
}
void solarledon(){
  digitalWrite(solarled,HIGH);
}
void solarledoff(){
  digitalWrite(solarled,LOW);
}
void relay1off(){
  digitalWrite(relay1,HIGH);
}
void relay1on(){
  digitalWrite(relay1,LOW);
}
void relay2off(){
  digitalWrite(relay2,HIGH);
}
void relay2on(){
  digitalWrite(relay2,LOW);
}
void checkinputauto(){
  autoledon();
  if((digitalRead(input1)==HIGH)&&(digitalRead(input2)==HIGH)){ ////SWITCH TO SOLAR
    relay1on();
    relay2off();
    solarledon();
    ecgledoff();
    delay(100); Serial.println("AUTOSOLAR");
  }
   if(digitalRead(input1)==HIGH&&digitalRead(input2)==LOW){ //SWITCH TO ECG
    relay1off();
    relay2on();
    ecgledon();
    solarledoff();
    delay(100); Serial.println("AUTOECG");
  }
   if(digitalRead(input1)==LOW&&digitalRead(input2)==HIGH){  //SWITCH TO SOLAR
    relay1on();
    relay2off();
    solarledon();
    ecgledoff();
    delay(100); Serial.println("AUTOSOLAR2");
  }
   if(digitalRead(input1)==LOW&&digitalRead(input2)==LOW){  //SYSTEM WONT WORK IN THE FIRST PLACE
    //DO NOTHING
       manledon();
      delay(200);
      manledoff();
      delay(200);
     
      
      ecgledon();
      delay(200);
      ecgledoff();
      delay(200);
      solarledon();
     delay(200);
      solarledoff();
       Serial.println("DO NOTHING");
      delay(200);
   
  }
}
void checkautomanual(){
  if(digitalRead(manauto)==LOW)
  {
    
    automanualstatus=!automanualstatus;
    delay(300);
  }
}
void checkecgsolar(){
   if(digitalRead(ecgsolar)==LOW)
  {
   
    ecgsolarstatus=!ecgsolarstatus;
    delay(300);
  }
  
}


