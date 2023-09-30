// -*-c++-*-

// --------------------------------------------------------------
// Arnau Soler Tomás
// 2023-09-25
// --------------------------------------------------------------

#include <bluefruit.h>

#undef min
#undef max

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

PuertoSerie elPuerto ( /* velocidad = */ 115200 ); // 115200 o 9600 o ...
};

// --------------------------------------------------------------
// Librerias
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"
// --------------------------------------------------------------
// --------------------------------------------------------------

//Al ver el namespace Globales duplicado en un inicio, pense en unificarlos,
//es decir, poner las variables Publicador elPublicador y Medidor elMedidor
//junto a las del otro. Pero daba error en la clase EmisoraBLE.h
//Al final, por razones de Arduino, se debe quedar así, "duplicado".

namespace Globales {

  Publicador elPublicador;

  Medidor elMedidor;

}; // namespace

// --------------------------------------------------------------
// setup()
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.esperarDisponible();

  Globales::elPublicador.encenderEmisora();

  //Globales::elMedidor.iniciarMedidor();

  //
  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
// --------------------------------------------------------------
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 1000 ); // 1000 encendido
  esperar ( 1000 ); //  100 apagado
} // ()

// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
uint8_t cont = 0;
};

void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );


  lucecitas();

  // --------------------------------------
  // mido y publico el valor de CO2
  // --------------------------------------
  int valorCO2 = elMedidor.medirCO2();

  elPublicador.publicarCO2( valorCO2,
                            cont,
                            1000 // intervalo de emisión
                          );

  // --------------------------------------
  // mido y publico el valor de Temperatura
  // --------------------------------------
  int valorTemperatura = elMedidor.medirTemperatura();

  elPublicador.publicarTemperatura( valorTemperatura,
                                    cont,
                                    1000 // intervalo de emisión
                                  );

  // -----------------------------------------------------------
  // prueba para emitir un iBeacon y poner
  // en la carga (21 bytes = uuid 16 major 2 minor 2 txPower 1 )
  // lo que queramos (sin seguir dicho formato)
  //
  // Al terminar la prueba hay que hacer Publicador::laEmisora privado
  // -----------------------------------------------------------
  char datos[21] = {
    'E', 's', 't', 'a',   // --------
    ' ', 'e', 's', ' ',   // - UUID -
    'm', 'i', ' ', 'U',   // -      -
    'U', 'I', 'D', '.',   // --------
    'M', 'j', 'M', 'n',   // major, minor
    'T'                   // txPower
  };

  elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( &datos[0], 21 );
  // elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( "MolaMolaMolaMolaMolaM", 21 );

  esperar( 2000 );

  elPublicador.laEmisora.detenerAnuncio();

  //
  //
  //
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );

} // loop ()
