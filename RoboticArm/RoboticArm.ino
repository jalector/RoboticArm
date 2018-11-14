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
    
}

void deleteStatus(){
  
}

void getStatus(byte position){
    for(byte i = position, e = 0; i < position + 5; i++, e++){
      status[e] = EEPROM.read( i );
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
void updateStatus( byte newSize ){
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
