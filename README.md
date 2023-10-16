# Biometria_Arduino
Repositorio del proyecto de biometría para Arduino

## Descripción

Este proyecto de Arduino emite iBeacons mediante un dispositivo Adafruit empleando el estandar IEEE 802.15.1 también conocido como Bluetooth. Concretamente Bluetooth LE

## Instalación

Se debe instalar Arduino para poder ejecutar el código. Preferiblemente la 1.8.19 que es la que se ha usado para desarrollar este proyecto.

Se debe descargar/clonar el repositorio.

Importante realizar los siguientes pasos para que Arduino soporte el módulo Sparkfun Pro nRF82540 mini

## Pasos para configurar:

1. Instalar soporte para placas basadas en nRF52. Esta extensión ha sido desarrollado por su competidor (Adafruit) y es genérica.

En File->Preferences->Additional boards manager URLs debes escribir:

https://adafruit.github.io/arduino-board-index/package_adafruit_index.json

2. Seguir las instrucciones de este link desde el apartado "Installing the Arduino Core for nRF52 Boards"

link: https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

3. En un momento te descargaras un .zip o un .rar
Necesitas ir a %LOCALAPPDATA%\Arduino15\packages\adafruit\hardware\nrf52\ 
Entonces descomprimes y le dices que sí a remplazar todo lo que te pida

4. Sigue con las instrucciones del link por donde te habías quedado.

Dale al Ctrl + F y busca con esta linea:
"Then open boards.txt. Scroll to the bottom and paste the below into the bottom of that file:"

5. Cuando termines, reinicia Arduino

6. Selecciona la placa nueva

<span>![</span><span>Imagen-Paso 6-Pasos para configurar el módulo Sparkfun Pro nRF82540 mini</span><span>]</span><span>(</span><span>https://raw.githubusercontent.com/asoltom/Biometria_Arduino/main/Sprint 0 - Individual/Arduino/docs/Imagen-Placa Sparkfun Pro.jpg</span><span>)</span>

## Uso:

1. Inicie Arduino
2. Asegurese de haber instalado todo correctamente.
3. Seleccione el módulo.
4. Seleccione el puerto de salida.
5. Situese en el archivo con la extensión .ino
6. Haga click en la flecha hacia la derecha situada en la zona superior izquierda para "subir" (cargar) el archivo.ino
7. Una vez haya terminado, haga click en la lupa situada en la zona superior derecha para abrir la consola

Una vez hecho todo esto, con una aplicación como BeaconScope o NRF Connect en su teléfono móvil, podrá comprobar que se estén emitiendo iBeacons.
También puede usar el Logcat en caso de usar el código en el Repositorio Biometria_Android

## Cambio de registro:

En el archivo Sprint0_Arduino, en la línea 125, hay un enumerador con unos valores por defecto para CO2, Temperatura y el tiempo de espera
En el archivo Publicador.h, en la línea 28, puede cambiar el nombre de la emisora
En la línea 29, el id del fabricante



