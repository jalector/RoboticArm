/*
  Conexión de teclado matricial:
 * Pin 1 a 4 digital de arduino
 * Pin 2 a 3 digital de arduino
 * Pin 3 a A5 digital de arduino
 * Pin 4 a A4 digital de arduino 
 * Pin 5 a A3 annalógico de arduino
 * Pin 6 a A2 annalógico de arduino
 * Pin 7 a A1 annalógico de arduino
 * Pin 8 a A0 annalógico de arduino
 *
  Conexión de servomotores para Brazo Robótico:
 * Pinza de Robot a Pin 6 digital de arduino
 * Muneca de Robot a Pin 7 digital de arduino
 * Codo de Robot a Pin 8 digital de arduino
 * Hombro de Robot a Pin 9 digital de arduino
 *
  Conexión de motor a pasos para Base de Brazo Robótico:
 * Pin 1 de Puente H a Pin 10 digital de arduino
 * Pin 2 de Puente H a Pin 11 digital de arduino
 * Pin 3 de Puente H a Pin 12 digital de arduino
 * Pin 4 de Puente H a Pin 13 digital de arduino
 * Pin - de Puente H a tierra
 * Pin + de Puente H a vcc
 * 
  Conexión de LED informativo de funcionamiento:
 * Pin 5 digital de arduino
 * 
  Conexión de botón de Paro de Emergencia:
 * Pin 2 digital de arduino
 * 
 * 
 * *** En Java se utiliza la librería Panama HiTek para 
 *     conectar arudino con Java.
 *     
 * *** En arduino al utilizar la sentencia println se envian
 *     los datos impresos a la aplicación de Java. 
 */

// Incluir la libreria:
#include <EEPROM.h> //Para guardar datos en la memoria EEPROM de Arduino
#include <Keypad.h> //Para utilizar el teclado matricial
#include <Servo.h> //Para mover los servomotores
#include "LowPower.h" //¿¿¿¿¿¿¿¿¿¿¿¿¿¿Sí se utiliza????????????????

//-----------Motores para Controlar el Robot------------
//Definición de variables y pines para servomotores
#define PinSerPinza 6
#define PinSerMuneca 7
#define PinSerCodo 8
#define PinSerHombro 9

//Definición de constantes y pines para motor a pasos (Puente H)
const int motorPin1 = 10;   // 28BYJ48 In1
const int motorPin2 = 11;   // 28BYJ48 In2
const int motorPin3 = 12;   // 28BYJ48 In3
const int motorPin4 = 13;   // 28BYJ48 In4

// Inicializar la libreria con variables para controlar los servomotores
Servo Srv_Wrist, Srv_Elbow, Srv_Shoulder, Srv_Hand;

//Definición de variables para controlar la velocidad y los pasos del motor a pasos
int motorSpeed = 1200;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 4076;  // pasos para una vuelta completa

//Datos necesarios para controlar la secuencia de bobinas del motor a pasos
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

//-----------Botón Paro de Emergencia------------
//Definición de variables para botón de paro de emergencia (interrupción)
#define stopButton 2
volatile boolean stopped = false;

//-----------Manejo de EEPROM------------
/** Dirección dónde se guarda la cantidad de estados guardados */
unsigned char addStatusSize = 0;

/** Este arreglo contiene la posición de cada motor*/
byte status[5];
/** Variable que ayuda a conocer la cantidad de estados */
byte statusSize;

String data = "";
/**
 * Variables que ayudan a manejar la posición
 * de cada servo, así como la posición de 
 * la base (el motor a pasos).
*/
byte pasos = 0;
byte shoulder = 130;
byte elbow = 50;
byte wrist = 90;
byte hand = 10;

/**
 * Variable que nos ayuda a saber sí vamos a 
 * manejar el brazo con los estados (modo automático)
 * o bien con el teclado matricial (modo manual)
*/
boolean manual = false;
boolean parar = false;

//--------Teclado matricial--------
//Definimos el número de renglones del teclado matricial
const byte rowsLength = 4;
//Definimos el número de columnas del teclado matricial
const byte colsLength = 4;
//Definimos los pines de los renglones que van conectados a arduino
byte rowPin [rowsLength] = {4, 3, A5, A4};
//Definimos los pines de las columnas que van conectados a arduino
byte colPin [colsLength] = {A3,A2,A1,A0};

