/*
  Conexión de teclado matricial:
 * Pin 1 a 3 digital de arduino
 * Pin 2 a 2 digital de arduino
 * Pin 3 a A5 digital de arduino
 * Pin 4 a A4 digital de arduino 
 * Pin 5 a A3 annalógico de arduino
 * Pin 6 a A2 annalógico de arduino
 * Pin 7 a A1 annalógico de arduino
 * Pin 8 a A0 annalógico de arduino

 */

// Incluir la libreria:
#include <EEPROM.h>
#include <Keypad.h>
#include <Servo.h>

//Definición de variables para servos y motor a pasos
#define PinSerPinza 6
#define PinSerMuneca 7
#define PinSerCodo 8
#define PinSerHombro 9
//definicion de pins
const int motorPin1 = 10;   // 28BYJ48 In1
const int motorPin2 = 11;   // 28BYJ48 In2
const int motorPin3 = 12;   // 28BYJ48 In3
const int motorPin4 = 13;   // 28BYJ48 In4

Servo Srv_Wrist, Srv_Elbow, Srv_Shoulder, Srv_Hand;

//definicion variables
int motorSpeed = 1200;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 4076;  // pasos para una vuelta completa

//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };


/** Dirección dónde se guarda la cantidad de estados guardados */
unsigned char addStatusSize = 0;

/** Este arreglo contiene la posisicón de cada motor*/
byte status[5];
/** variable que ayuda a conocer la cantidad de estados */
byte statusSize;

String data = "";
/**
 * Variables que ayudan a manejar la posición
 * de cada servo junto también la posición de 
 * la base (el motor a pasos).
*/
byte pasos = 0;
byte shoulder = 130;
byte elbow = 50;
byte wrist = 90;
byte hand = 10;

/**
 * Varianle que nos ayuda a saber sí es vamos a 
 * manejar el brazo con los estados o bien con el
 * teclado matricial
*/
boolean manual = true;
boolean parar = false;



//--------Teclado matricial--------
//Definimos el número de renglones del teclado matricial
const byte rowsLength = 4;
//Definimos el número de columnas del teclado matricial
const byte colsLength = 4;
//Definimos los pines de los renglones que van conectados a arduino
byte rowPin [rowsLength] = {3, 2, A5, A4};
//Definimos los pines de las columnas que van conectados a arduino
byte colPin [colsLength] = {A3,A2,A1,A0};

//Definimos la matriz de char con el nombre de los bótones del teclado
//Cambiar # por P y D por R para darle funcionalidad al bóton de paro.
char keys[rowsLength][colsLength] = {
  {'1', '2', '3' , 'A'},
  {'4', '5', '6' , 'B'},
  {'7', '8', '9' , 'C'},
  {'*', '0', 'P' , 'R'}
};
//Inicializamos el teclado
Keypad kb = Keypad( 
  makeKeymap( keys ), 
  rowPin,
  colPin,
  rowsLength,
  colsLength
);
//Definimos una variable de tipo char para que muestre cual tecla fue presionada
char keyPressed;

void setup() {
  Srv_Hand.attach(PinSerPinza);
  Srv_Wrist.attach(PinSerMuneca);
  Srv_Elbow.attach(PinSerCodo);
  Srv_Shoulder.attach(PinSerHombro);

  //declarar pines como salida
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  Srv_Hand.write(0);
  Srv_Wrist.write(90);
  Srv_Elbow.write(50);
  Srv_Shoulder.write(130);
  delay(3000);
  
  /** Se inicializa la cantidad de estados guardados*/
  statusSize = getStatusSize();
  // Configurar la comunicación serial.
  Serial.begin(9600);
}

