// Incluindo as bibliotecas de comunicação com o RTC
#include <Wire.h>
#include "RTClib.h"

// Cria o objeto do Relógio
RTC_DS3231 rtc; 

// 2. VARIÁVEIS DOS LEDS E BOTÃO
int pinosLEDs[6] = {11, 10, 9, 6, 5, 3}; 
int BTN_1 = 7;

// Lógica Inversa: LOW = Aceso, HIGH = Apagado
int estado_geral_leds = LOW; 
int estado_atual_button = HIGH;
int estado_anterior_button = HIGH;

// MUDANÇA AQUI: Duas variáveis independentes para garantir segurança
bool ja_desligou_hoje = false; 
bool ja_ligou_hoje = false; 

void setup() {
  Serial.begin(9600); // Ativa o monitor serial para debug
  
  // INICIALIZAÇÃO DO RTC
  if (! rtc.begin()) {
    Serial.println("RTC não encontrado! Verifique os fios SDA e SCL.");
    while (1); // Trava o Arduino aqui se o chip não estiver conectado
  }

  // Se a bateria acabou ou é a primeira vez ligando:
  if (rtc.lostPower()) {
    Serial.println("RTC perdeu energia. Ajustando a hora para a compilação!");
    // Essa linha mágica pega a hora do PC e joga no chip RTC!
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  }

  // Configuração dos Pinos
  pinMode(BTN_1, INPUT_PULLUP);
  
  for(int i = 0; i < 6; i++) {
    pinMode(pinosLEDs[i], OUTPUT);
    digitalWrite(pinosLEDs[i], estado_geral_leds); 
  }
}

void loop() {
  // ==========================================
  // 1. LENDO A HORA EXATA DO RTC
  // ==========================================
  DateTime agora = rtc.now(); // Puxa a hora do chip físico
  int horas = agora.hour();
  int minutos = agora.minute();
  
  // Reseta AMBAS as travas automaticamente toda meia-noite
  if (horas == 0 && minutos == 0) {
    ja_desligou_hoje = false; 
    ja_ligou_hoje = false;
  }

  // ==========================================
  // 2. LÓGICA MANUAL (O BOTÃO)
  // ==========================================
  estado_atual_button = digitalRead(BTN_1);
  if(estado_atual_button == LOW && estado_anterior_button == HIGH) {
    
    // Inverte o estado
    if(estado_geral_leds == LOW) { estado_geral_leds = HIGH; } 
    else { estado_geral_leds = LOW; }
    
    for(int i = 0; i < 6; i++) {
      digitalWrite(pinosLEDs[i], estado_geral_leds);
    }
    delay(50); // Anti-bounce
  } 
  estado_anterior_button = estado_atual_button;


  // ==========================================
  // 3. LÓGICA AUTOMÁTICA (Desligar às 07:00 da manhã)
  // ==========================================
  if(horas == 7 && minutos == 0 && ja_desligou_hoje == false) {
    
    estado_geral_leds = HIGH; // HIGH = Apaga na lógica inversa
    
    for(int i = 0; i < 6; i++) {
      digitalWrite(pinosLEDs[i], estado_geral_leds);
    }
    
    ja_desligou_hoje = true; // Trava ativada para o Desligamento
    Serial.println("Luzes apagadas automaticamente às 07:00");
  }

  // ==========================================
  // 4. LÓGICA AUTOMÁTICA (Ligar às 18:00 da noite)
  // ==========================================
  if(horas == 18 && minutos == 0 && ja_ligou_hoje == false) {

    estado_geral_leds = LOW; // LOW = Acende na lógica inversa
    
    for(int i = 0; i < 6; i++) {
      digitalWrite(pinosLEDs[i], estado_geral_leds);
    }

    ja_ligou_hoje = true; // Trava ativada para o Acendimento
    Serial.println("Luzes acesas automaticamente às 18:00");
  }
}