//Definimos la matriz de char con el nombre de los bótones del teclado
//Cambiar # por P, y D por R para darle funcionalidad al bóton de paro.
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
  //Declaración de push button como pin de entrada para reconocer interrupción
  pinMode(stopButton, INPUT);

  //Asignación de pin digital a cada uno de los servomotores inicializados en la librería
  Srv_Hand.attach(PinSerPinza);
  Srv_Wrist.attach(PinSerMuneca);
  Srv_Elbow.attach(PinSerCodo);
  Srv_Shoulder.attach(PinSerHombro);

  //Declaración de pines del motor a pasos (Puente H) como salida
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  //Establecer posición inicial a cada uno de los servomotores
  Srv_Hand.write(0);
  Srv_Wrist.write(90);
  Srv_Elbow.write(50);
  Srv_Shoulder.write(130);
  //Tiempo de espera para correcto acomodo del Brazo Robótico
  delay(3000);
  
  /** Se inicializa la cantidad de estados guardados*/
  statusSize = getStatusSize();
  // Configurar la comunicación serial.
  Serial.begin(9600);
}
int currentStatus = 0;

void loop() {
  //Interrupción donde el puerto que interviene es el 2
  //Para esta práctica es el pin correspondiente al push button
  //Al efectuarse la interrupción, se realiza un paro de emergencia en el brazo robótico
  attachInterrupt(digitalPinToInterrupt(stopButton), interruption, RISING);
  detachInterrupt(0);

  // Obtenemos el valor del teclado
  keyPressed = kb.getKey();
  //Comprobamos sí una tecla fue presionada
  if( keyPressed != NO_KEY ){
    // Enviamos la información de la tecla
    // La información es la contenida en el arreglo keys
    Serial.println( keyPressed );
    //Sí el valor de esa tecla fue 'A'
    if( keyPressed == 'A'){

    }
  }

  //Verificar si se tiene información pendiente por revisar
  if(Serial.available( )){
    //Fijar una espera para que el arduino lea toda la información del Serial
    delay(200);
    //Definición de las diferentes posibles entradas del teclado matricial
    //Y su efecto en el Brazo Robótico
     /**
     * A => Modo automático, cambiamos al modo automático
     * M => Modo manual, cambiamos al modo manuual
     * P => Parar el sistema.
     * R => Para reunudar el sistema
     */
    //Lectura de información recibida por el puerto serial hasta que encuentra un salto de línea
    data = Serial.readStringUntil('\n');
    //Si se recibe una "M" se lleva a cabo el control manual del Brazo Robótico por medio del teclado matricial
    if( data == "M" ) {
      manual = true;
    //Si se recibe una "A" se lleva a cabo el modo automático del Brazo Robótico
    } else if ( data == "A" ){
      manual = false;
      /** 
       * Sí el modo es autómatico se van a leer 5 estados los cuales
       * servirán para mover de manera automática el robot.
      */
      while( Serial.available() > 0 ){
        data = Serial.readStringUntil('\n');
        Serial.println( data );      
        byte toSave [5];
        toSave[0] = getNumber(data, 0);
        toSave[1] = getNumber(data, 1);
        toSave[2] = getNumber(data, 2);
        toSave[3] = getNumber(data, 3);
        toSave[4] = getNumber(data, 4); 
        
        saveStatus( toSave );
      }      
    }
    
  }
  //Función que limpia el buffer de datos recibidos por el puerto serial
  Serial.flush();
  /* En modo manual se va a leer todos los datos del 
  teclado para escribir en los servos. */
  if( manual ) {
    //Comprobamos sí una tecla fue presionada
    if( keyPressed != NO_KEY ){
      Serial.println( keyPressed );
      if( keyPressed == '1'){
        //Si se presiona la tecla "1" la base gira en sentido de las manecillas del reloj
        for (int i = 0; i < 300; i++)
        {
          clockwise();
          delayMicroseconds(motorSpeed);
        }
      }else if( keyPressed == '2'){
        //Si se presiona la tecla "2" la base gira en sentido contrario a las manecillas del reloj
        for (int i = 0; i < 300; i++)
        {
          anticlockwise();
          delayMicroseconds(motorSpeed);
        }
      }else if( keyPressed == '4'){
        //Si se presiona la tecla "4" el hombro se eleva 5 grados
        shoulder+=5;
        Srv_Shoulder.write(shoulder);
      }else if( keyPressed == '5'){
        //Si se presiona la tecla "5" el hombro baja 5 grados
        shoulder-=5;    
        Srv_Shoulder.write(shoulder);
      }else if( keyPressed == '7'){
        //Si se presiona la tecla "7" el codo se eleva 5 grados
        elbow+=5;
        Srv_Elbow.write(elbow);
      }else if( keyPressed == '8'){
        //Si se presiona la tecla "8" el codo baja 5 grados
        elbow-=5;
        Srv_Elbow.write(elbow);
      }else if( keyPressed == '3'){
        //Si se presiona la tecla "3" la muneca gira 5 grados hacia la derecha
        wrist+=5;
        Srv_Wrist.write(wrist);
      }else if( keyPressed == 'A'){
        //Si se presiona la tecla "A" la muneca gira 5 grados hacia la izquierda
        wrist-=5;
        Srv_Wrist.write(wrist);
      }else if( keyPressed == '6'){
        //Si se presiona la tecla "6" la pinza se abre 5 grados
        hand+=5;
        Srv_Hand.write(hand);
      }else if( keyPressed == 'B'){
        //Si se presiona la tecla "B" la pinza se cierra 5 grados
        hand-=5;
        Srv_Hand.write(hand);
      }
    }
  } 
  /* En modo automático se le da un delay a cada uno
  de los estados, un tiempo para que se puedan ejecutar.  
    Se utiliza una variable global la cual
  ayuda a saber cual es el estado que se debe ejecutar.*/
  else {
    getStatus( currentStatus++ );    
    
    Srv_Shoulder.write( status[1] );
    Srv_Elbow.write( status[2] );
    Srv_Wrist.write( status[3] );
    Srv_Hand.write( status[4] );
    delay( 1000 );
    
    Serial.print("[CS]:");
    Serial.println( currentStatus );
  }
}

