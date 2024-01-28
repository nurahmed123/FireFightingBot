char BlueToothValue;

#include <Wire.h>               //include Wire.h library
#include <Servo.h>              //include servo.h library
#include <Adafruit_MLX90614.h>  //include MLX90614.h library

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo myservo;

int pos = 0;
boolean fire = false;
double temp;


#define Left 8     // left sensor
#define Right 10   // right sensor
#define Forward 9  //front sensor

#define LM1 2  // left motor
#define LM2 3  // left motor
#define RM1 4  // right motor
#define RM2 5  // right motor
#define pump 6

void setup() {
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
  Serial.begin(9600);
  digitalWrite(pump, 1);
}

void put_off_fire() {
  delay(500);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);

  digitalWrite(pump, 0);
  delay(500);

  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }

  digitalWrite(pump, 1);
  myservo.write(90);

  fire = false;
}

void manual_control() {
  if (Serial.available()) {
    BlueToothValue = Serial.read();
    // Serial.println(BlueToothValue);
  }

  if (BlueToothValue == 'L') {
    // Serial.println("l");
    left();
  } else if (BlueToothValue == 'R') {
    // Serial.println("r");
    right();
  } else if (BlueToothValue == 'F') {
    // Serial.println("f");
    forward();
  } else if (BlueToothValue == 'B') {
    // Serial.println("b");
    backward();
  } else if (BlueToothValue == 'S') {
    // Serial.println("s");
    stop();
  }
}

void forward() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void backward() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void stop() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
}

void left() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
}

void right() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void loop() {

  temp = mlx.readObjectTempC();
  myservo.write(90);  //Sweep_Servo();

  if (digitalRead(Left) == 1 && digitalRead(Right) == 1 && digitalRead(Forward) == 1) {
    stop();

    // digitalWrite(LM1, LOW);
    // digitalWrite(LM2, LOW);
    // digitalWrite(RM1, LOW);
    // digitalWrite(RM2, LOW);
  }

  else if (digitalRead(Forward) == 0) {
    forward();
    put_off_fire();
  }

  else if (digitalRead(Left) == 0) {
    left();
    put_off_fire();
  }

  else if (digitalRead(Right) == 0) {
    right();
    put_off_fire();

    digitalWrite(RM2, LOW);
  } else {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }
  if (temp > 50) {
    // put_off_fire();
  } else {
    fire = false;
  }





  manual_control();
}
