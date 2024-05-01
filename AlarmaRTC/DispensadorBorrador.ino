#include <I2C_RTC.h>
static DS1307 RTC;

/* Este borrador servirá para volver a practicar los elementos básicos de progarmación
 *  Como primera etapa se tratará de prender un led a determinada hora
 *  antes de comenzar se repasarán los conceptos básicos
 *  Se utilizará como base el codigo utilizado en el lab "termostato"
 *   1 - la idea básica es asignar una variable Hora /minuto, para que luego en un if ejecute el le prendido
 *   2 - Tomar las funciones
 */

//------------------------------Variables

int h_set1 = 12 ; //variable de seteo para hora (Ver variable)
int m_set1 = 00 ; //variable de seteo para minutos (ver variable)

// Segunda Variable asignada, se prueba con una al principio

//int hora_set2 = 12 ; //variable de seteo para hora (Ver variable)
//int min_set2 = 00 ; //variable de seteo para minutos (ver variable)


//------------------------------Salidas

#define led 8 //= LOW 

//------------------------------Configuraciones RTC

void setup() {

  Serial.begin(9600);
  RTC.begin();

  //RTC.setHourMode(CLOCK_H12);
  /*RTC.setHourMode(CLOCK_H24);

  if (RTC.getHourMode() == CLOCK_H12)
                  {
                     RTC.setMeridiem(HOUR_PM);
                  }*/
/*
  RTC.setDay(13);
  RTC.setMonth(05);
  RTC.setYear(2020);

  RTC.setHours(9);
  RTC.setMinutes(47);
  RTC.setSeconds(56);
*/
  RTC.setWeek(1);
  RTC.setDate(22,07,21);
  RTC.setTime(23,00,00); 
    } 

void loop()      
              {
        
        LecturaRTC (); // Mediante esta función obtenemos los datos del RTC (hora, min)      
        Temporizador (); // Aca se tomara los datos, en base a esto se carga el if para la sentencia
        
        }

//----------- Funcion
        
void Temporizador () {

     if ((h_set1 == RTC.getHours()) && m_set1 == RTC.getMinutes())  // si la Hora y los minutos es igual a la del RTC
            
            {
            digitalWrite (led,HIGH);  // prender el led
            Serial.print("DISPENSAR");
            delay (100);
            }
            
            else  // si eso no ocurre, apagar el led
            
            {
            digitalWrite (led,LOW);
            }



   RTC.getHours();
   RTC.getMinutes ();
  
  }

void LecturaRTC ()
{
/*  switch (RTC.getWeek())
  {
    case 1:
      Serial.print("SUN");
      break;
    case 2:
      Serial.print("MON");
      break;
    case 3:
      Serial.print("TUE");
      break;
    case 4:
      Serial.print("WED");
      break;
    case 5:
      Serial.print("THU");
      break;
    case 6:
      Serial.print("FRI");
      break;
    case 7:
      Serial.print("SAT");
      break;
  }*/
  
  Serial.print(" ");
  Serial.print(RTC.getDay());
  Serial.print("-");
  Serial.print(RTC.getMonth());
  Serial.print("-");
  Serial.print(RTC.getYear());

  Serial.print(" ");

  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.print(RTC.getSeconds());
  Serial.print(" ");

  if (RTC.getHourMode() == CLOCK_H12)
  {
    switch (RTC.getMeridiem()) {
      case HOUR_AM :
        Serial.print(" AM");
        break;
      case HOUR_PM :
        Serial.print(" PM");
        break;
    }
  }
  Serial.println("");
  delay(1000);
}