void loop() {
  keyPressed = kb.getKey();
  if( keyPressed != NO_KEY ){
    Serial.println( keyPressed );
    if( keyPressed == 'A'){

    }
  }

  if(Serial.available( )){
    //Fijar una espera para que el arduino lea toda la información del Serial
    delay(200);
     /**
     * A => Modo automático, cambiamos al modo automático
     * M => Modo manual, cambiamos al modo maunual
     * P => Parar el sistema.
     * R => Para reunudar el sistema
     */
    data = Serial.readStringUntil('\n');
    if( data == "M" ) {
      manual = true;     
    } else if ( data == "A" ){
      manual = false;
      /** 
       * Sí el modo es autómatico se van a leer 5 estaos los cuales
       * servirán para mover de manera automática el robot.
      */
      while( Serial.available() > 0 ){
        /*
        data = Serial.readStringUntil('\n');
        byte numerito =  getNumber(data,0) ;
        Serial.println( numerito );      
        status[0] = getNumber(data, 0);
        status[1] = getNumber(data, 1);
        status[2] = getNumber(data, 2);
        status[3] = getNumber(data, 3);
        status[4] = getNumber(data, 4); */
      }      
    }
    
  }
  Serial.flush();
  /* En modo manual se va a leer todos los dados del 
  teclado para escribir en los servos. */
  if( manual ) {
    if( keyPressed != NO_KEY ){
      Serial.println( keyPressed );
      if( keyPressed == '1'){
        //girar en sentido de las manecillas del reloj
        for (int i = 0; i < 300; i++)
        {
          clockwise();
          delayMicroseconds(motorSpeed);
        }
      }else if( keyPressed == '2'){
        //girar en sentido contrario a las manecillas del reloj
        for (int i = 0; i < 300; i++)
        {
          anticlockwise();
          delayMicroseconds(motorSpeed);
        }
      }else if( keyPressed == '4'){
        shoulder+=5;    
        Srv_Shoulder.write(shoulder);
      }else if( keyPressed == '5'){
        shoulder-=5;    
        Srv_Shoulder.write(shoulder);
      }else if( keyPressed == '7'){
        elbow+=5;
        Srv_Elbow.write(elbow);
      }else if( keyPressed == '8'){
        elbow-=5;
        Srv_Elbow.write(elbow);
      }else if( keyPressed == '3'){
        wrist+=5;
        Srv_Wrist.write(wrist);
      }else if( keyPressed == 'A'){
        wrist-=5;
        Srv_Wrist.write(wrist);
      }else if( keyPressed == '6'){
        hand+=5;
        Srv_Hand.write(hand);
      }else if( keyPressed == 'B'){
        hand-=5;
        Srv_Hand.write(hand);
      }
    }
  } 
  /* En modo automático se le dá un delay a cada uno
  de los estaos un tiempo para que se puedan ejecutar.  
    Nos vamos apoyar de una variable global la cual nos 
  ayude a saber cual es el estado que se debe ejecutar.*/
  else {
    
  }
}

byte getNumber( String text, int pos ){
  return (byte)
    text.substring(
      (pos*3), 
      (pos*3)+3
    ).toInt();
}

void saveStatus( byte toSave [ ] ){
  updateStatusSize( +statusSize );
  byte address = statusSize * 5;
  for(byte i = address, e = 0; i < address + 5; i++, e++){
    EEPROM.write( toSave[ e ], i+1 );
  }    
}

void deleteStatus(){  
  if( statusSize > 0 ){
    byte address = statusSize * 5;
    for(byte i = address; i < address + 5; i++){
      EEPROM.write( 255, i+1 );
    }
    updateStatusSize( --statusSize );
  }  
}

void getStatus(byte position){
    byte address = position * 5;
    for(byte i = address, e = 0; i < address+ 5; i++, e++){
      status[e] = EEPROM.read( i+1 );
    }
    
}

/** 
 *  @author Juda Alector
 *  @since Nov 13, 2018
 *  @desc Actualiza en la memoria EEPROM la 
 *        cantidad de status guardados.
 *  @param ( newSize ) Es el nuevo valor para la cantidad
 *        de estados guardados en EEPROM.
 */
void updateStatusSize( byte newSize ){
  EEPROM.write( newSize, addStatusSize );
}

/** 
 *  @author Juda Alector
 *  @since Nov 13, 2018
 *  @desc Ayuda a saber la cantidad de estados que están
 *        guardados en la memoria.
 */
byte getStatusSize( ){
  byte amountOfStatus = EEPROM.read( addStatusSize );
  return ( amountOfStatus == 255 )? 0 : amountOfStatus;
}

/** 
 *  @author Juda Alector
 *  @since Nov 13, 2018
 *  @desc Método que pone en alto los bits de la memoria 
 *  @param ( until ) valor de 0 a 255 que nos permmite borrar bloques 
 *        de 5 en 5 en la memoria. Ejem. Sï se da 4, el borrara 
 *        20 bytes de la memoria, sí son 5 serán 25.
 *        
 *        IMPORTATANTE: Este método sólo debe usarse cuando 
 *  se quiera borrar los datos de la memoria, sí se manda 
 *  a llamar constantemente los datos no se guardarán como se 
 *  epsera.
 */
void clearEEPROM( byte until ) {
  if( until > 0 ){
    int top = ( until * 5 ) + 1;
    for(byte i = 1; i < top ; i++){
       EEPROM.write( 255, i);
    }
  }
}

//Método para girar el motor a pasos en sentido a las manecillas del reloj
void clockwise(){
  //Aumentar el contador de pasos
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}
 //Método para girar el motor a pasos en sentido contrario a las manecillas del reloj
void anticlockwise(){
  //Disminuir el contador de pasos
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}
void setOutput(int step)
{
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}
