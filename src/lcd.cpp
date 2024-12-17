#include <Arduino.h>
#include "lcd.h"
#include <LiquidCrystal_I2C.h>

// Instância do LCD I2C
LiquidCrystal_I2C lcd(0x27, 20, 4); // Endereço 0x27, 20 colunas, 4 linhas


// Variáveis de senha e tempo
int senha;
const unsigned long intervaloNormal = 30000;
const unsigned long intervaloEstendido = 90000;
unsigned long tempoInicialResetSenha = 0;
unsigned long intervaloResetSenha = 0;


void setuplcd()
{ 
    
    // Inicializa o LCD
    lcd.init();      // Inicializa o display
    lcd.backlight(); // Ativa o backlight
    lcd.setCursor(0, 0);
    lcd.print("Iniciando...");

    // Inicializa a senha
    randomSeed(analogRead(0)); // Usa entropia
    senha = randomiza_senha();
}

// Função principal do LCD
void looplcd()
{
    randomiza_senha();
    // Outras lógicas podem ser adicionadas aqui
}

// Função para randomizar a senha
int randomiza_senha()
{
    unsigned long tempoAtual = millis();

    if (tempoAtual - tempoInicialResetSenha >= intervaloResetSenha)
    {
        if (intervaloResetSenha != intervaloNormal)
            intervaloResetSenha = intervaloNormal;

        tempoInicialResetSenha = tempoAtual;
        senha = random(1000, 9999);

        // Exibe a senha no LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Nova senha:");
        lcd.setCursor(0, 1);
        lcd.print(senha);
    }
    return senha;
}

// Função para estender o tempo da senha
void tempoSenhaEstendido()
{
    if (intervaloResetSenha != intervaloEstendido)
    {
        unsigned long tempoAtual = millis();
        tempoInicialResetSenha = tempoAtual;
        intervaloResetSenha = intervaloEstendido;

        // Mensagem no LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Senha estendida");
        lcd.setCursor(0, 1);
        lcd.print("por 90 segundos");
    }
}

// Função de configuração do LCD