#include <WiFiUdp.h>
#include <NTPClient.h> // Consultar a hora no servidor
#include <TimeLib.h>   // Formatar a hora
#include "tempo.h"

const int fusoHorario = -10800;
const unsigned long atualizaNTP = 60000; // em milissegundos

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", fusoHorario, atualizaNTP);


void hora_certa()
{
  unsigned long epochTime = timeClient.getEpochTime();
  setTime(epochTime);
  Serial.printf("%02d/%02d/%04d", day(), month(), year());
  Serial.printf(" %02d:%02d:%02d \n", hour(), minute(), second());
}

String getFormattedDateTime()
 {
    unsigned long epochTime = timeClient.getEpochTime();
    setTime(epochTime);
    
    char dateTime[20]; // Buffer para armazenar a data e hora formatada
    snprintf(dateTime, sizeof(dateTime), "%02d/%02d/%04d %02d:%02d:%02d", 
             day(), month(), year(), hour(), minute(), second());
    
    return String(dateTime); // Retorna a string formatada
}

unsigned long timeStamp()
{
  return timeClient.getEpochTime();
}

void setup_time()
{
  timeClient.begin();
}

void atualiza_time()
{
  timeClient.update();
}
