/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"
#include "interrupts.h"
#include "motor.h"
#include "mpu6050.h"
#include "serial.h"
#include "vectors.h"

int main() {
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
  initTimers();
  uartPrintf("+ measurements ready\r\n");

  // Setup mpu6050
  initMPU6050();
  uartPrintf("+ mpu6050 initialised\r\n");
  configureAccelerometer(RANGE_2G); // +/- 2g over 16bit range
  configureGyrometer(RANGE_250);    // +/- 250 º/s over 16bit range
  uartPrintf("+ accelerometers configured to +/- 2g\r\n");

  unsigned long lastMillis = 0;
  double desiredAngle = 0.0, balancingPower = 0.0;
  vec3 accel, gyro;
  while (1) {
    while ( // FIXME (cameron): use fast timer between measurements
        (millis - lastMillis) < 100) {
      readGyrometer(&gyro);
      readAccelerometer(&accel);
    }
    balancingPower = pitchPID(&accel, &desiredAngle);
    if (balancingPower < 0) {
      balancingPower *= -1.0;
      forward();
    } else {
      reverse();
    }
    uartPrintf("%f\r\n", balancingPower);
    setSpeed(balancingPower);
    lastMillis = millis;
  }

  return 0;
}
