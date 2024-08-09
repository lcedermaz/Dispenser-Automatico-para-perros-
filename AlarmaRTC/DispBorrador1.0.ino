

/* Este borrador servirá para volver a practicar los elementos básicos de progarmación
 *  Como primera etapa se tratará de prender un led a determinada hora
 *  antes de comenzar se repasarán los conceptos básicos
 *  Se utilizará como base el codigo utilizado en el lab "termostato"
 *   1 - la idea básica es asignar una variable Hora /minuto, para que luego en un if ejecute el le prendido
 *   2 - Tomar las funciones
 *   3 - Ejecutarla al momento seteado del RTC
 */
 
#include <Wire.h>;
#include "RTClib.h";

// Pines para el A4988
const int dirPin = 2;
const int stepPin = 3;
const int enablePin = 4;

// Pines para el LED
const int ledPin = 8;

// Pines para el DS1302 - Tiene que ser el 1307 Tiny
/*const int RST_PIN = 5;
const int DAT_PIN = 6;
const int CLK_PIN = 7;
*/

/*#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif0
*/
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};


//------------------------------Variables
//Tiempo de seteo

int h_set1 = 19 ; //variable de seteo para hora (Ver variable)
int m_set1 = 48 ; //variable de seteo para minutos (ver variable)

// Segunda Variable asignada, se prueba con una al principio

int h_set2 = 00 ; //variable de seteo para hora (Ver variable)
int m_set2 = 20 ; //variable de seteo para minutos (ver variable)

//Movimiento del motor, se configura para que de 10 vueltas

const int stepsPerRevolution = 200; // Asumiendo que el motor tiene 200 pasos por revolución
const int numberOfRevolutions = 10; // Número de vueltas
const unsigned long stepDelay = 500; // Microsegundos entre pasos


//------------------------------SETEO DE TIEMPOS DE REFRESCO (Monitor)

unsigned long previousMillis = 0;        
const long interval = 5000 ;  // Reemplaza el dealy, para que no retrase ningun tiempo tomado por el RTC


 
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT); // Iniciar el LED 13 como salida
  digitalWrite (LED_BUILTIN,LOW); // Iniciar apagado

  // Configuración de pines para el A4988
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // Habilitar el driver
        
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
             
unsigned long currentMillis_2 = millis();   // Conteo de tiempo para la interrupción
 
if(currentMillis_2 - previousMillis >= interval) {
    
  previousMillis = currentMillis_2;
  
  Dispensar (); // Mediante esta función obtenemos los datos del RTC (hora, min), Aca se tomara los datos, en base a esto se carga el if para la sentencia
  
}
}

//----------- Funcion
        
void Dispensar () {
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
    //delay(3000);

      if ((h_set1 == now.hour()) && m_set1 == now.minute()||(h_set2 == now.hour()) && m_set2 == now.minute())   // Se confguran dos tiempos para actuar el motor, el cual se definiría uno al mediodía y otro a la noche
            
            {
            digitalWrite (LED_BUILTIN,HIGH);  // prender el led 13
            Serial.print("DISPENSAR");
            Serial.println();
            // Se agrega giro del motor
        
        // Mover el motor paso a paso 10 vueltas
        digitalWrite(dirPin, HIGH); // Establecer dirección
        
        for(int x = 0; x < stepsPerRevolution * numberOfRevolutions; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(stepDelay);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(stepDelay);
        
            // (1000);
            
                        }
     }

            else  // si eso no ocurre, apagar el led
            
                {

            digitalWrite (LED_BUILTIN,LOW);// Apagar el 13
              
                }
          
}
