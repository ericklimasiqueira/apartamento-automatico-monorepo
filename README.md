# 🏠 Smart Apartment - Automação Residencial do Zero

## 📖 Sobre o Projeto
Bem-vindo ao repositório do meu projeto pessoal de automação residencial. O objetivo principal é automatizar todo o meu apartamento através de uma solução *end-to-end*. Este espaço documenta a criação e integração de todo o ecossistema, aplicando conceitos de elétrica, eletrônica e ciência da computação para desenvolver desde os circuitos e programação de microcontroladores (Hardware) até o servidor e a interface de controle do usuário (Software).

## 🚀 Estado Atual: Primeiros Passos
O projeto foi iniciado pelo controle de iluminação via hardware. Até o momento, desenvolvemos a lógica principal no microcontrolador para gerenciar múltiplos LEDs (simulando as lâmpadas do apartamento).

**Funcionalidades já implementadas:**
* **Controle Manual:** Uso de botão físico (push button) como interruptor (toggle) com tratamento de debounce.
* **Automação por Software (Timer):** Criação de um relógio interno usando a função `millis()` do Arduino para agendar o acionamento e desligamento das luzes em horários específicos, sem travar a execução do código principal.
* **Lógica Inversa:** Adaptação do código para hardware com acionamento em nível lógico baixo (Ativo em Baixo / Active Low).

## 🛠️ Tecnologias e Componentes Iniciais
Nesta primeira etapa (Hardware), estamos utilizando:
* **Microcontrolador:** Arduino (C/C++)
* **Componentes Eletrônicos:** LEDs, Push Buttons, Resistores, Protoboard.
* **Conceitos aplicados:** Arrays, controle de fluxo de tempo (`millis()`), Pull-up interno, manipulação de portas I/O.

## 🗺️ Roadmap (Próximos Passos)
A arquitetura final do projeto será dividida em três pilares principais. O que está planejado:

- [x] **Fase 1: Prova de Conceito (Hardware)** - Controle local de iluminação com Arduino.
- [ ] **Fase 2: Expansão de Hardware** - Integração de Módulo RTC (DS3231) para precisão de tempo e transição para relés (controle de lâmpadas reais de 110V/220V).
- [ ] **Fase 3: O Cérebro (Servidor/Backend)** - Criação de um servidor local (ex: Node.js, Python ou Raspberry Pi) para centralizar os comandos.
- [ ] **Fase 4: Conectividade (IoT)** - Fazer o hardware se comunicar com o servidor (via Wi-Fi com ESP32/ESP8266 ou Serial).
- [ ] **Fase 5: Interface (Frontend)** - Desenvolvimento de um painel web/mobile para controle do apartamento pelo celular.

## 📁 Estrutura do Repositório
Para manter a organização entre diferentes linguagens e ambientes, o projeto seguirá esta estrutura:
```text
/hardware   # Códigos em C++ (Arduino/ESP) e esquemas elétricos
/backend    # API e servidor local (Em breve)
/frontend   # Interface do usuário Web/Mobile (Em breve)