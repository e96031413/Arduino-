#include <Servo.h>
Servo myservo;			
int potpin=A0;			
int val;			
void setup() 
{
myservo.attach(9);		
pinMode(A0, INPUT);
Serial.begin(9600);
}
void loop()
{
  Serial.println(val);
val = analogRead(potpin);	
val = map(val,0,1023,0,180);	
myservo.write(val); 			
delay(10);					
}

