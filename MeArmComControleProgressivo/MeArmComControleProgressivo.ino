//Braço esquerdo = 33 a 90 --> JOY2X
//Braço direito = 85 a 160 --> JOY2Y
//Garra = 80 a 125 --> JOY1X
//Base 20 a 155 --> JOY1Y

#include <VarSpeedServo.h>

#define ANGULO_INICIAL_MOTOR 90

#define BASE 5
#define GARRA 6
#define MOT_DIR 9
#define MOT_ESQ 10

#define JOY1X A0
#define JOY1Y A1
#define JOY2X A2
#define JOY2Y A3

VarSpeedServo motorBase;
VarSpeedServo motorGarra;
VarSpeedServo motorDir;
VarSpeedServo motorEsq;

int auxBase = ANGULO_INICIAL_MOTOR;
int auxGarra = ANGULO_INICIAL_MOTOR;
int auxMotEsq = ANGULO_INICIAL_MOTOR;
int auxMotDir = ANGULO_INICIAL_MOTOR;

void setup() {
  motorBase.attach(5);
  motorGarra.attach(6);
  motorDir.attach(9);
  motorEsq.attach(10);
  motorBase.write(ANGULO_INICIAL_MOTOR);
  motorGarra.write(ANGULO_INICIAL_MOTOR);
  motorDir.write(ANGULO_INICIAL_MOTOR);
  motorEsq.write(ANGULO_INICIAL_MOTOR);
  Serial.begin(9600);
}

void loop() {
  moverMotorBase();
  moverMotorGarra();
  moverMotorEsquerdo();
  moverMotorDireito();
           
  delay(50);                   
}

void moverMotorBase() {
  int valorJoy1yMotBase = analogRead(JOY1Y);
  valorJoy1yMotBase = map(valorJoy1yMotBase, 0, 1023, 20, 155);
  if(valorJoy1yMotBase > 100 && auxBase < 151 ){
    auxBase+=5;
    motorBase.write(auxBase,50);
  }else if(valorJoy1yMotBase < 60 && auxBase > 20){
    auxBase-=5;
    motorBase.write(auxBase,50);
  }  
}

void moverMotorGarra() {
  int valorJoy1xMotGarra = analogRead(JOY1X);
  valorJoy1xMotGarra = map(valorJoy1xMotGarra, 0, 1023, 80, 125);
  if(valorJoy1xMotGarra > 105 && auxGarra < 121 ){
    auxGarra+=5;
    motorGarra.write(auxGarra,50);
  }else if(valorJoy1xMotGarra < 100 && auxGarra > 80){
    auxGarra-=5;
    motorGarra.write(auxGarra,50);
  }  
}

void moverMotorEsquerdo() {
  int valorJoy2xMotEsq = analogRead(JOY2X);
  valorJoy2xMotEsq = map(valorJoy2xMotEsq, 0, 1023, 35, 90);
  if(valorJoy2xMotEsq > 65 && auxMotEsq < 91 ){
    auxMotEsq+=5;
    motorEsq.write(auxMotEsq,50);
  }else if(valorJoy2xMotEsq < 60 && auxMotEsq > 40){
    auxMotEsq-=5;
    motorEsq.write(auxMotEsq,50);
  }  
}

void moverMotorDireito() {
  int valorJoy2yMotDir = analogRead(JOY2Y);
  valorJoy2yMotDir = map(valorJoy2yMotDir, 0, 1023, 0, 180);
  if(valorJoy2yMotDir > 120 && auxMotDir < 156 ){
    auxMotDir+=5;
    motorDir.write(auxMotDir,50);
  }else if(valorJoy2yMotDir < 80 && auxMotDir > 90){
    auxMotDir-=5;
    motorDir.write(auxMotDir,50);
  }  
}

