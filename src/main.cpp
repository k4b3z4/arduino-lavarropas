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
#define PIN_K3 13
#define PIN_K4 2
#define PIN_K5 1
#define PIN_K6 0

// ANALOG
#define PIN_KEYPAD A0
#define PIN_PUERTA A5
#define PIN_NIVEL  A4

// ENCODER
#define PIN_CLK  3
#define PIN_DATA A1
#define PIN_SW   A2

// BEEP
#define PIN_BEEP A3

// *******************************************************************


Timer timer;  // timer para programas
Timer timer2; // timer para Reloj
Timer timer3; // timer para beep

LiquidCrystal lcd(PIN_RS, PIN_E, PIN_D4, PIN_D5, PIN_D6, PIN_D7);


int    contador  = 0;
int    segundos  = 0;
bool   lavando   = false;
int    programa  = 1;
bool   cambia_programa = false;
int    boton     = 0;
char   buffer[18];

int  menu_posicion = 0;
int  menu_activar  = 0;
bool menu_presionado = false;
bool menu_parar = false;
bool menu_pausa = false;

int  encoder_val = 0;
int  encoder = 0;

int beeps = 0;

// *******************************************************************

void IncrementaContador(void);
void Reloj(void);
void Beep(void);
void Estado(byte);
void doEncoder(void);
int  calculaTotal(int);

// *******************************************************************



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

    // encoder
    pinMode(PIN_SW, INPUT_PULLUP);
    pinMode(PIN_DATA, INPUT_PULLUP);
    pinMode(PIN_CLK, INPUT_PULLUP);
    
    // beep
    pinMode(PIN_BEEP, OUTPUT);
    digitalWrite(PIN_BEEP, 0);

    // button adc input
    pinMode(PIN_KEYPAD, INPUT);         // ensure Key ADC pin is an input
    digitalWrite(PIN_KEYPAD, LOW);      // ensure pull-up is off on Key ADC pin

    // 10 segundos
    timer.every(10000, IncrementaContador);

    // 1 segundo
    timer2.every(1000, Reloj);

    // 200 ms
    timer3.every(200, Beep);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // Primer programa
    cambia_programa = true;

    // segunda linea
    lcd.setCursor(0, 1);
    lcd.print("Listo...        ");

    // interrupcion encoder
    attachInterrupt(digitalPinToInterrupt(PIN_CLK), doEncoder, CHANGE);

    beeps = 3;

}


// ###########################################################################
// ######################## Loop Principal ###################################

void loop() {

    // Menu seleccion de programa
    if (menu_posicion == 1 && lavando == false){
        if (encoder < 10){
            lcd.setCursor(0,1);       
            lcd.print("[B] C D E - K -");
            programa = 1;
        }
        if (encoder > 10 & encoder < 20){ 
            lcd.setCursor(0,1);
            lcd.print("B [C] D E - K -");
            programa = 2;
        }
        if (encoder > 20 & encoder < 30){ 
            lcd.setCursor(0,1);
            lcd.print("B C [D] E - K -");
            programa = 3;
        }
        if (encoder > 30 & encoder < 40){ 
            lcd.setCursor(0,1);
            lcd.print("B C D [E] - K -");
            programa = 4;
        }
        if (encoder > 40 & encoder < 50){ 
            lcd.setCursor(0,1);
            lcd.print("B C D E [-] K -");
            programa = 5;
        }
        if (encoder > 50 & encoder < 60){ 
            lcd.setCursor(0,1);
            lcd.print("B C D E - [K] -");
            programa = 6;
        }
        if (encoder > 60){ 
            lcd.setCursor(0,1);
            lcd.print("B C D E - K [-]");
            programa = 7;
        }
        segundos = calculaTotal(programa);
        if (encoder > 70) encoder = 70;
        if (encoder < 0 ) encoder = 0;
    }

    // Menu detener lavado (modo pausa)
    if( menu_posicion == 1 && lavando == true){
        if (encoder < 10){
            lcd.setCursor(0,1);       
            lcd.print("Parar? [No] Si ");
            menu_parar = false;
        }
        if (encoder > 10){ 
            lcd.setCursor(0,1);
            lcd.print("Parar?  No [Si]");
            menu_parar = true;
        }
        if (encoder > 20) encoder = 20;
        if (encoder < 0 ) encoder = 0;
    }


    // click Menu
    if( !digitalRead(PIN_SW) & !menu_presionado){

        menu_presionado = 1;

        // activa menu principal
        if(menu_posicion == 0){
            if (lavando == false){
                lcd.clear();
                lcd.setCursor(0,0);  
                lcd.print("Prg?");
                encoder = 0;
                menu_posicion = 1;
            }else{
                encoder = 0;
                menu_posicion = 1;
                menu_pausa = true;
                digitalWrite(PIN_K1, 1);
                digitalWrite(PIN_K2, 1);
                digitalWrite(PIN_K3, 1);
                digitalWrite(PIN_K4, 1);
                digitalWrite(PIN_K5, 1);
                digitalWrite(PIN_K6, 1);
            }
        }

        // vuelve del menu principal
        else if(menu_posicion == 1){
            lcd.setCursor(0,1);
            lcd.print("               ");
            if(lavando == false){
                if(programa == 1 || programa == 2 || programa == 3 || programa == 4 || programa == 6){
                    lavando = true;
                }
                cambia_programa = true;
            }else{
                if(menu_parar){
                    lcd.setCursor(0, 0);
                    lcd.print("Prog -  00:00:00");
                    lcd.setCursor(0, 1);
                    lcd.print("Finalizado      ");
                    lavando = false;
                }
                menu_pausa = false;
            }
            menu_posicion = 0;
        }

    }
    if(digitalRead(PIN_SW)){
        menu_presionado = 0;
    }


    if(cambia_programa){

        lcd.setCursor(0, 0);

        switch (programa){
            case 1:
                lcd.print("Prg B");
                break;
            case 2:
                lcd.print("Prg C");
                break;
            case 3:
                lcd.print("Prg D");
                break;
            case 4:
                lcd.print("Prg E");
                break;
            case 6:
                lcd.print("Prg K");
                break;
            case 5:
            case 7:
                lcd.print("Prg -");
                digitalWrite(PIN_K1, 1);
                digitalWrite(PIN_K2, 1);
                digitalWrite(PIN_K3, 1);
                digitalWrite(PIN_K4, 1);
                digitalWrite(PIN_K5, 1);
                digitalWrite(PIN_K6, 1);
                lavando = false;
                break;
        }

        segundos = calculaTotal(programa);
        cambia_programa = false;

    }

    timer.update();
    timer2.update();
    timer3.update();

}

// ###########################################################################
// ###########################################################################


void Reloj(){

    int h;
    int m;
    int s;

    h = segundos / 3600;
    m = ( segundos % 3600 ) / 60;
    s = ( segundos % 3600 ) % 60;

    lcd.setCursor(8, 0);
    sprintf(buffer,"%02d:%02d:%02d",h,m,s);
    lcd.print(buffer);

    if(lavando == true and menu_pausa == false){
        segundos--;
    }

    return;
}

void Beep(void){

    if (beeps > 0){
        if(digitalRead(PIN_BEEP)){
            digitalWrite(PIN_BEEP,0);
            beeps--;
        }else{
            digitalWrite(PIN_BEEP,1);
        }
    }


}

// ###########################################################################
// ###########################################################################

