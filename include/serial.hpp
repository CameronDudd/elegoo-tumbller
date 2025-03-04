/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef SERIAL_H
#define SERIAL_H

class Serial {
 public:
  Serial();
  void uart_print(const char *str);

 private:
  void _uart_transmit(unsigned char data);
};

#endif  // SERIAL_H
