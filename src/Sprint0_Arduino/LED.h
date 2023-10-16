// -*- mode: c++ -*-

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

// ----------------------------------------------------------
// Arnau Soler Tomás
// 2023-09-25
// ----------------------------------------------------------

// ----------------------------------------------------------
// tiempo:long --> esperar()
// ----------------------------------------------------------
void esperar (long tiempo) {
  delay (tiempo);
}

// ----------------------------------------------------------
// ----------------------------------------------------------
class LED {
  private:
    int numeroLED;
    bool encendido;
  public:

// -------------------------------------------------------------------------------------------------------------
// numero: N --> Led()
// Descripción: Constructor de la clase LED
// -------------------------------------------------------------------------------------------------------------
    LED (int numero)
      : numeroLED (numero), encendido(false)
    {
      pinMode(numeroLED, OUTPUT);
      apagar ();
    }

// -------------------------------------------------------------------------------------------------------------
// --> encender() --> encendido:V
// Descripción: Método de la clase LED que apaga el LED al poner el valor de la variable encendido en "true"
// -------------------------------------------------------------------------------------------------------------
    void encender () {
      digitalWrite(numeroLED, HIGH);
      encendido = true;
    }

// -------------------------------------------------------------------------------------------------------------
// --> apagar() --> encendido:F
// Descripción: Método de la clase LED que apaga el LED al poner el valor de la variable encendido en "false"
// -------------------------------------------------------------------------------------------------------------
    void apagar () {
      digitalWrite(numeroLED, LOW);
      encendido = false;
    }

// -------------------------------------------------------------------------------------------------------------
// --> alternar() --> encendido:VoF
// Descripción: Método de la clase LED que alterna el estado de la variable encendido. Es decir, si el valor
// era true, lo pone en false y viceversa
// -------------------------------------------------------------------------------------------------------------
    void alternar () {
      if (encendido) {
        apagar();
      } else {
        encender ();
      }
    } // ()

// -------------------------------------------------------------------------------------------------------------
// tiempo:long --> brillar()
// Descripción: Método de la clase LED que mediante un determinado tiempo, va haciendo brillar el LED
// -------------------------------------------------------------------------------------------------------------
    void brillar (long tiempo) {
      encender ();
      esperar(tiempo);
      apagar ();
    }
}; // class

#endif
