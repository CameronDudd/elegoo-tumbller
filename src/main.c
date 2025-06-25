/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include <avr/interrupt.h>

#include "balance.h"
#include "button.h"
#include "kalman.h"
#include "led.h"
#include "motor.h"
#include "mpu6050.h"
#include "serial.h"
#include "timer.h"
#include "vectors.h"

#define MIN(A, B) ((A < B) ? A : B)

PIDCtx pitchPIDCtx = {
    .KP            = 20.0,
    .KI            = 0.05,
    .KD            = 0.5,
    .integralError = 0.0,
    .previousError = 0.0,
};

PIDCtx speedPIDCtx = {
    .KP            = 0.0,
    .KI            = 0.0,
    .KD            = 0.0,
    .integralError = 0.0,
    .previousError = 0.0,
};

static void setup() {
  usartInit();
  uartPrint("+ usart\r\n");

  initLED();
  uartPrint("+ led\r\n");

  // initTimers();
  uartPrint("+ timers\r\n");

  // Setup motor encoders
  initEncoders();
  uartPrint("+ encoders\r\n");

  // Setup motors
  initPWM();
  uartPrint("+ pwm\r\n");
  initMotors();
  uartPrint("+ motors\r\n");
  enableMotors();
  uartPrint("+ motors enabled\r\n");

  // Setup buttons
  initButtons();

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

  float pitchPower   = 0.0f;
  float desiredPitch = 0.0f;
  vec3 accel, gyro;

  static unsigned long lastMillis = 0;
  while (1) {
    float dt = (millis - lastMillis) / 1000.0f;
    if (dt <= 0 || dt > 0.2f) dt = 0.01f;
    lastMillis = millis;
    if (dt <= 0) {
      dt = 0.001;
    }

    readGyrometer(&gyro);
    readAccelerometer(&accel);
    float pitch      = updateKalmanFilter(&kf, &accel, &gyro, &dt);
    float speed      = ((rightWheelPulses + leftWheelPulses) / 2.0) / dt;
    leftWheelPulses  = 0;
    rightWheelPulses = 0;
    uartPrintf("speed=%f\r\n", speed);

    desiredPitch = outputFromPID(&speedPIDCtx, speed, 0.0f, dt);

    if (desiredPitch > 10.0f) desiredPitch = 10.0f;
    if (desiredPitch < -10.0f) desiredPitch = -10.0f;

    pitchPower = outputFromPID(&pitchPIDCtx, pitch, desiredPitch, dt);

    if (accel.z < 0.01f) {
      pitchPower = 0;
      setSpeed(0);
      stop();
    } else {
      if (pitchPower < 0) {
        pitchPower *= -1.0f;
        forward();
      } else {
        reverse();
      }
    }

    if (pitchPower > 255.0f) pitchPower = 255.0f;
    if (pitchPower < 0.0f) pitchPower = 0.0f;

    setSpeed(pitchPower);
  }

  return 0;
}
