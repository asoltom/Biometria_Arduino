// -*- mode: c++ -*-

// ----------------------------------------------------------
// Arnau Soler Tomás
// 2023-09-25
// ----------------------------------------------------------
#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------
// ----------------------------------------------------
#include <vector>

// -------------------------------------------------------------------------------------------------------------
// alReves() utilidad
// pone al revés el contenido de una array en el mismo array
// -------------------------------------------------------------------------------------------------------------
template< typename T >
T *  alReves( T * p, int n ) {
  T aux;

  for ( int i = 0; i < n / 2; i++ ) {
    aux = p[i];
    p[i] = p[n - i - 1];
    p[n - i - 1] = aux;
  }
  return p;
} // ()

// -------------------------------------------------------------------------------------------------------------
// pString:<char>, pUint:<N>, tamMax:N --> stringAUint8AlReves() --> pUint:<N>
// Descripción: Método que nos sirve para cambiar los valores de una lista de tipo String a una lista de
// números enteros, ambas usando punteros con los que referenciar a las listas y un tamaño máximo
// -------------------------------------------------------------------------------------------------------------
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

  int longitudString =  strlen( pString );
  int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );
  // copio nombreServicio -> uuidServicio pero al revés
  for ( int i = 0; i <= longitudCopiar - 1; i++ ) {
    pUint[ tamMax - i - 1 ] = pString[ i ];
  } // for

  return pUint;
} // ()

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------
class ServicioEnEmisora {

  public:

    using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
                                          BLECharacteristic * chr,
                                          uint8_t * data, uint16_t len);
// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------
    class Caracteristica {
      private:
        uint8_t uuidCaracteristica[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
          // least signficant byte, el primero
          '0', '1', '2', '3',
          '4', '5', '6', '7',
          '8', '9', 'A', 'B',
          'C', 'D', 'E', 'F'
        };

        //
        //
        //
        BLECharacteristic laCaracteristica;

      public:

// -------------------------------------------------------------------------------------------------------------
// Constructor
// nombreCaracteristica_:char --> Caracteristica() --> laCaracteristica:Caracteristica
// -------------------------------------------------------------------------------------------------------------
        Caracteristica( const char * nombreCaracteristica_ )
          :
          laCaracteristica( stringAUint8AlReves( nombreCaracteristica_, &uuidCaracteristica[0], 16 ) )
        {

        } // ()

// -------------------------------------------------------------------------------------------------------------
// Constructor
// nombreCaracteristica_:char, props:N, permisoRead:SecureMode_t, permisoWrite:SecureMode_t,
// tam:N --> Caracteristica()
// -------------------------------------------------------------------------------------------------------------
        Caracteristica( const char * nombreCaracteristica_ ,
                        uint8_t props,
                        SecureMode_t permisoRead,
                        SecureMode_t permisoWrite,
                        uint8_t tam )
          :
          Caracteristica( nombreCaracteristica_ ) // llamada al otro constructor
        {
          (*this).asignarPropiedadesPermisosYTamanyoDatos( props, permisoRead, permisoWrite, tam );
        } // ()

      private:
// -------------------------------------------------------------------------------------------------------------
// CHR_PROPS_WRITE , CHR_PROPS_READ ,  CHR_PROPS_NOTIFY
// -------------------------------------------------------------------------------------------------------------
// props:N --> asignarPropiedades()
// Descripción: Nos permite asignar propiedades
// -------------------------------------------------------------------------------------------------------------
        void asignarPropiedades ( uint8_t props ) {
          (*this).laCaracteristica.setProperties( props );
        } // ()

// -------------------------------------------------------------------------------------------------------------
// SecureMode_t::SECMODE_OPEN  , SecureMode_t::SECMODE_NO_ACCESS
// -------------------------------------------------------------------------------------------------------------
// permisoRead:SecureMode_t, permisoWrite:SecureMode_t --> asignarPermisos()
// Descripción: Nos permite asignar permisos de lectura y escritura
// -------------------------------------------------------------------------------------------------------------
        void asignarPermisos( SecureMode_t permisoRead, SecureMode_t permisoWrite ) {
          // no puedo escribir AUN si el constructor llama a esto: Serial.println( "laCaracteristica.setPermission( permisoRead, permisoWrite ); " );
          (*this).laCaracteristica.setPermission( permisoRead, permisoWrite );
        } // ()

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------
        void asignarTamanyoDatos( uint8_t tam ) {
          // no puedo escribir AUN si el constructor llama a esto: Serial.print( " (*this).laCaracteristica.setFixedLen( tam = " );
          // no puedo escribir AUN si el constructor llama a esto: Serial.println( tam );
          // (*this).laCaracteristica.setFixedLen( tam );
          (*this).laCaracteristica.setMaxLen( tam );
        } // ()

      public:
// -------------------------------------------------------------------------------------------------------------
// props:N, permisoRead:SecureMode_t, permisoWrite:SecureMode_t, tam:N --> asignarPropiedadesPermisosYTamanyoDatos()
// Descripción: Una función conjunta de las anteriores (en realidad, las llama) con la que podemos
// asignar propiedades, permisos de Lectura y Escritura y tamaño de datos
// -------------------------------------------------------------------------------------------------------------
        void asignarPropiedadesPermisosYTamanyoDatos( uint8_t props,
            SecureMode_t  permisoRead,
            SecureMode_t permisoWrite,
            uint8_t tam ) {
          asignarPropiedades( props );
          asignarPermisos( permisoRead, permisoWrite );
          asignarTamanyoDatos( tam );
        } // ()


// -------------------------------------------------------------------------------------------------------------
// str:char --> escribirDatos()
// Descripción: Método que nos permite escribir datos de tipo Char por Pantalla
// -------------------------------------------------------------------------------------------------------------
        uint16_t escribirDatos( const char * str ) {
          // Serial.print( " return (*this).laCaracteristica.write( str  = " );
          // Serial.println( str );

          uint16_t r = (*this).laCaracteristica.write( str );

          // Serial.print( ">>>Escritos " ); Serial.print( r ); Serial.println( " bytes con write() " );

          return r;
        } // ()

// -------------------------------------------------------------------------------------------------------------
// str:char --> notificarDatos() --> r:N
// Descripción: Método que nos permite Notificar los Datos obtenidos
// Nota: 'r' significa 'res' o 'resultado'. Por si acaso
// -------------------------------------------------------------------------------------------------------------
        uint16_t notificarDatos( const char * str ) {

          uint16_t r = laCaracteristica.notify( &str[0] );

          return r;
        } //  ()

// -------------------------------------------------------------------------------------------------------------
// cb:callback --> instalarCallbackCaracteristicaEscrita()
// Descripción: función que sirve como callback de la Característica
// -------------------------------------------------------------------------------------------------------------
        void instalarCallbackCaracteristicaEscrita( CallbackCaracteristicaEscrita cb ) {
          (*this).laCaracteristica.setWriteCallback( cb );
        } // ()

// -------------------------------------------------------------------------------------------------------------
// --> activar()
// Descripción: Método que nos sirve para 'activar'
// -------------------------------------------------------------------------------------------------------------
        void activar() {
          err_t error = (*this).laCaracteristica.begin();
          Globales::elPuerto.escribir(  " (*this).laCaracteristica.begin(); error = " );
          Globales::elPuerto.escribir(  error );
        } // ()

    }; // class Caracteristica

  private:

    uint8_t uuidServicio[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
      // least signficant byte, el primero
      '0', '1', '2', '3',
      '4', '5', '6', '7',
      '8', '9', 'A', 'B',
      'C', 'D', 'E', 'F'
    };

    //
    //
    //
    BLEService elServicio;

    //
    //
    //
    std::vector< Caracteristica * > lasCaracteristicas;

  public:

