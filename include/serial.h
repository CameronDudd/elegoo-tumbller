/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef SERIAL_H
#define SERIAL_H

void usart_init();
void uart_print(const char *str);
void uart_printf(const char *format, ...);

#endif  // SERIAL_H
