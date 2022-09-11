#include <Arduino.h>

// *******************************************************************
// ********************** PROGRAMAS **********************************
//
// {k1,k2,k3,k4,k5,k6,0,0}  (10 segundos)
//  |  |  |  |  |  |    |_ beep
//  |  |  |  |  |  |
//  |  |  |  |  |  |______ llenado
//  |  |  |  |  |_________ vaciado
//  |  |  |__|____________ centrifugado
//  |  |__________________ motor izquierda
//  |_____________________ alimentacion motor
//

 byte PROG_K[] = {

   // 10 seg vaciado y llenado
   B00001100,

   // 1 minutos llenado
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,

   // 2 minuto lavado
   B10000100,
   B00000100,
   B00000100,
   B11000100,
   B00000100,
   B00000100,
   B10000100,
   B00000100,
   B00000100,
   B11000100,
   B00000100,
   B00000100,

   // 15 minutos espera
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,

   // 2 minutos lavado
   B10000000,
   B00000000,
   B00000000,
   B11000000,
   B00000000,
   B00000000,
   B10000000,
   B00000000,
   B00000000,
   B11000000,
   B00000000,
   B00000000,

   // 2 minutos vaciado
   B10001001,
   B00001000,
   B00001000,
   B11001000,
   B00001000,
   B00001000,
   B10001000,
   B00001000,
   B00001000,
   B11001000,
   B00001000,
   B00001000,

   // 3 minutos llenado
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B10000100,
   B00000100,
   B00000100,
   B11000100,
   B00000100,
   B00000100,

   // 2 minutos vaciado
   B10001000,
   B00001000,
   B00001000,
   B11001000,
   B00001000,
   B00001000,
   B10001000,
   B00001000,
   B00001000,
   B11001000,
   B00001000,
   B00001000,

   // 3 minutos llenado
   B10000100,
   B00000100,
   B00000100,
   B11000100,
   B00000100,
   B00000100,
   B10000100,
   B00000100,
   B00000100,
   B11000100,
   B00000100,
   B00000100,
   B10000100,
   B00000100,
   B00000100,
   B11000100,
   B00000100,
   B00000100,

   // 2 minutos vaciado
   B10001000,
   B00001000,
   B00001000,
   B11001000,
   B00001000,
   B00001000,
   B10001000,
   B00001000,
   B00001000,
   B11001000,
   B00001000,
   B00001000,

   // 2 minutos centrifugado vaciado
   B10111000,
   B10111000,
   B10111000,
   B10111000,
   B10111000,
   B10111000,
   B10111000,
   B10111000,
   B10111000,
   B10111000,
   B10111000,
   B10111000,

   // 1 minuto
   B00001000,
   B00001000,
   B00001000,
   B00001000,
   B00001001,
   B00001001
   

 };


 byte PROG_E[]  = {

  // 2 minutos vaciado
  B10001000,
  B00001000,
  B00001000,
  B11001000,
  B00001000,
  B00001000,
  B10001000,
  B00001000,
  B00001000,
  B11001000,
  B00001000,
  B00001000,

  // 3 minutos centrifugado vaciado
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,

  // 1 minutos
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001001,
  B00001001,

};


 byte PROG_D[]  = {

  // 2 minutos vaciado
  B10001001,
  B00001000,
  B00001000,
  B11001000,
  B00001000,
  B00001000,
  B10001000,
  B00001000,
  B00001000,
  B11001000,
  B00001000,
  B00001000,

  // 3 minutos llenado
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,


  // 7 minutos enjuague
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,

  // 2 minutos vaciado
  B10001000,
  B00001000,
  B00001000,
  B11001000,
  B00001000,
  B00001000,
  B10001000,
  B00001000,
  B00001000,
  B11001000,
  B00001000,
  B00001000,

  // 2 minutos centrifugado vaciado
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,


  // 3 minutos llenado
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,

  // 7 minutos enjuague
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,

  // 2 minutos vaciado
  B10001000,
  B00001000,
  B00001000,
  B11001000,
  B00001000,
  B00001000,
  B10001000,
  B00001000,
  B00001000,
  B11001000,
  B00001000,
  B00001000,

  // 2 minutos centrifugado vaciado
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,
  B10111000,

  // 3 minutos llenado
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100

};


 byte PROG_C[]  = {

  // 5 minutos llenado
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,

  // 20 minutos lavado
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000

};


byte PROG_B[]  = {

  // 10 seg vaciado y llenado
  B00001100,

  // 5 minutos llenado
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,
  B10000100,
  B00000100,
  B00000100,
  B11000100,
  B00000100,
  B00000100,

  // 10 minutos lavado
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B11000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000

};