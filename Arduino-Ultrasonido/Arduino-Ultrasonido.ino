#include <NewPing.h>

// Pines del sensor ultrasónico
const int trigPin = 8;
const int echoPin = 9;

// Crear objeto del sensor ultrasónico
NewPing sonar(trigPin, echoPin);

void setup() {
  Serial.begin(9600); // Iniciar comunicación serial
  Serial.println("Iniciando prueba del sensor ultrasónico...");
}

void loop() {
  int distancia = sonar.ping_cm(); // Medir distancia en cm

  if (distancia > 0) {
    Serial.print("Distancia medida: ");
    Serial.print(distancia);
    Serial.println(" cm");
  } else {
    Serial.println("No se detecta eco (verifica conexiones o rango)");
  }

  delay(1000); // Esperar 1 segundo antes de la siguiente medición
}
