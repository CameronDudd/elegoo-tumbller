/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"
#include "button.h"
#include "motor.h"
#include "mpu6050.h"
#include "serial.h"
#include "timer.h"
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

  double desiredAngle = 0.0, balancingPower = 0.0;
  vec3 accel, gyro;
  while (1) {
    readGyrometer(&gyro);
    readAccelerometer(&accel);
    balancingPower = pitchPID(&accel, &gyro, &desiredAngle);
    if (accel.z < 0.01) {
      balancingPower = 0;
    } else if (balancingPower < 0) {
      balancingPower *= -1.0;
      forward();
    } else {
      reverse();
    }
    balancingPower *= (255.0 / 90.0);
    if (balancingPower > 255) {
      balancingPower = 255;
    }
    uartPrintf("state=%i %f\r\n", state, balancingPower);
    setSpeed((state == BALANCE) ? balancingPower : 0);
  }

  return 0;
}
