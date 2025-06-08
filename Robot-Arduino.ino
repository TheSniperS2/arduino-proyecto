#include <Servo.h>
#include <NewPing.h>

// Pines del sensor ultrasónico
const int trigPin = 8;
const int echoPin = 9;

// Crear objeto del sensor
NewPing sonar(trigPin, echoPin);

// Crear objeto del servomotor
Servo miServo;

void setup() {
  Serial.begin(9600);             // Iniciar comunicación serial
  miServo.attach(10);             // Conectar el servomotor al pin 10
  Serial.println("Iniciando prueba del conjunto servomotor + sensor ultrasónico...");
}

void loop() {
  // Girar el servo de 0 a 180 grados en pasos de 30°
  for (int angulo = 0; angulo <= 180; angulo += 30) {
    miServo.write(angulo);        // Mover servo
    delay(500);                   // Esperar que el servo se acomode

    int distancia = sonar.ping_cm(); // Medir distancia

    // Mostrar la información
    Serial.print("Ángulo: ");
    Serial.print(angulo);
    Serial.print("° - ");

    if (distancia > 0) {
      Serial.print("Distancia: ");
      Serial.print(distancia);
      Serial.println(" cm");
    } else {
      Serial.println("No se detecta eco");
    }

    delay(1000);  // Esperar antes de continuar al siguiente ángulo
  }

  // Girar de regreso de 180 a 0 grados
  for (int angulo = 180; angulo >= 0; angulo -= 30) {
    miServo.write(angulo);
    delay(500);

    int distancia = sonar.ping_cm();

    Serial.print("Ángulo: ");
    Serial.print(angulo);
    Serial.print("° - ");

    if (distancia > 0) {
      Serial.print("Distancia: ");
      Serial.print(distancia);
      Serial.println(" cm");
    } else {
      Serial.println("No se detecta eco");
    }

    delay(1000);
  }
}
