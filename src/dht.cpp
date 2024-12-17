#include "dhtt.h"
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Defina os pinos e tipo do sensor
#define DHTPIN_OPERACAO 4 // Pino para o sensor da sala de operação
#define DHTTYPE DHT22     // Tipo de sensor, DHT22 ou DHT11

// Instancia os sensores DHT para cada sala
DHT dhtOperacao(DHTPIN_OPERACAO, DHTTYPE);

// Variáveis globais para armazenar os dados lidos
float humidityOperacao = 0;
float temperatureOperacao = 0;

// Variáveis para controle de tempo
unsigned long previousMillis = 0;
const long interval = 2000; // Intervalo de 2 segundos

// Função de configuração
void setupDHT()
{
    dhtOperacao.begin();
    Serial.println("Sensores DHT inicializados para salas de operação.");
}

// Função de loop para leitura dos sensores
void loopDHT()
{
    unsigned long currentMillis = millis();

    // Verifica se o intervalo de tempo já passou
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis; // Atualiza o tempo
        // Leitura do sensor da sala de operação
        humidityOperacao = dhtOperacao.readHumidity();
        temperatureOperacao = dhtOperacao.readTemperature();
        
        if (isnan(humidityOperacao) || isnan(temperatureOperacao))
        {
            Serial.println("Erro ao ler o sensor DHT da Sala de Operação!");
        }
    }
}
