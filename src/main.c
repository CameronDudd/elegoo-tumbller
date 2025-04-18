/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"
#include "button.h"
#include "kalman.h"
#include "led.h"
#include "motor.h"
#include "mpu6050.h"
#include "serial.h"
#include "timer.h"
#include "vectors.h"

#ifdef UNIT_TEST
#include "mock_avr_delay.h"
#else
#include <util/delay.h>
#endif

int main() {
  // Give everything a second to stabilise (especially Bluetooth module)
  _delay_ms(1000);

  // First thing to setup to allow display of error codes
  initLED();

  // Setup serial
  usartInit();
  uartPrint("+ serial initialised\r\n");

  // Setup motors
  initPWM();
  initMotors();
  uartPrint("+ motors initialised\r\n");
  enableMotors();
  uartPrintf("+ motors enabled\r\n");

  // Setup timed measurements
  initEncoders();
  uartPrintf("+ encoders ready\r\n");

  initTimers();
  uartPrintf("+ timers ready\r\n");

  initButtons();
  uartPrintf("+ buttons ready\r\n");

  // Setup mpu6050
  initMPU6050();
  uartPrintf("+ mpu6050 initialised\r\n");
  configureAccelerometer(RANGE_2G); // +/- 2g over 16bit range
  configureGyrometer(RANGE_250);    // +/- 250 º/s over 16bit range
  uartPrintf("+ accelerometers configured to +/- 2g\r\n");

  // Setup Kalman filter and state
  Kalman_t kf;
  initKalmanFilter(&kf);

  double desiredAngle = 0.0, balancingPower = 0.0;
  vec3 accel, gyro;

  static unsigned long lastMillis = 0;
  while (1) {
    double dt = (millis - lastMillis) / 1000.0;
    lastMillis = millis;
    if (dt <= 0) {
      dt = 0.00001;
    }

    readGyrometer(&gyro);
    readAccelerometer(&accel);
    double pitch = updateKalmanFilter(&kf, &accel, &gyro, &dt);
    balancingPower = pitchPID(&pitch, &desiredAngle, &dt);

    if (accel.z < 0.01) {
      balancingPower = 0;
    } else if (balancingPower < 0) {
      balancingPower *= -1.0;
      forward();
    } else {
      reverse();
    }

    setSpeed((state == BALANCE) ? balancingPower : 0);
  }

  return 0;
}
