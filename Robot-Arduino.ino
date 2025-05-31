#include <Servo.h>

Servo miServo;

void setup() {
  miServo.attach(10);  // Pin donde está conectado el servo
}

void loop() {
  // Mover de 0 a 180 grados
  for (int angulo = 0; angulo <= 180; angulo += 1) {
    miServo.write(angulo);
    delay(15);  // Pequeña pausa para que el servo alcance la posición
  }
  delay(15);
  // Mover de 180 a 0 grados
  for (int angulo = 180; angulo >= 0; angulo -= 1) {
    miServo.write(angulo);
    delay(15);
  }
  delay(15);
}