//Método utilizado para obtener ????????????????????????????????????????
byte getNumber( String text, int pos ){
  return (byte)
    text.substring(
      (pos*3), 
      (pos*3)+3
    ).toInt();
}

//Método utilizado para guardar un estado con las posiciones deseadas en los 5 motores del Brazo Robótico
void saveStatus( byte toSave [ ] ){
  updateStatusSize( +statusSize );
  byte address = statusSize * 5;
  for(byte i = address, e = 0; i < address + 6; i++, e++){
    EEPROM.write( toSave[ e ], i+1 );
    delay( 25 ); 
  }    
  delay(300);
}

//Método utilizado para eliminar un estado con las posiciones de los motores del Brazo Robótico
void deleteStatus(){  
  if( statusSize > 0 ){
    byte address = statusSize * 5;
    for(byte i = address; i < address + 5; i++){
      EEPROM.write( 255, i+1 );
    }
    updateStatusSize( --statusSize );
  }  
}

//Método utilizado para obtener un estado con las posiciones deseadas en los 5 motores del Brazo Robótico
void getStatus(byte position){
    byte address = position * 5;
    Serial.println("[Charged status]");
    for(byte i = address, e = 0; i < address+ 6; i++, e++){
      status[e] = EEPROM.read( i+1 );
      Serial.print(status[e]);
      Serial.print(",");
      delay( 25 );
    }
    Serial.println("");
    delay( 250 );
}

/** 
 *  @author Juda Alector
 *  @since Nov 13, 2018
 *  @desc Actualiza en la memoria EEPROM la 
 *        cantidad de status guardados.
 *  @param ( newSize ) Es el nuevo valor para la cantidad 
 *        de estados guardados en EEPROM.
 */
 
//Método utilizado para actualizar en la memoria EEPROM la cantidad de estados guardados
void updateStatusSize( byte newSize ){
  EEPROM.write( newSize, addStatusSize );
}

/** 
 *  @author Juda Alector
 *  @since Nov 13, 2018
 *  @desc Ayuda a saber la cantidad de estados que están
 *        guardados en la memoria.
 */

//Método utilizado para obtener la cantidad de estados que están guardados en la memoria EEPROM
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

//Método utilizado para poner en alto los bits de la memoria EEPROM
//Recibe un valor de 0 a 255 que nos permmite borrar bloques de 5 en 5 en la memoria.
//Ejem: -Sï recibe un 4 se borrarán 20 bytes de la memoria
//      -Si recibe un 5 se borrarán 25 bytes de la memoria

//IMPORTANTE: Este método sólo debe usarse cuando se quiera borrar los datos de la memoria
//Sí se manda llamar constantemente los datos no se guardarán como se espera
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
//Método utilizado para mover las bobinas del motor a pasos dependiendo del número de paso recibido
void setOutput(int step)
{
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}

//Método utilizado para controlar la interrupción mediante el botón de paro de emergencia
void interruption(){
  //Si la variable está en false cambia a true y viceversa, para revertir el estado actual
  stopped = !stopped;
  Serial.println("Interrumpido");
}
