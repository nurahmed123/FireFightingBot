#include <Wire.h>                //include Wire.h library
#include <Servo.h>              //include servo.h library
#include <Adafruit_MLX90614.h> //include MLX90614.h library

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo myservo;
 
int pos = 0;    
boolean fire = false;
double temp;

 
#define Left 8         // left sensor
#define Right 9       // right sensor
#define Forward 10   //front sensor

#define LM1 2        // left motor
#define LM2 3       // left motor
#define RM1 4      // right motor
#define RM2 5     // right motor
#define pump 6
 
void setup()
{
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  
  mlx.begin();
  myservo.attach(11);
  myservo.write(90); 
}
 
void put_off_fire()
{
    delay (500);
 
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    
   digitalWrite(pump, HIGH);
   delay(500);
    
    for (pos = 50; pos <= 130; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 130; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }
  
  digitalWrite(pump,LOW);
  myservo.write(90);
  
  fire=false;
}
 
void loop()
{
   temp = mlx.readObjectTempC(); 
   myservo.write(90); //Sweep_Servo(); 
 
    if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
    {
    
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
    
    else if (digitalRead(Forward) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    }
    
    else if (digitalRead(Left) ==0)
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
    
    else if (digitalRead(Right) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    }
     if (temp > 50)
     {
      put_off_fire();
     }
     else
     {
   fire=false;
     }
}
