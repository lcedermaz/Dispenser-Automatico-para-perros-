

/* Este borrador servirá para volver a practicar los elementos básicos de progarmación
 *  Como primera etapa se tratará de prender un led a determinada hora
 *  antes de comenzar se repasarán los conceptos básicos
 *  Se utilizará como base el codigo utilizado en el lab "termostato"
 *   1 - la idea básica es asignar una variable Hora /minuto, para que luego en un if ejecute el le prendido
 *   2 - Tomar las funciones
 */
 
#include <Wire.h>;
#include "RTClib.h";

// Pines para el A4988
const int dirPin = 2;
const int stepPin = 3;
const int enablePin = 4;

// Pines para el LED
const int ledPin = 8;

//Configuracion RTC
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};


//------------------------------Variables
//Tiempo de seteo

int h_set1 = 21 ; //variable de seteo para hora (Ver variable)
int m_set1 = 10 ; //variable de seteo para minutos (ver variable)
//int s_set1 = 00 ; //variable segundo, se agregar para que la condicion no la repita todo el minuto

// Segunda Variable asignada, se prueba con una al principio

int h_set2 = 00 ; //variable de seteo para hora (Ver variable)
int m_set2 = 20 ; //variable de seteo para minutos (ver variable)

//Movimiento del motor, se configura para que de 10 vueltas

const int stepsPerRevolution = 200; // Asumiendo que el motor tiene 200 pasos por revolución
const int numberOfRevolutions = 10; // Número de vueltas
const unsigned long stepDelay = 500; // Microsegundos entre pasos


//------------------------------SETEO DE TIEMPOS DE REFRESCO (Monitor)

unsigned long previousMillis = 0;        
const long interval = 35000 ;  // Tiempo ejecución de la operacion del motor (3 s, para que no se vuelva a activa con el if)
 
unsigned long previousMillis1 = 0;        
const long interval1 = 5000 ;  // Tiempo refresco RTC

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT); // Iniciar el LED 13 como salida
  digitalWrite (LED_BUILTIN,LOW); // Iniciar apagado

  // Configuración de pines para el A4988
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH); // Deshabilitar el driver
        
    // Configuración del LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Asegurarse de que el LED esté apagado inicialmente


  Serial.begin(57600);
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
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  } 
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
    
  previousMillis1 = currentMillis_2;
  
  SerialRTC (); // Se muestra tiempo en serial del RTC
  }
//delay(5000);
}

//----------- Funcion
        
void Dispensar () {

      DateTime now = rtc.now();
      SerialRTC();   

      if ((h_set1 == now.hour()) && (m_set1 == now.minute())||(h_set2 == now.hour()) && m_set2 == now.minute())   // Se confguran dos tiempos para actuar el motor, el cual se definiría uno al mediodía y otro a la noche
            
            {
            digitalWrite (LED_BUILTIN,HIGH);  // prender el led 13
            Serial.print("DISPENSAR");
            Serial.println();
            
            // Se agrega giro del motor
            digitalWrite(dirPin, HIGH); // Establecer dirección
            digitalWrite(enablePin, LOW); // habilitar el driver
            Motor();
            //return 0;
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