void IncrementaContador() {

    if(lavando == false){
        return;
    }

    if(menu_pausa == true){
        return;
    }

    //lcd.setCursor(9, 0);
    //sprintf(buffer,"%03d",contador);
    //lcd.print(buffer);

    if(programa == 1){
        digitalWrite(PIN_K1, !(PROG_B[contador] & B10000000 ));
        digitalWrite(PIN_K2, !(PROG_B[contador] & B01000000 ));
        digitalWrite(PIN_K3, !(PROG_B[contador] & B00100000 ));
        digitalWrite(PIN_K4, !(PROG_B[contador] & B00010000 ));
        digitalWrite(PIN_K5, !(PROG_B[contador] & B00001000 ));
        digitalWrite(PIN_K6, !(PROG_B[contador] & B00000100 ));
        if(PROG_B[contador] & B00000001) beeps = 6;
        Estado(PROG_B[contador]);
        if(contador == sizeof(PROG_B)-1 ){
            cambia_programa=true;
            programa ++;
            contador = 0;
            return;
        }
    }

    if(programa == 2){
        digitalWrite(PIN_K1, !(PROG_C[contador] & B10000000 ));
        digitalWrite(PIN_K2, !(PROG_C[contador] & B01000000 ));
        digitalWrite(PIN_K3, !(PROG_C[contador] & B00100000 ));
        digitalWrite(PIN_K4, !(PROG_C[contador] & B00010000 ));
        digitalWrite(PIN_K5, !(PROG_C[contador] & B00001000 ));
        digitalWrite(PIN_K6, !(PROG_C[contador] & B00000100 ));
        if(PROG_C[contador] & B00000001) beeps = 6;
        Estado(PROG_C[contador]);
        if(contador == sizeof(PROG_C)-1 ){
            cambia_programa=true;
            programa ++;
            contador = 0;
            return;
        }
    }

    if(programa == 3){
        digitalWrite(PIN_K1, !(PROG_D[contador] & B10000000));
        digitalWrite(PIN_K2, !(PROG_D[contador] & B01000000));
        digitalWrite(PIN_K3, !(PROG_D[contador] & B00100000));
        digitalWrite(PIN_K4, !(PROG_D[contador] & B00010000));
        digitalWrite(PIN_K5, !(PROG_D[contador] & B00001000));
        digitalWrite(PIN_K6, !(PROG_D[contador] & B00000100));
        if(PROG_D[contador] & B00000001) beeps = 6;
        Estado(PROG_D[contador]);
        if(contador == sizeof(PROG_D)-1 ){
            cambia_programa=true;
            programa ++;
            contador = 0;
            return;
        }
    }

    if(programa == 4){
        digitalWrite(PIN_K1, !(PROG_E[contador] & B10000000));
        digitalWrite(PIN_K2, !(PROG_E[contador] & B01000000));
        digitalWrite(PIN_K3, !(PROG_E[contador] & B00100000));
        digitalWrite(PIN_K4, !(PROG_E[contador] & B00010000));
        digitalWrite(PIN_K5, !(PROG_E[contador] & B00001000));
        digitalWrite(PIN_K6, !(PROG_E[contador] & B00000100));
        if(PROG_E[contador] & B00000001) beeps = 6;
        Estado(PROG_E[contador]);
        if(contador == sizeof(PROG_E)-1 ){
            lcd.setCursor(0, 1);
            lcd.print("Finalizado      ");
            cambia_programa=true;
            programa ++;
            contador = 0;
            return;
        }
    }

    if(programa == 6){
        digitalWrite(PIN_K1, !(PROG_K[contador] & B10000000));
        digitalWrite(PIN_K2, !(PROG_K[contador] & B01000000));
        digitalWrite(PIN_K3, !(PROG_K[contador] & B00100000));
        digitalWrite(PIN_K4, !(PROG_K[contador] & B00010000));
        digitalWrite(PIN_K5, !(PROG_K[contador] & B00001000));
        digitalWrite(PIN_K6, !(PROG_K[contador] & B00000100));
        if(PROG_K[contador] & B00000001) beeps = 6;
        Estado(PROG_K[contador]);
        if(contador == sizeof(PROG_K)-1 ){
            lcd.setCursor(0, 1);
            lcd.print("Finalizado      ");
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


void Estado(byte B){

    if(menu_posicion == 0){
        lcd.setCursor(0, 1);
        if(B & B00000100){
            lcd.print("Llenando...     ");
            return;
        }
        if(B & B00100000){
            lcd.print("Centrifugando...");
            return;
        }
        if(B & B00001000){
            lcd.print("Vaciando...     ");
            return;
        }
        if(B & B11000000){
            lcd.print("Lavando...      ");
            return;
        }

        lcd.print("Esperando...    ");
        return;
    }
   
}

int calculaTotal(int prog){

    int seg;

    switch (prog){
        case 1:
            seg = sizeof(PROG_B)*10 + sizeof(PROG_C)*10 + sizeof(PROG_D)*10 + sizeof(PROG_E)*10;
            break;
        case 2:
            seg = sizeof(PROG_C)*10 + sizeof(PROG_D)*10 + sizeof(PROG_E)*10;
            break;
        case 3:
            seg = sizeof(PROG_D)*10 + sizeof(PROG_E)*10;
            break;
        case 4:
            seg = sizeof(PROG_E)*10;
            break;
        case 6:
            seg = sizeof(PROG_K)*10;
            break;
        default:
            seg = 0;
    }

    return seg;

}


void doEncoder(){
    if(menu_posicion){
        if (digitalRead(PIN_CLK) == digitalRead(PIN_DATA))  {
            encoder++;
        }else{
            encoder--;
        }
        encoder_val = encoder / 2.5;
    }
}