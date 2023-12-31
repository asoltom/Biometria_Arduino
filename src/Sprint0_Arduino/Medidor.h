// -*- mode: c++ -*-

// --------------------------------------------------------------
// Arnau Soler Tomás
// 2023-09-25
// --------------------------------------------------------------

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

// ------------------------------------------------------
// ------------------------------------------------------
class Medidor {

    // -------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
  private:

  public:

    // -------------------------------------------------------------------------------------------------------------
    // constructor
    // Descripción: Constructor vacio
    // -------------------------------------------------------------------------------------------------------------
    Medidor() {
    } // ()

    // -------------------------------------------------------------------------------------------------------------
    // --> iniciarMedidor()
    // Descripción: esta función servirá para iniciar el Medidor
    // -------------------------------------------------------------------------------------------------------------
    void iniciarMedidor() {
      // las cosas que no se puedan hacer en el constructor, if any
    } // ()

    // -------------------------------------------------------------------------------------------------------------
    // --> medirCO2() --> medidaCO2:N
    // -------------------------------------------------------------------------------------------------------------
    int medirCO2() {
      return 235;
    } // ()

    // -------------------------------------------------------------------------------------------------------------
    // --> medirTemperatura() --> temp
    // Descripción: En futuros Sprints, esta función devolverá la temperatura
    // -------------------------------------------------------------------------------------------------------------
    int medirTemperatura() {
      return -12; // qué frío !
    } // ()

}; // class

#endif
