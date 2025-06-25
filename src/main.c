/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include <avr/interrupt.h>

#include "balance.h"
#include "kalman.h"
#include "led.h"
#include "motor.h"
#include "mpu6050.h"
#include "serial.h"
#include "timer.h"
#include "vectors.h"

#define MIN(A, B) ((A < B) ? A : B)

static void setup() {
  usartInit();
  uartPrint("+ usart\r\n");

  initLED();
  uartPrint("+ led\r\n");

  initTimers();
  uartPrint("+ timers\r\n");

  // Setup motors
  initPWM();
  uartPrint("+ pwm\r\n");
  initMotors();
  uartPrint("+ motors\r\n");
  enableMotors();
  uartPrint("+ motors enabled\r\n");

  // Setup timed measurements
  initEncoders();
  uartPrint("+ encoders\r\n");

  // Setup mpu6050
  initMPU6050();
  uartPrint("+ mpu6050\r\n");
  configureAccelerometer(RANGE_2G);  // +/- 2g over 16bit range
  uartPrint("+ accel\r\n");
  configureGyrometer(RANGE_250);  // +/- 250 º/s over 16bit range
  uartPrint("+ gyro\r\n");

  sei();
}

int main() {
  setup();
  uartPrint("+ setup\r\n");

  // Setup Kalman filter and state
  Kalman_t kf;
  initKalmanFilter(&kf);

  float balancingPower = 0.0f;
  float desire         = 0.0f;
  vec3 accel, gyro;

  static unsigned long lastMillis = 0;
  while (1) {
    float dt   = (millis - lastMillis) / 1000.0f;
    lastMillis = millis;
    if (dt <= 0) {
      dt = 0.001;
    }

    readGyrometer(&gyro);
    readAccelerometer(&accel);
    float pitch      = updateKalmanFilter(&kf, &accel, &gyro, &dt);
    float speed      = (rightWheelPulses + leftWheelPulses) / 2.0 * dt;
    leftWheelPulses  = 0;
    rightWheelPulses = 0;
    float d          = (0.5 * pitch) + (0.5 * speed);
    uartPrintf("speed=%f\r\n", speed);
    balancingPower = pitchPID(&d, &desire, &dt);

    if (accel.z < 0.01) {
      balancingPower = 0;
    } else if (balancingPower < 0) {
      balancingPower *= -1.0;
      forward();
    } else {
      reverse();
    }

    balancingPower *= 2.83333333333f;
    balancingPower = MIN(balancingPower, 255);
    setSpeed(balancingPower);
  }

  return 0;
}
