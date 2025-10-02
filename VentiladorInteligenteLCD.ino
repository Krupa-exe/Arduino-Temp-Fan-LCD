#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

// Definir endereço do módulo
LiquidCrystal_I2C lcd(32, 16, 2); 

// Definição dos Pinos
const int sensorPin = A0;   // Sensor TMP está conectado ao pino Analógico A0
const int motorPin = 9;     // Motor está conectado ao pino Digital 9
const int ledPin = 8;		// Led está conectado ao pino Digital 8

// Limite de Temperatura para Ligar o Ventilador
const float limiteTemperaturaC = 27.0; 

void setup() {
  // Configura o pino do motor como SAÍDA
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  // Inicia a comunicação serial (opcional, mas bom para debug)
  Serial.begin(9600);

  // Configuração de Inicialização do LCD I2C
  lcd.init();      
  lcd.backlight(); 
  lcd.display();

  // Mensagem de Inicialização no LCD
  lcd.setCursor(0, 0); // Posição (coluna, linha)
  lcd.print("SMART FAN");
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(1500);
}

void loop() {
  // 1. Leitura do Sensor (valor de 0 a 1023)
  int valorAnalogico = analogRead(sensorPin);

  // 2. Converte o valor analógico em Milivolts (mV)
  // 5000.0 (mV) / 1024.0 (passos)
  float tensao_mv = valorAnalogico * (5000.0 / 1024.0); 

  // 3. Converte a tensão em Graus Celsius
  float temperaturaC = (tensao_mv - 500) / 10.0;
  
  // 4. --- Exibe o resultado no LCD ---
  lcd.clear(); // Limpa o display
  
  // PRIMEIRA LINHA: Temperatura
  lcd.setCursor(0, 0); 
  lcd.print("Temp: ");
  lcd.print(temperaturaC, 1); // Exibe com 1 casa decimal
  lcd.print(" C");

  // SEGUNDA LINHA: Status do Ventilador
  lcd.setCursor(0, 1);
  if (temperaturaC > limiteTemperaturaC) {
    // Se a temperatura estiver acima do limite, LIGA o Motor e o Led
    digitalWrite(motorPin, HIGH);
    digitalWrite(ledPin, HIGH);
    lcd.print("Status: ON");
 
  } else {
    // Se estiver abaixo do limite, DESLIGA o Motor e o Led
    digitalWrite(motorPin, LOW);
    digitalWrite(ledPin, LOW);
    lcd.print("Status: OFF");
    
  }

  delay(1500); // Aguarda 1,5 segundos
}