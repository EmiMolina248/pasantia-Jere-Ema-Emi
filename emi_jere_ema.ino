 /*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int sensorValue,regulaUmbral, servoValue,cont, prom, optionUmbral,segs;
 
//const int BUTTON_PIN = 7;
const int led = 8;
const int largoArray = 10;// variable que contiene el largo del array del sensor
int arraySensor[largoArray]; 
int arrayRegulador[largoArray];
int currentState  = HIGH;                         // the current reading from the input pin



int promValues(int b){
  int sum  = 0;
  for(int i= 1;i<largoArray ;i++){
   arraySensor[i-1] = arraySensor[i]; //funcion para sacar el promedio de los valores del sensor guardados en el array
   sum += arraySensor[i-1];
   }
  arraySensor[9] = b;
  sum += b ; 
  return sum/largoArray ;
}

           

int getUmbral(int p,int o, int um){
  
  if(currentState == LOW){
    if (optionUmbral== 3){
        optionUmbral=0;
    }
    else{
      optionUmbral++;
    }
}
  switch(o){
  case 0:
    return 250;
   break; 
  case 1:
    return 100 + um;
  break; 
  case 2:
     return p*1.25;
     break;
  }
}


  
void setup() {
  pinMode(led, OUTPUT);
  //pinMode(BUTTON_PIN, INPUT_PULLUP);
  optionUmbral= 1;
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  myservo.write(0);
}



void loop() {
  regulaUmbral = analogRead(A2);
  sensorValue = analogRead(A3);
  //currentState = digitalRead(BUTTON_PIN);
  if(cont % 2 == 0 ){
   prom = promValues(sensorValue);
   if (cont >= 800){
    cont=0;
   }
  }
  cont++; 
  if(sensorValue > getUmbral(prom, optionUmbral,regulaUmbral)){
   segs++;
   digitalWrite(led, HIGH);
   if(segs>=180){
    myservo.write(0);
    segs=0;
   }
   else{
    myservo.write(segs);
   }
  }
    else{
      segs = 0;
      digitalWrite(led, LOW);
      myservo.write(0);
    }
  Serial.println(String(sensorValue) +","+ String(prom)+ ", "+ String(getUmbral(prom,optionUmbral,regulaUmbral)) + ", " +String(segs));
  delay(100);        
                             
}



String arrayMessage(){
  String mess = "{";
  for(int i = 0; i<largoArray ;i++){      // funcion para mostrar los elementos del array
    mess += String(arraySensor[i])+ ", ";
  } 
    mess += "}";
    return mess;
} 
