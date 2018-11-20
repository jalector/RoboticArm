#include <Servo.h>

#define PinSerPinza 6
#define PinSerMuneca 7
#define PinSerCodo 8
#define PinSerHombro 9
//definicion de pins
const int motorPin1 = 10;   // 28BYJ48 In1
const int motorPin2 = 11;   // 28BYJ48 In2
const int motorPin3 = 12;   // 28BYJ48 In3
const int motorPin4 = 13;   // 28BYJ48 In4

Servo Srv_Muneca, Srv_Codo, Srv_Hombro, Srv_Pinza;

//definicion variables
int motorSpeed = 1200;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 4076;  // pasos para una vuelta completa

//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

void setup() {
  Srv_Pinza.attach(PinSerPinza);
  Srv_Muneca.attach(PinSerMuneca);
  Srv_Codo.attach(PinSerCodo);
  Srv_Hombro.attach(PinSerHombro);

  //declarar pines como salida
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  Srv_Pinza.write(0);
  Srv_Muneca.write(90);
  Srv_Codo.write(50);
  Srv_Hombro.write(130);
  delay(3000);
}

void loop() {
  for (int x = 0; x <= 180; x += 1) {
    Srv_Pinza.write(x);
    Srv_Muneca.write(x);
    Srv_Codo.write(x);
    Srv_Hombro.write(x);
    delay(50);
  }
  for (int x = 180; x >= 0; x -= 1) {
    Srv_Pinza.write(x);
    Srv_Muneca.write(x);
    Srv_Codo.write(x);
    Srv_Hombro.write(x);
    delay(50);
  }
  /*Srv_Pinza.write(45);
    Srv_Muneca.write(45);
    Srv_Codo.write(45);
    Srv_Hombro.write(45);
    delay(2000);

    Srv_Pinza.write(90);
    Srv_Muneca.write(90);
    Srv_Codo.write(90);
    Srv_Hombro.write(90);
    delay(2000);

    Srv_Pinza.write(135);
    Srv_Muneca.write(135);
    Srv_Codo.write(135);
    Srv_Hombro.write(135);
    delay(2000);*/
}
