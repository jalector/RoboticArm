Brazo Robótico de 5 Ejes
========================

Autores
-------
* Ornelas Pérez Luis Saul
* Paniagua Soto Rafael
* Vallejo Herrera Juda Alector

Descripción de la Práctica
--------------------------

El propósito de esta práctica es desarrollar paso a paso un proyecto para controlar y programar
un Brazo Robot, simulando las funciones básicas de un robot industrial.

### Funciones básicas:

1. Programar: Registrar las posiciones de los brazos en tres dimensiones (cada registro es un "paso",
un programa consiste en una serie de pasos).

2. Ejecutar: Realice en secuencia las posiciones registradas en el "Programa". El robot ejecutará
el programa hasta que se use el comando "ABORTAR".

### Características principales:

El proyecto se usa para controlar robots con  5 DOF ("Grados de libertad").
El robot se controla en modo "REMOTO" (a través de una programa en java por medio del puerto serial).
La información para el usuario se proporciona a través de LEDS de colores.
Contiene un botón de paro de emergencia (Físico).
Si existe un fallo y/o corte de energía, después de restablecerse la corriente el robot
continúa el programa (aunque este no se encuentre conectado a la aplicación).
    
Los brazos robóticos se pueden clasificar de acuerdo con el número de "articulaciones"
o "Grados de libertad" (DOF) que tienen.
-La "Base", o "Cintura", puede girar el brazo 360°, se utiliza un motor a pasos.
-El "Hombro" es el responsable de "levantar o bajar" el brazo verticalmente
-El "codo" hace que el brazo "avance o retroceda".
-La Muñeca hace que “gire” la Pinza.
-La "Garra" o "Pinza" funciona abriendo o cerrándose para "agarrar cosas".

![Imagen](EjemploBrazo.PNG)

Material
--------
### Hardware

* 1 Arduino UNO
* 1 Protoboard
* 1 Chasis de Brazo Robótico con 5 Grados de Libertad
* 4 Servomotores
* 1 Motor a Pasos
* 1 Módulo Controlador del Motor a Pasos (Puente H)
* 2 Leds de Colores
* 3 Resistencias de 330 Ohms
* 1 Teclado Matricial
* 1 Push Button
* Cables conectores

### Software
* IDE Arduino
* IDE Netbeans
* Lenguaje de programación Java

Especificaciones técnicas del equipo
------------------------------------
* Sistema Operativo: Ubuntu 16.04
* Procesador: AMD Radeon R2
* Memoria RAM: 8 GB

Resultados de la Práctica
-------------------------
### Armado del circuito



### Pruebas