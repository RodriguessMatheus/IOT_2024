#include <Arduino.h>
#include <ESP32Servo.h>
#include "atuadores.h"

#define BUTTON_PIN 5 // Pino do botão
#define SERVO_PIN 33 // Pino do servo

Servo servoMotor;         // Cria um objeto Servo
bool portaAberta = false; // Estado da porta

void Servosetup()
{
  servoMotor.attach(SERVO_PIN);      // Atacha o servo ao pino especificado
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura o botão como entrada com pull-up interno
  servoMotor.write(0);               // Garante que o servo inicie na posição 0 graus (porta fechada)
}

void Servoloop()
{
  static bool buttonPressed = false; // Estado anterior do botão
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 50; // Tempo para debounce

  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && !buttonPressed && (millis() - lastDebounceTime > debounceDelay))
  {
    // Alterna o estado da porta
    portaAberta = !portaAberta;
    buttonPressed = true;
    lastDebounceTime = millis();

    if (portaAberta)
    {
      servoMotor.write(100); // Abre a porta (100 graus)
    }
    else
    {
      servoMotor.write(0); // Fecha a porta (0 graus)
    }
  }
  else if (buttonState == HIGH)
  {
    buttonPressed = false; // Libera para próxima leitura
  }
}
