

/* Este borrador servirá para volver a practicar los elementos básicos de progarmación
 *  Como primera etapa se tratará de prender un led a determinada hora
 *  antes de comenzar se repasarán los conceptos básicos
 *  Se utilizará como base el codigo utilizado en el lab "termostato"
 *   1 - la idea básica es asignar una variable Hora /minuto, para que luego en un if ejecute el le prendido
 *   2 - Tomar las funciones y agruparlas para despues ejecutarlas
 *   3 - Sincronizar los tiempos para que no falle el temporizador
 *   4 - Se agrega blink led en funcionamiento ok
 */
 
#include <Wire.h>;
#include "RTClib.h";

// Pines para el A4988
const int dirPin = 2;
const int stepPin = 3;
const int enablePin = 4;

// Pines para el LED
//const int ledPin = 8;
const int ledPin = 6;  // the number of the LED pin
int ledState = LOW;  // ledState used to set the LED

//Configuracion RTC
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};


//------------------------------Variables
//Tiempo de seteo

int h_set1 = 11 ; //variable de seteo para hora (Ver variable)
int m_set1 = 40 ; //variable de seteo para minutos (ver variable)

// Segunda Variable asignada, se prueba con una al principio

int h_set2 = 11 ; //variable de seteo para hora (Ver variable)
int m_set2 = 45 ; //variable de seteo para minutos (ver variable)

//Movimiento del motor, se configura para que de 10 vueltas

const int stepsPerRevolution = 200; // Asumiendo que el motor tiene 200 pasos por revolución
const int numberOfRevolutions = 10; // Número de vueltas
const unsigned long stepDelay = 500; // Microsegundos entre pasos


//------------------------------SETEO DE TIEMPOS DE REFRESCO (Monitor)

unsigned long previousMillis = 0;        
const long interval = 60000 ;  // Tiempo ejecución de la operacion del motor (60 s, para que no se vuelva a activa con el if)
 
unsigned long previousMillis1 = 0;        
const long interval1 = 1000 ;  // Tiempo refresco RTC

unsigned long previousMillis2 = 0;        
const long interval2 = 1000 ;  // Tiempo parpadeo LED indicador

void setup() {
  
  // Configuración del LED's

  pinMode(LED_BUILTIN, OUTPUT); // Iniciar el LED 13 como salida
  digitalWrite (LED_BUILTIN,LOW); // Iniciar apagado

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Asegurarse de que el LED esté apagado inicialmente

  // Configuración de pines para el A4988
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH); // Deshabilitar el driver

  Wire.begin();
  rtc.begin();
  //Si quitamos el comentario de la linea siguiente, se ajusta la hora y la fecha con la del ordenador
  //RTC.adjust(DateTime(__DATE__, __TIME__));

  Serial.begin(57600);

  /*
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2024, 8, 10, 15, 47, 0));
    */
  } 
     

void loop()      
              {
             
unsigned long currentMillis_2 = millis();   // T1 
if(currentMillis_2 - previousMillis >= interval) {    
  previousMillis = currentMillis_2; 
  Dispensar (); // Operacion del motor
  
}

unsigned long currentMillis_3 = millis();   // T2 
if(currentMillis_3 - previousMillis1 >= interval1) {   
  previousMillis1 = currentMillis_3; 
  SerialRTC (); // Se muestra tiempo en serial del RTC
  }

unsigned long currentMillis_4 = millis();   // T3 
if(currentMillis_4 - previousMillis2 >= interval2) {   
  previousMillis2 = currentMillis_4; 
  LEDparp(); // Se muestra tiempo en serial del RTC
  }

}

//----------- Funciones
        
void Dispensar () {

      DateTime now = rtc.now();
      SerialRTC();   

      if ((h_set1 == now.hour()) && (m_set1 == now.minute())||(h_set2 == now.hour()) && m_set2 == now.minute())   // Se confguran dos tiempos para actuar el motor, el cual se definiría uno al mediodía y otro a la noche
            
            {
            
            // Se agrega giro del motor
            digitalWrite(dirPin, HIGH); // Establecer dirección
            digitalWrite(enablePin, LOW); // habilitar el driver

            digitalWrite (LED_BUILTIN,HIGH);  // prender el led 13
            Serial.print("DISPENSAR");
            Serial.println();
            
            Motor(); // Funcion que mueve el motor 10 vueltas
            }
            else  // si eso no ocurre, apagar el led
            
                {

            digitalWrite (LED_BUILTIN,LOW);// Apagar el 13

                }  
            
}

void Motor()  {

 // Mover el motor paso a paso 10 vueltas

        for(int x = 0; x < stepsPerRevolution * numberOfRevolutions; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(stepDelay);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(stepDelay);
            //delay (1000); // Se espera 1 segundo para que no vuelva a detectar el if en ese mismo tiempo
                        }
            digitalWrite(enablePin, HIGH); // deshabilitar el driver
     }

void SerialRTC(){

    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

void LEDparp() {
 
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }



