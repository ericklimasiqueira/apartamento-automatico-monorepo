// 1. O RELÓGIO (Ajustado para o horário de AGORA - 19:53)
int horas = 19;    // 19 horas
int minutos = 57;  // Mude para o minuto exato em que for fazer o upload!
int segundos = 0;  // 0 segundos

unsigned long tempoAnterior = 0; 

// 2. VARIÁVEIS DOS LEDS E BOTÃO
int pinosLEDs[6] = {11, 10, 9, 6, 5, 3}; 
int BTN_1 = 7;

// ==========================================
// MUDANÇA AQUI: Lógica Inversa! 
// Como queremos começar ACESOS à noite, o estado inicial agora é LOW (0V).
// ==========================================
int estado_geral_leds = LOW; 
int estado_atual_button = HIGH;
int estado_anterior_button = HIGH;

bool ja_desligou_hoje = false; 

void setup() {
  pinMode(BTN_1, INPUT_PULLUP);
  
  for(int i = 0; i < 6; i++) {
    pinMode(pinosLEDs[i], OUTPUT);
    
    // O setup agora envia LOW para todos os pinos logo de cara,
    // o que fará os seus LEDs acenderem imediatamente.
    digitalWrite(pinosLEDs[i], estado_geral_leds); 
  }
}

void loop() {
  // ==========================================
  // 1. O MOTOR DO RELÓGIO (Continua igual)
  // ==========================================
  unsigned long tempoAtual = millis(); 
  
  if (tempoAtual - tempoAnterior >= 1000) { 
    tempoAnterior = tempoAtual; 
    segundos++; 
    
    if (segundos >= 60) {
      segundos = 0;
      minutos++;
      
      if (minutos >= 60) {
        minutos = 0;
        horas++;
        
        if (horas >= 24) {
          horas = 0; 
          ja_desligou_hoje = false; 
        }
      }
    }
  }

  // ==========================================
  // 2. LÓGICA MANUAL (O BOTÃO)
  // ==========================================
  estado_atual_button = digitalRead(BTN_1);
  if(estado_atual_button == LOW && estado_anterior_button == HIGH) {
    
    // Inverte a memória (se está LOW, vai para HIGH e vice-versa)
    if(estado_geral_leds == LOW) { estado_geral_leds = HIGH; } 
    else { estado_geral_leds = LOW; }
    
    for(int i = 0; i < 6; i++) {
      digitalWrite(pinosLEDs[i], estado_geral_leds);
    }
    delay(50); 
  } 
  estado_anterior_button = estado_atual_button;

  // ==========================================
  // 3. LÓGICA AUTOMÁTICA (Desligar às 07:00 da manhã)
  // ==========================================
  if(horas == 7 && minutos == 0 && ja_desligou_hoje == false) {
    
    // MUDANÇA AQUI: Para DESLIGAR na lógica inversa, precisamos enviar HIGH!
    estado_geral_leds = HIGH; 
    
    for(int i = 0; i < 6; i++) {
      digitalWrite(pinosLEDs[i], estado_geral_leds);
    }
    
    ja_desligou_hoje = true; 
  }
}