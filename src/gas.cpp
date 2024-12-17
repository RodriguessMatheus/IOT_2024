#include <Arduino.h>
#include "gas.h"

// Pinos do sensor e LEDs
const int sensorPin = 34; // Pino analógico do sensor MQ-3
const int greenLED = 2;   // LED verde
const int yellowLED = 19; // LED amarelo
const int redLED = 18;    // LED vermelho

// Variáveis e constantes
const unsigned long sensorInterval = 1000; // Intervalo para leitura do sensor
const unsigned long blinkInterval = 500;   // Intervalo para piscada
int sensorValue = 0;

// Controle de tempo
unsigned long lastSensorTime = 0;
unsigned long lastBlinkTime = 0;
bool redLEDState = false;

void setupGAS()
{
    pinMode(sensorPin, INPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(redLED, OUTPUT);

    // Apaga todos os LEDs no início
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
}

void loopGAS()
{
    unsigned long currentTime = millis();

    // Leitura do sensor a cada intervalo
    if (currentTime - lastSensorTime >= sensorInterval)
    {
        sensorValue = analogRead(sensorPin);
        lastSensorTime = currentTime;
        

        // Atualização dos LEDs
        digitalWrite(greenLED, sensorValue < 3200);
        digitalWrite(yellowLED, sensorValue >= 1500 && sensorValue < 3200);

        // Controle do LED vermelho
        if (sensorValue < 3200)
        {
            digitalWrite(redLED, sensorValue >= 2900); // Liga para alta concentração
        }
        else
        {
            handleBlink(currentTime); // Pisca no nível crítico
        }
    }
}

// Função para gerenciar o piscar do LED vermelho
void handleBlink(unsigned long currentTime)
{
    if (currentTime - lastBlinkTime >= blinkInterval)
    {
        redLEDState = !redLEDState;
        digitalWrite(redLED, redLEDState);
        lastBlinkTime = currentTime;
    }
}
