// -*- mode: c++ -*-

// --------------------------------------------------------------
// Arnau Soler Tomás
// 2023-09-25
// --------------------------------------------------------------

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
// --------------------------------------------------------------
class Publicador {

    // -------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
  private:

    uint8_t beaconUUID[16] = {
      'E', 'P', 'S', 'G', '-', 'G', 'T', 'I',
      '-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
    };

    // -------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
  public:
    EmisoraBLE laEmisora {
      "GTI-PROY-3A-ARNAU", //  nombre emisora
      0x004c, // fabricanteID (Apple)
      4 // txPower
    };

    const int RSSI = -55; // por poner algo, de momento no lo uso

    // -------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
  public:

    // -------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
    enum MedicionesID  {
      CO2 = 11,
      TEMPERATURA = 12,
      RUIDO = 13
    };

    // -------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
    Publicador( ) {
      // ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
      // Pondremos un método para llamarlo desde el setup() más tarde
    } // ()

    // -------------------------------------------------------------------------------------------------------------
    // --> encenderEmisora()
    // Descripción: Literalmente, enciende la Emisora
    // -------------------------------------------------------------------------------------------------------------
    void encenderEmisora() {
      (*this).laEmisora.encenderEmisora();
    } // ()

// -------------------------------------------------------------------------------------------------------------
// valorCO2:N, contador:N, tiempoEspera:long --> publicarCO2()
// Descripción: Emite un anuncio con un determinado valor de CO2, un contador y, tras un tiempo determinado,
// detenemos el anuncio
// -------------------------------------------------------------------------------------------------------------
    void publicarCO2( int16_t valorCO2, uint8_t contador, long tiempoEspera ) {

      //
      // 1. empezamos anuncio
      //
      uint16_t major = (MedicionesID::CO2 << 8) + contador;
      (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID,
                                              major, // major
                                              valorCO2, // minor
                                              (*this).RSSI // rssi
                                            );
      //
      // 2. esperamos el tiempo que nos digan
      //
      esperar( tiempoEspera );

      //
      // 3. paramos anuncio
      //
      (*this).laEmisora.detenerAnuncio();
    } // ()

// -------------------------------------------------------------------------------------------------------------
// valorTemperatura:N, contador:N, tiempoEspera:long --> publicarTemperatura()
// Descripción: Método de la clase Publicador que sirve para publicar un anuncio, con la temperatura y un
// contador, que durará un determinado tiempo
// -------------------------------------------------------------------------------------------------------------
    void publicarTemperatura( int16_t valorTemperatura,
                              uint8_t contador, long tiempoEspera ) {

      uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;
      (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID,
                                              major, // major
                                              valorTemperatura, // minor
                                              (*this).RSSI // rssi
                                            );
      esperar( tiempoEspera );

      (*this).laEmisora.detenerAnuncio();
    } // ()

}; // class

#endif
