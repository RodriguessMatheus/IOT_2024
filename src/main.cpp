/*************************
 * Projeto IOT com ESP32
 * Escola SENAI de Informática
 * Curso de Apredizagem industrial
 * Integrador de soluções em nuvem
 * Data: 01/08/2024
 *
 * Autor: matheus rodrigues
 *
 * Descrição: Projeto de automação utilizando ESP32
 * com conexão WiFi e MQTT.
 *
 * versão: 0.9
 *************************/

#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#include "atuadores.h"
#include "funcoes.h"
#include "umidificador.h"
#include "motorDC.h"
#include "atuadores.h"
#include "dhtt.h"
#include <lcd.h>
#include "gas.h"

// Definição dos tópicos de publicação
#define mqtt_pub_topic1 "projeto/dados"

float distanciaMedida = 0;

// Variáveis globais
unsigned long tempoAnteriorIntervaloPublicacao = 0;
const unsigned long intervaloPublicao = 1000;

// Prototipo das funcoes

void setup()
{
  Serial.begin(115200);
  

  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
  randomSeed(esp_random());
  setupUmidificador();
  inicializaSensorTinta();
  MotorSetup();
  Servosetup();
  setupDHT();
  setuplcd();
  setupGAS();
}
void loop()
{

  atualiza_time();
  atualiza_saidas();
  atualiza_botoes();
  atualiza_mqtt();
  randomiza_senha();
  loopUmidificador();
  medirNivelTinta();
  Motorloop();
  Servoloop();
  loopDHT();
  looplcd();
  loopGAS();

  JsonDocument doc;
  String json;
  bool mensagemPendente = false;

  if (millis() - tempoAnteriorIntervaloPublicacao >= intervaloPublicao)
  {
    tempoAnteriorIntervaloPublicacao = millis();

    // Adicionando dados comuns ao JSON
    doc["timeStamp"] = getFormattedDateTime();
    doc["LedSinal"] = estadoLed;
    doc["UmidificadorState"] = umidificadorLigado; // Estado do umidificador
    doc["nivelTinta"] = round(distanciaMedida * 10) / 10.0;
    doc["motorDC"] = motorLigado;                  // Estado do motor DC
    doc["portaAberta"] = portaAberta;              // Estado da porta
    doc["UmidadeOperacao"] = round(humidityOperacao * 10) / 10.0;
    doc["TemperaturaOperacao"] = round(temperatureOperacao * 10) / 10.0;
    doc["SensorGas"] = sensorValue;

    mensagemPendente = true;
  }

  // Se houver uma mensagem pendente, serialize e publique no MQTT
  if (mensagemPendente)
  {
    String json;
    serializeJsonPretty(doc, json);
    publica_mqtt(mqtt_pub_topic1, json); // Publica no MQTT
    mensagemPendente = false;            // Reseta a flag de mensagem pendente
  }
}


