#include <Servo.h>
#include <NewPing.h>

// Pines del motor
const int motorIzquierdoAdelante = 7;
const int motorIzquierdoAtras = 6;
const int motorDerechoAdelante = 5;
const int motorDerechoAtras = 4;

// Pines del sensor ultrasónico
const int pinTrig = 8;
const int pinEcho = 9;

Servo miServo;
NewPing sonar(pinTrig, pinEcho);

unsigned long ultimoTiempoMedicion = 0;
const unsigned long intervaloDeMedicion = 2000; // 2 segundos

void setup() {
  Serial.begin(9600);

  pinMode(motorIzquierdoAdelante, OUTPUT);
  pinMode(motorIzquierdoAtras, OUTPUT);
  pinMode(motorDerechoAdelante, OUTPUT);
  pinMode(motorDerechoAtras, OUTPUT);

  miServo.attach(10);
  miServo.write(90);
}

void loop() {
  if (millis() - ultimoTiempoMedicion >= intervaloDeMedicion) {
    int distancia = medirDistancia();
    Serial.print("Distancia: ");
    Serial.println(distancia);

    int umbral = 20;

    if (distancia > umbral) {
      avanzarDistancia(distancia);
    } else {
      evitarObstaculo();
    }

    ultimoTiempoMedicion = millis();
  }
}

int medirDistancia() {
  return sonar.ping_cm();
}

void detenerMovimiento() {
  digitalWrite(motorIzquierdoAdelante, LOW);
  digitalWrite(motorIzquierdoAtras, LOW);
  digitalWrite(motorDerechoAdelante, LOW);
  digitalWrite(motorDerechoAtras, LOW);
}

void avanzarConPWM(int velocidad) {
  velocidad = constrain(velocidad, 0, 255);

  analogWrite(motorIzquierdoAdelante, velocidad);
  digitalWrite(motorIzquierdoAtras, LOW);
  analogWrite(motorDerechoAdelante, velocidad);
  digitalWrite(motorDerechoAtras, LOW);
}

void retroceder() {
  digitalWrite(motorIzquierdoAdelante, LOW);
  digitalWrite(motorIzquierdoAtras, HIGH);
  digitalWrite(motorDerechoAdelante, LOW);
  digitalWrite(motorDerechoAtras, HIGH);
}

void girarIzquierda() {
  digitalWrite(motorIzquierdoAdelante, LOW);
  digitalWrite(motorIzquierdoAtras, HIGH);
  digitalWrite(motorDerechoAdelante, HIGH);
  digitalWrite(motorDerechoAtras, LOW);
}

void girarDerecha() {
  digitalWrite(motorIzquierdoAdelante, HIGH);
  digitalWrite(motorIzquierdoAtras, LOW);
  digitalWrite(motorDerechoAdelante, LOW);
  digitalWrite(motorDerechoAtras, HIGH);
}

void girar180() {
  digitalWrite(motorIzquierdoAdelante, HIGH);
  digitalWrite(motorIzquierdoAtras, LOW);
  digitalWrite(motorDerechoAdelante, LOW);
  digitalWrite(motorDerechoAtras, HIGH);
  delay(2000);
}

void evitarObstaculo() {
  detenerMovimiento();

  miServo.write(180);
  delay(2000);
  int distanciaIzquierda = medirDistancia();

  miServo.write(0);
  delay(2000);
  int distanciaDerecha = medirDistancia();

  miServo.write(90);
  delay(2000);

  if (distanciaIzquierda > distanciaDerecha && distanciaIzquierda > 20) {
    girarIzquierda();
    delay(500);
    detenerMovimiento();
  } else if (distanciaDerecha > 20) {
    girarDerecha();
    delay(500);
    detenerMovimiento();
  } else {
    girar180();
    detenerMovimiento();
  }
}

void avanzarDistancia(int distancia) {
  int velocidad = map(distancia, 0, 100, 100, 255);

  if (distancia < 5) {
    detenerMovimiento();
    return;
  }

  int tiempoAvance = map(distancia, 0, 100, 500, 1500);

  avanzarConPWM(velocidad);
  delay(tiempoAvance);
  detenerMovimiento();
}
