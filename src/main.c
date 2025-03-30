/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "interrupts.h"
#include "motor.h"
#include "mpu6050.h"
#include "serial.h"

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

  // Setup speed measurement
  initEncoders();
  initTimers();
  uartPrintf("+ measurements ready\r\n");

  // Setup mpu6050
  initMPU6050();
  uartPrintf("+ mpu6050 initialised\r\n");
  configureAccelerometer(RANGE_2G); // +/- 2g over 16bit range
  uartPrintf("+ accelerometers configured to +/- 2g\r\n");

  int16_t ax, ay, az;
  while (1) {
    readAccelerometer(&ax, &ay, &az);
    uartPrintf("time=%7i axg=%7i ayg=%7i azg=%7i\r\n", ax, ay, az);
  }

  return 0;
}
