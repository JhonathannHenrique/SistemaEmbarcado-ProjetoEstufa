#include <DHT.h>

// --- Definição dos Pinos ---
#define ledRed      13
#define ledYellow   12
#define ledGreen    11
#define piezo       10
#define releLuz     9
#define SENSOR_LUZ  A2   // Sensor de luminosidade (LDR) continua no A2

// --- Configuração do DHT11 ---
#define DHTPIN A0     // O pino de DADOS do DHT11 está conectado no A0
#define DHTTYPE DHT11 // Definindo o modelo do sensor
DHT dht(DHTPIN, DHTTYPE);

// --- Parâmetros de Controle ---
const int LIMITE_LUZ = 400; // Ajuste conforme necessário

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(releLuz, OUTPUT);
  pinMode(SENSOR_LUZ, INPUT);

  // Inicia o Relé desligado
  digitalWrite(releLuz, HIGH);

  Serial.begin(9600);
  
  // Inicia o sensor DHT
  dht.begin();
  Serial.println("Inicializando sistema com DHT11...");
  delay(2000); // O DHT11 demora um pouco para estabilizar
}

void loop() {
  // --- Leitura da Luminosidade ---
  int leituraLuz = analogRead(SENSOR_LUZ);

  // --- Leitura do DHT11 ---
  // O DHT11 é lento, pode levar até 2 segundos para ler
  float umidade = dht.readHumidity();    // Lê a umidade do ar
  float temperatura = dht.readTemperature(); // Lê a temperatura em Celsius

  // Verifica se houve falha na leitura do sensor
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor DHT11! Verifique os cabos.");
    // Pisca o LED vermelho para indicar erro de hardware
    digitalWrite(ledRed, HIGH);
    delay(500);
    digitalWrite(ledRed, LOW);
    return; // Sai do loop e tenta de novo
  }

  // --- Exibe os dados no Monitor Serial ---
  Serial.print("Temp: ");
  Serial.print(temperatura);
  Serial.print(" °C | Umid Ar: ");
  Serial.print(umidade);
  Serial.print(" % | Luz: ");
  Serial.println(leituraLuz);

  // --- Lógica de Controle da Temperatura ---
  // A lógica permanece a mesma, mas agora usa a variável 'temperatura' correta do DHT
  
  if ((temperatura >= 28 && temperatura <= 34) || (temperatura >= 5 && temperatura <= 10)) {
    // Estado de Atenção
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    noTone(piezo);
  } 
  else if (temperatura > 35 || temperatura < 5) {
    // Estado de Alerta/Perigo
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    tone(piezo, 1000, 250); 
  } 
  else {
    // Estado Ideal
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    noTone(piezo);
  }

  // --- Lógica de Controle da Iluminação ---
  if (leituraLuz < LIMITE_LUZ) {
    digitalWrite(releLuz, LOW); // Liga luz (relé ativado em LOW)
  } else {
    digitalWrite(releLuz, HIGH); // Desliga luz
  }

  // Delay de 2 segundos (o DHT11 não consegue ler mais rápido que isso)
  delay(2000);
}