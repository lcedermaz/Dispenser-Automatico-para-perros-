/* Este borrador servirá para volver a practicar los elementos básicos de progarmación
 *  Como primera etapa se tratará de prender un led a determinada hora
 *  antes de comenzar se repasarán los conceptos básicos
 *  Se utilizará como base el codigo utilizado en el lab "termostato"
 *   1 - la idea básica es asignar una variable Hora /minuto, para que luego en un if ejecute el le prendido
 *   2 - Tomar las funciones
 */
 
#include <Wire.h>;
#include "RTClib.h";

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};


//------------------------------Variables

int h_set1 = 16 ; //variable de seteo para hora (Ver variable)
int m_set1 = 02 ; //variable de seteo para minutos (ver variable)

// Segunda Variable asignada, se prueba con una al principio

int h_set2 = 16 ; //variable de seteo para hora (Ver variable)
int m_set2 = 04 ; //variable de seteo para minutos (ver variable)

//------------------------------SETEO DE TIEMPOS DE REFRESCO (Monitor)

unsigned long previousMillis = 0;        
const long interval = 5000 ;  // Reemplaza el dealy, para que no retrase ningun tiempo tomado por el RTC

 
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT); // Iniciar el LED 13 como salida

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
             
unsigned long currentMillis_2 = millis();   // Reemplazo del delay por el currentmilles (sin interrupciones)
 
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
            // (1000);
            }
            
            else  // si eso no ocurre, apagar el led
            
            {
            digitalWrite (LED_BUILTIN,LOW);// Apagar el 13
            }   
       }

