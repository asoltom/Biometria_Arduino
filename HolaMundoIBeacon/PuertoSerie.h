// -*- mode: c++ -*-

// ----------------------------------------------------------
// Arnau Soler Tomás
// 2023-09-25
// ----------------------------------------------------------

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

// ----------------------------------------------------------
// ----------------------------------------------------------
class PuertoSerie  {

  public:
// -------------------------------------------------------------------------------------------------------------
// Inicializador del Puerto Serie
// baudios:long --> PuertoSerie()
// -------------------------------------------------------------------------------------------------------------
    PuertoSerie (long baudios) {
      Serial.begin( baudios );
      // mejor no poner esto aquí: while ( !Serial ) delay(10);
    } // ()

// -------------------------------------------------------------------------------------------------------------
// --> esperarDisponible()
// Descripción: Método de la clase PuertoSerie que permite esperar (hacer un delay de) 10 milisegundos
// -------------------------------------------------------------------------------------------------------------
    void esperarDisponible() {

      while ( !Serial ) {
        delay(10);
      }

    } // ()

// -------------------------------------------------------------------------------------------------------------
// mensaje:T --> escribir()
// Descripción: Un método que se resume en que hace un 'print' del mensaje que le demos.
// Es decir, escribir en pantalla el mensaje que le demos
// -------------------------------------------------------------------------------------------------------------
    template<typename T>
    void escribir (T mensaje) {
      Serial.print( mensaje );
    } // ()

}; // class PuertoSerie

#endif
