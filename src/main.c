/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#include <avr/interrupt.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>

#include "button.h"
#include "command.h"
#include "elegooKit.h"
#include "filter.h"
#include "i2c.h"
#include "motor.h"
#include "mpu6050.h"
#include "pid.h"
#include "pwm.h"
#include "serial.h"
#include "stdbool.h"
#include "timer.h"
#include "vectors.h"

#define ALPHA 0.975f  // 1.0 GYRO ; 0.0 ACCEL
#define DT_S 0.01f
#define PITCH_THRESHOLD 30.0f
#define MOTOR_MIN_PWM 8.0f

#define BALANCE_DT_MS 10
#define COMMAND_DT_MS 1000
#define PARSE_SERIAL_BUFF_DT_MS 200

#define PitchKp 15.0f
#define PitchKi 50.0f
#define PitchKd 0.0f

#define PosKp 0.0f
#define PosKi 0.0f
#define PosKd 0.0f

#define MAX_PITCH_OFFSET 1.5f

bool shouldBalance = true;

vec3 gyroVec;
vec3 accelVec;

CompFilter pitchFilter;
PIDController pitchPID;
PIDController positionPID;
SerialParser serialParser;

static void _reset(void) {
  resetPIDController(&pitchPID);
  resetPIDController(&positionPID);
  resetEncoders();
  setMotorsPercent(0);
}

void init() {
  initUsart();
  uartPrint("Usart init\r\n");

  initEncoders();
  uartPrint("Encoders init\r\n");

  pwmInit();
  uartPrint("PWM init\r\n");

  initMotors();
  enableMotors();
  uartPrint("Motors init\r\n");

  i2cInit();
  uartPrint("i2c init\r\n");

  mpu6050Init();
  uartPrint("MPU init\r\n");

  timersInit();
  uartPrint("Timers init\r\n");

  buttonsInit();
  uartPrint("Buttons init\r\n");

  initCompFilter(&pitchFilter, ALPHA, DT_S, 0.0);
  uartPrint("Pitch filter init\r\n");

  initPIDController(&pitchPID, PitchKp, PitchKi, PitchKd, DT_S, 100.0f);
  uartPrint("Pitch PID init\r\n");

  initPIDController(&positionPID, PosKp, PosKi, PosKd, DT_S, 5.0f);
  uartPrint("Position PID init\r\n");

  initSerialParser(&serialParser);
  uartPrint("Serial parser init\r\n");

  sei();
}

static void doBalance(void) {
  readAccelerometer(&accelVec);
  readGyrometer(&gyroVec);

  float accelAngle   = atan2(accelVec.y, accelVec.z) * (180.0 / M_PI);
  float gyroRate     = gyroVec.x;
  float currentPitch = updateCompFilter(&pitchFilter, accelAngle, gyroRate);

  if (fabs(accelAngle) > PITCH_THRESHOLD) {
    _reset();
    return;
  }

  int32_t leftPos       = getLeftWheelPulses();
  int32_t rightPos      = getRightWheelPulses();
  float currentPosition = (float)(leftPos + rightPos) / 2.0f;

  float targetPitch = updatePIDController(&positionPID, 0.0f, currentPosition);

  if (targetPitch > MAX_PITCH_OFFSET) {
    targetPitch = MAX_PITCH_OFFSET;
  } else if (targetPitch < -MAX_PITCH_OFFSET) {
    targetPitch = -MAX_PITCH_OFFSET;
  }

  float output = updatePIDController(&pitchPID, targetPitch, currentPitch);

  if (output > 100.0f) {
    output = 100.0f;
  } else if (output < -100.0f) {
    output = -100.0f;
  }

  setMotorsPercent(-output);
}

void doCommand(void) {
  Command cmd;
  if (popCmd(&cmd)) {
    switch (cmd.type) {
      case GET:
        if (strcmp(cmd.key, "pos") == 0) {
          uartPrintf("POSITION kp=%f ki=%f kd=%f\r\n", pitchPID.Kp, pitchPID.Ki, pitchPID.Kd);
        } else if (strcmp(cmd.key, "dis") == 0) {
          uartPrintf("DISTANCE kp=%f ki=%f kd=%f\r\n", positionPID.Kp, positionPID.Ki, positionPID.Kd);
        } else {
          uartPrintf("Cannot get value for key: %s\r\n", cmd.key);
        }
        break;

      case SET:
        if (strcmp(cmd.key, "posp") == 0) {
          pitchPID.Kp = cmd.value;
          uartPrintf("kp=%f\r\n", pitchPID.Kp);
        } else if (strcmp(cmd.key, "posi") == 0) {
          pitchPID.Ki = cmd.value;
          uartPrintf("ki=%f\r\n", pitchPID.Ki);
        } else if (strcmp(cmd.key, "posd") == 0) {
          pitchPID.Kd = cmd.value;
          uartPrintf("kd=%f\r\n", pitchPID.Kd);
        } else if (strcmp(cmd.key, "disp") == 0) {
          positionPID.Kp = cmd.value;
          uartPrintf("kp=%f\r\n", positionPID.Kp);
        } else if (strcmp(cmd.key, "disi") == 0) {
          positionPID.Ki = cmd.value;
          uartPrintf("ki=%f\r\n", positionPID.Ki);
        } else if (strcmp(cmd.key, "disd") == 0) {
          positionPID.Kd = cmd.value;
          uartPrintf("kd=%f\r\n", positionPID.Kd);
        } else {
          uartPrintf("Cannot set value for key: %s\r\n", cmd.key);
        }

        _reset();
        break;

      default:
        uartPrintf("Bad command type %i\r\n", cmd.type);
        break;
    }
  }
}

int main() {
  init();

  uint32_t lastBalanceTime         = 0;
  uint32_t lastReportTime          = 0;
  uint32_t lastParseSerialBuffTime = 0;

  while (1) {
    uint32_t currentTime = getMillis();

    if (shouldBalance && (currentTime - lastBalanceTime >= BALANCE_DT_MS)) {
      lastBalanceTime = currentTime;
      doBalance();
    }

    if (currentTime - lastParseSerialBuffTime >= PARSE_SERIAL_BUFF_DT_MS) {
      lastParseSerialBuffTime = currentTime;
      readSerialBuff(&serialParser);
    }

    if (currentTime - lastReportTime >= COMMAND_DT_MS) {
      lastReportTime = currentTime;
      doCommand();
    }
  }
}
