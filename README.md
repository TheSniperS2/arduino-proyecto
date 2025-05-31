# 🤖 Robot con Servomotor y Sensor Ultrasónico (Arduino UNO)

Este proyecto implementa un sistema de escaneo utilizando un servomotor controlado por una placa Arduino UNO. Está diseñado para ser la base de un robot que utiliza un sensor ultrasónico montado sobre el servo para detectar obstáculos en su entorno.

---

## 🛠️ Componentes utilizados

- Arduino UNO
- Servomotor (SG90 o similar)
- Sensor ultrasónico HC-SR04 (opcional en esta versión)
- Jumpers
- Protoboard (opcional)

---

## ⚙️ Funcionamiento

El programa mueve el servomotor desde 0° hasta 180° y luego de regreso a 0°, en pasos de 1°. Cada posición se mantiene durante 15 ms para permitir que el servo alcance la posición deseada.

Este comportamiento es ideal para realizar un barrido horizontal con un sensor ultrasónico, permitiendo al robot escanear su entorno y detectar obstáculos o paredes.

---

## 📄 Código principal

El código se encuentra en el archivo `robot_servo.ino` e incluye:

- Importación de la librería `Servo.h`
- Inicialización del servomotor en el pin digital 10
- Bucle continuo de movimiento de barrido
