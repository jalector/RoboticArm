Brazo Rob�tico de 5 Ejes
========================

Autores
-------
* Ornelas P�rez Luis Saul
* Paniagua Soto Rafael
* Vallejo Herrera Juda Alector

Descripci�n de la Pr�ctica
--------------------------

El prop�sito de esta pr�ctica es desarrollar paso a paso un proyecto para controlar y programar
un Brazo Robot, simulando las funciones b�sicas de un robot industrial.

### Funciones b�sicas:

1. Programar: Registrar las posiciones de los brazos en tres dimensiones (cada registro es un "paso",
un programa consiste en una serie de pasos).

2. Ejecutar: Realice en secuencia las posiciones registradas en el "Programa". El robot ejecutar�
el programa hasta que se use el comando "ABORTAR".

### Caracter�sticas principales:

El proyecto se usa para controlar robots con  5 DOF ("Grados de libertad").
El robot se controla en modo "REMOTO" (a trav�s de una programa en java por medio del puerto serial).
La informaci�n para el usuario se proporciona a trav�s de LEDS de colores.
Contiene un bot�n de paro de emergencia (F�sico).
Si existe un fallo y/o corte de energ�a, despu�s de restablecerse la corriente el robot
contin�a el programa (aunque este no se encuentre conectado a la aplicaci�n).
    
Los brazos rob�ticos se pueden clasificar de acuerdo con el n�mero de "articulaciones"
o "Grados de libertad" (DOF) que tienen.
-La "Base", o "Cintura", puede girar el brazo 360�, se utiliza un motor a pasos.
-El "Hombro" es el responsable de "levantar o bajar" el brazo verticalmente
-El "codo" hace que el brazo "avance o retroceda".
-La Mu�eca hace que �gire� la Pinza.
-La "Garra" o "Pinza" funciona abriendo o cerr�ndose para "agarrar cosas".

![Imagen](EjemploBrazo.PNG)

Material
--------
### Hardware

* 1 Arduino UNO
* 1 Protoboard
* 1 Chasis de Brazo Rob�tico con 5 Grados de Libertad
* 4 Servomotores
* 1 Motor a Pasos
* 1 M�dulo Controlador del Motor a Pasos (Puente H)
* 2 Leds de Colores
* 3 Resistencias de 330 Ohms
* 1 Teclado Matricial
* 1 Push Button
* Cables conectores

### Software
* IDE Arduino
* IDE Netbeans
* Lenguaje de programaci�n Java

Especificaciones t�cnicas del equipo
------------------------------------
* Sistema Operativo: Ubuntu 16.04
* Procesador: AMD Radeon R2
* Memoria RAM: 8 GB

Resultados de la Pr�ctica
-------------------------
### Armado del circuito



### Pruebas