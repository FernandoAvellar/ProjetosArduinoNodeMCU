#include <Wire.h>

/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

//Braço esquerdo = 33 a 90
//Braço direito = 85 a 160
//Garra = 80 a 125 --> JOY1X
//Base 20 a 155 --> JOY1Y

#include <Servo.h>

#define BASE 5
#define GARRA 6
#define MOT_DIR 9
#define MOT_ESQ 10

#define JOY1X A0
#define JOY1Y A1
#define JOY2X A2
#define JOY2Y A3

Servo motorBase;
Servo motorGarra;
Servo motorDir;
Servo motorEsq;

void setup() {
  motorBase.attach(5);
  motorGarra.attach(6);
  motorDir.attach(9);
  motorEsq.attach(10);
  Serial.begin(9600);
}

void loop() {
  int valorJoy1x = analogRead(JOY1X); 
  int valorJoy1y = analogRead(JOY1Y); 
  int valorJoy2x = analogRead(JOY2X); 
  int valorJoy2y = analogRead(JOY2Y); 

  int valorJoy1yMotBase = map(valorJoy1y, 0, 1023, 20, 155);
  int valorJoy1xMotGarra = map(valorJoy1x, 0, 1023, 80, 125);
  int valorJoy2xMotEsq = map(valorJoy2x, 0, 1023, 35, 90);
  int valorJoy2yMotDir = map(valorJoy2y, 0, 1023, 85, 160);

  motorBase.write(valorJoy1yMotBase);
  motorGarra.write(valorJoy1xMotGarra);
  motorDir.write(valorJoy2yMotDir);
  motorEsq.write(valorJoy2xMotEsq);
           
  delay(100);                   
}

