// ********************************************************************
// Automatizacion Labarropas
// Arduino Uno + LCD Keypad Shield
// Federico Pedot fedped@gmail.com
//
// ********************************************************************

#include <Arduino.h>
#include <Wire.h>
#include <Timer.h>
#include <LiquidCrystal.h>
#include "programas.h"


// ********************************************************************
// Config Shield

// LCD
#define PIN_RS 8
#define PIN_E  9
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7

// DIGITAL
#define PIN_K1 12
#define PIN_K2 11
#define PIN_K3 3
#define PIN_K4 2
#define PIN_K5 1
#define PIN_K6 0

// ANALOG
#define PIN_KEYPAD A0
#define PIN_PUERTA A5
#define PIN_NIVEL  A4


// *******************************************************************


Timer timer;
LiquidCrystal lcd(PIN_RS, PIN_E, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

int    contador  = 0;
bool   lavando   = false;
int    programa  = 1;
bool   cambia_programa = false;
int    boton     = 0;

// *******************************************************************

void IncrementaContador(void);
int LeerBotones(void);


void setup() {

  // contactores
  pinMode(PIN_K1, OUTPUT);
  pinMode(PIN_K2, OUTPUT);
  pinMode(PIN_K3, OUTPUT);
  pinMode(PIN_K4, OUTPUT);
  pinMode(PIN_K5, OUTPUT);
  pinMode(PIN_K6, OUTPUT);

  digitalWrite(PIN_K1, 1);
  digitalWrite(PIN_K2, 1);
  digitalWrite(PIN_K3, 1);
  digitalWrite(PIN_K4, 1);
  digitalWrite(PIN_K5, 1);
  digitalWrite(PIN_K6, 1);

  // entradas
  pinMode(PIN_PUERTA, INPUT);
  pinMode(PIN_NIVEL, INPUT);
  digitalWrite(PIN_PUERTA, LOW);
  digitalWrite(PIN_NIVEL, LOW);

  // button adc input
  pinMode(PIN_KEYPAD, INPUT);         // ensure Key ADC pin is an input
  digitalWrite(PIN_KEYPAD, LOW);      // ensure pull-up is off on Key ADC pin

  // 10 segundos
  timer.every(10000, IncrementaContador);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // primera linea
  lcd.setCursor(0, 0);
  lcd.print("Prg C");

  // segunda linea
  lcd.setCursor(0, 1);
  lcd.print("Listo...        ");


}


// ###########################################################################
// ######################## Loop Principal ###################################

void loop() {

  boton = LeerBotones();

  if(boton > 0){
    lcd.setCursor(0, 1);
    if(boton == 2){
      if(programa > 1){
        programa--;
        contador=0;
        cambia_programa=true;
      }
    }
    if(boton == 3){
      if(programa < 3){
        programa++;
        contador=0;
        cambia_programa=true;
      }
    }
    if(boton == 5){ // START
      lavando = true;
      contador = 0;
      lcd.print("Lavando...      ");
    }
    if(boton == 1){ // STOP
      lavando = false;
      digitalWrite(PIN_K1, 1);
      digitalWrite(PIN_K2, 1);
      digitalWrite(PIN_K3, 1);
      digitalWrite(PIN_K4, 1);
      digitalWrite(PIN_K5, 1);
      digitalWrite(PIN_K6, 1);
      lcd.print("Listo...        ");
      cambia_programa=true;
    }
    delay(500);
  }

  if(cambia_programa){
    lcd.setCursor(0, 0);
    if(programa == 1){
      lcd.print("Prg C           ");
    }
    if(programa == 2){
      lcd.print("Prg D           ");
    }
    if(programa == 3){
      lcd.print("Prg E           ");
    }
    if(programa == 4){
      lcd.print("Fin             ");
      lavando=false;
    }
    cambia_programa=false;
  }

  timer.update();

}

// ###########################################################################
// ###########################################################################


void IncrementaContador() {



  if(lavando == false){
      return;
  }

  lcd.setCursor(13, 0);
  lcd.print(contador);


  if(programa == 1){
    digitalWrite(PIN_K1, !(PROG_C[contador] & B10000000 ));
    digitalWrite(PIN_K2, !(PROG_C[contador] & B01000000 ));
    digitalWrite(PIN_K3, !(PROG_C[contador] & B00100000 ));
    digitalWrite(PIN_K4, !(PROG_C[contador] & B00010000 ));
    digitalWrite(PIN_K5, !(PROG_C[contador] & B00001000 ));
    digitalWrite(PIN_K6, !(PROG_C[contador] & B00000100 ));
    if(contador == sizeof(PROG_C)-1 ){
      cambia_programa=true;
      programa ++;
      contador = 0;
      return;
    }
  }

  if(programa == 2){
    digitalWrite(PIN_K1, !(PROG_D[contador] & B10000000));
    digitalWrite(PIN_K2, !(PROG_D[contador] & B01000000));
    digitalWrite(PIN_K3, !(PROG_D[contador] & B00100000));
    digitalWrite(PIN_K4, !(PROG_D[contador] & B00010000));
    digitalWrite(PIN_K5, !(PROG_D[contador] & B00001000));
    digitalWrite(PIN_K6, !(PROG_D[contador] & B00000100));
    if(contador == sizeof(PROG_D)-1 ){
      cambia_programa=true;
      programa ++;
      contador = 0;
      return;
    }
  }

  if(programa == 3){
    digitalWrite(PIN_K1, !(PROG_E[contador] & B10000000));
    digitalWrite(PIN_K2, !(PROG_E[contador] & B01000000));
    digitalWrite(PIN_K3, !(PROG_E[contador] & B00100000));
    digitalWrite(PIN_K4, !(PROG_E[contador] & B00010000));
    digitalWrite(PIN_K5, !(PROG_E[contador] & B00001000));
    digitalWrite(PIN_K6, !(PROG_E[contador] & B00000100));
    if(contador == sizeof(PROG_E)-1 ){
      cambia_programa=true;
      programa ++;
      contador = 0;
      return;
    }
  }

  contador ++;

}


// ###########################################################################
// ###########################################################################


int LeerBotones(void){
  int boton = analogRead(PIN_KEYPAD);
  if (boton < 65){
    return 1; // Derecha
  }
  else if (boton < 221){
    return 2; // Arriba
  }
  else if (boton < 395){
    return 3; // Abajo
  }
  else if (boton < 602){
    return 4; // Izquierda
  }
  else if (boton < 873){
    return 5; // Seleccionar
  }
  return 0;
}