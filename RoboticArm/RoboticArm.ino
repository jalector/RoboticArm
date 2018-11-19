#include <EEPROM.h>


/** Dirección dónde se guarda la cantidad de estados guardados */
unsigned char addStatusSize = 0;

/** Este arreglo contiene la posisicón de cada motor*/
byte status[5];
/** variable que ayuda a conocer la cantidad de estados */
byte statusSize;

String data = "";
void setup() {
  /** Se inicializa la cantidad de estados guardados*/
  statusSize = getStatusSize();
  Serial.begin( 9600 );
}
/**
 * Variables que ayudan a manejar la posición
 * de cada servo junto también la posición de 
 * la base (el motor a pasos).
*/
byte pasos = 0;
byte shoulder = 130;
byte elbow = 50;
byte wrist = 90;
byte hand = 0;

/**
 * Varianle que nos ayuda a saber sí es vamos a 
 * manejar el brazo con los estados o bien con el
 * teclado matricial
*/
boolean manual = false;
boolean parar = false;
void loop() {
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
