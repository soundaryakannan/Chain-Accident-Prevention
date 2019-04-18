const int trigPin = 4;
const int echoPin = 2;
int vibr_Pin =3;
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() 
{ 
   pinMode(vibr_Pin, INPUT);
   radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
Serial.begin(9600);
} 
void loop()
{
 
long duration, inches, cm;
pinMode(trigPin, OUTPUT); 
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT); 
duration = pulseIn(echoPin, HIGH);
cm = microsecondsToCentimeters(duration);
Serial.print(cm);
Serial.println("mm"); 
delay(100);
while(cm<200&&cm!=0)
{
  long measurement =TP_init();
  delay(50);
  if (measurement > 1000){
     Serial.println("VIBED");
     const char text[] = "ALERT";
     radio.write(&text, sizeof(text));
     delay(1000);
  }
}
delay(1000);
}

long microsecondsToCentimeters(long microseconds)
{return microseconds / 29 / 2;}
long TP_init(){
  delay(10);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
