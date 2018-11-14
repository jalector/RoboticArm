
/*
 * Juda Alector
 * Nov 11, 2018
 * Práctica de prueba para manejo de memoria EEPROM.
*/


/* Biblioteca para manejar servos */
#include <Servo.h>
/* 
    Biblioteca para manejar memoria EEPROM. La capacidad
  para manejar la memoria EEPROM es de 1024b dado el caso se puede
  manejar 1024 datos individualmente.
*/
#include <EEPROM.h>

/* Objeto que maneja el servo*/
Servo servo1;

/* 
    
    Frame, ayuda a saber un frame relativo a sí esta activo
  en forma automática o no. Su rango va de 0 a 180, esto se 
  usa para dar de forma automática un angulo al servo y a su
  vez se apolla de canGrow para saber en que dirección va.   
*/
int frame = 0;
boolean canGrow = true;
/* 
    Sí el servo está en forma automática esta variable esta en 
  bajo. Al estar en estado bajo el servo tomará como angulo cada
  frame que se le dé; y al estar en alto esperará que se le den 
  ordenes para darle estados que estén previamente guardados en
  la memoria EEPROM.
*/
boolean manuela = false;

/* Posición actual del servo */
int sPosition = 0;

void setup() {
  Serial.begin(9600);
  /* Se identifica en que pin esta el servo*/
  servo1.attach(3);
  /* Inicializamos el servo en 0, cómo todo buen valedor ;)*/
  frame = getStatus( 'a' );
  servo1.write( frame );
  delay(500);
  Serial.println("Started");
}



void loop() {
    if( Serial.available() > 0){
      int character = Serial.read();
      Serial.print("Read: ");
      Serial.println( (char) character );      
      
      /*Identificamos un rango de 'a' a 'f' para 
          los estados que se pueden guardar.*/ 
      if( character >= 'a'  && character <= 'f'){
        /* Sí se está en modo manual se pueden obtener
        los estados guardados, de no estar guardados 
        se coloca un 0*/
        if( manuela ) {
          /* De ser la letra f el servo toma la posición
          0 (para comenzar a hacer pruebas)*/
          if( character == 'f') sPosition = 0;
          /*De ser diferente se obtiene el estado que 
          se pueda utilizar para la posición del servo*/
          else sPosition = getStatus( character );          
        }else {
          /*De ser automático se guarda la posición actual
          en la posición del caracter leído, esto va de:
            a => 97            b => 98
            c => 99            d => 100
            e => 101
          Se debe tomar en concideración que se pudieron 
          guardar desde la posición 0*/
          setStatus(character, sPosition);
        }
      }else if (character == 'm'){
        /*De ser 'm' el caracter leído, se cambia de modo
        automatico a manualy biseversa.*/
        manuela = !manuela;
      }  
    }   
    /* Sí estámos en modo automatico el servo tomará los valores
    del frame en curso.*/
    if( !manuela ){            
      if( canGrow ){
        if( ++frame == 180 ) canGrow = false;
      } else {
        if( --frame == 0 ) canGrow = true;
      }
      sPosition = frame; 
    }
    /* Se escriben los datos en el servo*/
    servo1.write( sPosition );      
    delay(10);      
}

/*  ###### Para la actividad del brazo se debería conciderar ######
    Se debe prepara para que la capacidad máxima de estados
  guardados sean sólo 5, para no batallar mucho al momento de
  leer y escribir los datos ya que se escriben uno a uno. 

    Al momento de escribir los datos se apartará la primera posición
  de la memoria EEPROM como el número que determinará la cantidad de 
  estados que podremos leer. De esa forma sí tenemos 5 estados sabremos
  que tenemos que leer 25 direcciones de la memoria EEPROM. 

    Para cada dirección de la memoria EEPROM sólo se pueden guardar 
  1 byte y la memoria EEPROM soporta sólo 1kb de información. 
*/
int getStatus( int address ){
  int answer = EEPROM.read( address );
  Serial.print("Get position [");
  Serial.print( answer);
  Serial.print("] in ");
  Serial.println( address ); 
  return (answer == 255)? 0 : answer;
}

void setStatus( int address, int sPosition ){
  Serial.print("Set position [");
  Serial.print( sPosition );
  Serial.print("] in ");
  Serial.println( address ); 
  EEPROM.write(address, sPosition);
}