// -------------------------------------------------------------------------------------------------------------
// nombreServicio_: char --> ServicioEnEmisora()
// Descripción: Inicializa el Servicio de la Emisora mediante un nombre (nombreServicio_)
// -------------------------------------------------------------------------------------------------------------
    ServicioEnEmisora( const char * nombreServicio_ )
      :
      elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) )
    {

    } // ()

// -------------------------------------------------------------------------------------------------------------
// --> escribeUUID()
// Descripción: Método que sirve para escribir la UUID por pantalla
// -------------------------------------------------------------------------------------------------------------
    void escribeUUID() {
      Serial.println ( "**********" );
      for (int i = 0; i <= 15; i++) {
        Serial.print( (char) uuidServicio[i] );
      }
      Serial.println ( "\n**********" );
    } // ()

// -------------------------------------------------------------------------------------------------------------
// car:Caracteristica --> anyadirCaracteristica()
// Descripción: añade una caracterísitca a la lista de Características
// -------------------------------------------------------------------------------------------------------------
    void anyadirCaracteristica( Caracteristica & car ) {
      (*this).lasCaracteristicas.push_back( & car );
    } // ()

// -------------------------------------------------------------------------------------------------------------
// --> activarServicio()
// Ddescripción: Srive para activar el Servicio
// -------------------------------------------------------------------------------------------------------------
    void activarServicio( ) {
      // entiendo que al llegar aquí ya ha sido configurado
      // todo: características y servicio

      err_t error = (*this).elServicio.begin();
      Serial.print( " (*this).elServicio.begin(); error = " );
      Serial.println( error );

      for ( auto pCar : (*this).lasCaracteristicas ) {
        (*pCar).activar();
      } // for

    } // ()

    // -------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
    operator BLEService&() {
      // "conversión de tipo": si pongo esta clase en un sitio donde necesitan un BLEService
      return elServicio;
    } // ()

}; // class

#endif
