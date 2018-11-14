 #include <EEPROM.h>
 
/** Dirección dónde se guarda la cantidad de estados guardados */
unsigned char addStatusSize = 0;

/** Este arreglo contiene la posisicón de cada motor*/
byte status[5];
/** variable que ayuda a conocer la cantidad de estados */
byte statusSize;

void setup() {
  /** Se inicializa la cantidad de estados guardados*/
  statusSize = getStatusSize();

}

void loop() {
  // put your main code here, to run repeatedly:

}



void saveStatus(){
  updateStatusSize( +statusSize );
  byte address = statusSize * 5;
  for(byte i = address, e = 0; i < address + 5; i++, e++){
    EEPROM.write( status[ e ], i+1 );
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
byte getStatusSize(){
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
