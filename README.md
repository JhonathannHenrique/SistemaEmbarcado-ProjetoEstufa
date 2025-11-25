# Controlador de Estufa Inteligente com Arduino

Este projeto consiste em um sistema automatizado para monitoramento e controle de microclima para estufas agrícolas ou domésticas. O sistema utiliza um Arduino para gerenciar a temperatura, a umidade do ar e a luminosidade, oferecendo feedbacks visuais, sonoros e atuando diretamente na iluminação artificial através de um relé.

## Funcionalidades

*   **Monitoramento Ambiental:** Leitura constante de Temperatura e Umidade do Ar (via DHT11) e Luminosidade (via LDR).
*   **Controle de Iluminação:** Acionamento automático de lâmpadas (via Relé) quando o ambiente escurece.
*   **Semáforo de Status:**
    *   🟢 **Verde:** Temperatura Ideal.
    *   🟡 **Amarelo:** Atenção (Temperatura subindo ou descendo).
    *   🔴 **Vermelho:** Perigo (Temperatura crítica).
*   **Alarme Sonoro:** Alerta sonoro via buzzer em casos de temperatura crítica.
*   **Monitor Serial:** Exibição dos dados em tempo real no computador.

---

## Hardware Necessário

*   1x Placa Arduino (Uno, Nano ou compatível)
*   1x Sensor de Temperatura e Umidade **DHT11**
*   1x Sensor de Luminosidade (**LDR**) + Resistor 10kΩ
*   1x Módulo Relé de 1 Canal (para a lâmpada/fita LED)
*   3x LEDs (1 Verde, 1 Amarelo, 1 Vermelho) + Resistores (220Ω ou 330Ω)
*   1x Buzzer Ativo ou Passivo
*   Jumpers e Protoboard

---

## Pinagem (Conexões)

| Componente | Pino do Arduino | Observação |
| :--- | :--- | :--- |
| **LED Vermelho** | D13 | Indicador de Perigo |
| **LED Amarelo** | D12 | Indicador de Atenção |
| **LED Verde** | D11 | Indicador Ideal |
| **Buzzer** | D10 | Alarme Sonoro |
| **Relé (Luz)** | D9 | Controla a lâmpada da estufa |
| **Sensor DHT11** | A0 | Pino de Dados (Requer biblioteca) |
| **Sensor LDR** | A2 | Leitura Analógica de Luz |

---

## Parâmetros de Controle (Lógica)

O sistema toma decisões baseadas nas seguintes faixas de valores:

### 1. Temperatura (DHT11)
*   **🟢 Estado Ideal:** Temperaturas entre **11°C e 27°C**.
    *   *Ação:* LED Verde aceso.
*   **🟡 Estado de Atenção:** Entre **28°C e 34°C** OU entre **5°C e 10°C**.
    *   *Ação:* LED Amarelo aceso.
*   **🔴 Estado Crítico:** Acima de **35°C** OU abaixo de **5°C**.
    *   *Ação:* LED Vermelho aceso + Alarme sonoro ativado.

### 2. Iluminação (LDR)
*   **Luz Baixa (< 400):** O ambiente está escuro.
    *   *Ação:* O Relé é ativado (LIGA a luz artificial).
*   **Luz Alta (>= 400):** O ambiente está claro o suficiente.
    *   *Ação:* O Relé é desativado (DESLIGA a luz artificial).

## Como Testar
*   Luz: Cubra o sensor LDR com a mão para simular a noite. O módulo Relé deve estalar e acender a luz.
*   Temperatura (Simulação): Para testar o alarme sem precisar aquecer a sala, você pode adicionar temporariamente a linha temperatura = 40; logo após a leitura do sensor no código. O LED Vermelho acenderá e o buzzer tocará.
