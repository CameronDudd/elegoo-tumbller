/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MOCK_AVR_IO_H
#define MOCK_AVR_IO_H

#include <stdint.h>

#define ISR(VECTOR) void VECTOR()

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

extern volatile uint8_t PINB;
#define PINB0 0
#define PINB1 1
#define PINB2 2
#define PINB3 3
#define PINB4 4
#define PINB5 5
#define PINB6 6
#define PINB7 7

extern volatile uint8_t DDRB;
#define DDB0 0
#define DDB1 1
#define DDB2 2
#define DDB3 3
#define DDB4 4
#define DDB5 5
#define DDB6 6
#define DDB7 7

extern volatile uint8_t PORTB;
#define PORTB0 0
#define PORTB1 1
#define PORTB2 2
#define PORTB3 3
#define PORTB4 4
#define PORTB5 5
#define PORTB6 6
#define PORTB7 7

extern volatile uint8_t PINC;
#define PINC0 0
#define PINC1 1
#define PINC2 2
#define PINC3 3
#define PINC4 4
#define PINC5 5
#define PINC6 6

extern volatile uint8_t DDRC;
#define DDC0 0
#define DDC1 1
#define DDC2 2
#define DDC3 3
#define DDC4 4
#define DDC5 5
#define DDC6 6

extern volatile uint8_t PORTC;
#define PORTC0 0
#define PORTC1 1
#define PORTC2 2
#define PORTC3 3
#define PORTC4 4
#define PORTC5 5
#define PORTC6 6

extern volatile uint8_t PIND;
#define PIND0 0
#define PIND1 1
#define PIND2 2
#define PIND3 3
#define PIND4 4
#define PIND5 5
#define PIND6 6
#define PIND7 7

extern volatile uint8_t DDRD;
#define DDD0 0
#define DDD1 1
#define DDD2 2
#define DDD3 3
#define DDD4 4
#define DDD5 5
#define DDD6 6
#define DDD7 7

extern volatile uint8_t PORTD;
#define PORTD0 0
#define PORTD1 1
#define PORTD2 2
#define PORTD3 3
#define PORTD4 4
#define PORTD5 5
#define PORTD6 6
#define PORTD7 7

extern volatile uint8_t TIFR0;
#define TOV0 0
#define OCF0A 1
#define OCF0B 2

extern volatile uint8_t TIFR1;
#define TOV1 0
#define OCF1A 1
#define OCF1B 2
#define ICF1 5

extern volatile uint8_t TIFR2;
#define TOV2 0
#define OCF2A 1
#define OCF2B 2

extern volatile uint8_t PCIFR;
#define PCIF0 0
#define PCIF1 1
#define PCIF2 2

extern volatile uint8_t EIFR;
#define INTF0 0
#define INTF1 1

extern volatile uint8_t EIMSK;
#define INT0 0
#define INT1 1

extern volatile uint8_t GPIOR0;
#define GPIOR00 0
#define GPIOR01 1
#define GPIOR02 2
#define GPIOR03 3
#define GPIOR04 4
#define GPIOR05 5
#define GPIOR06 6
#define GPIOR07 7

extern volatile uint8_t EECR;
#define EERE 0
#define EEPE 1
#define EEMPE 2
#define EERIE 3
#define EEPM0 4
#define EEPM1 5

extern volatile uint8_t EEDR;
#define EEDR0 0
#define EEDR1 1
#define EEDR2 2
#define EEDR3 3
#define EEDR4 4
#define EEDR5 5
#define EEDR6 6
#define EEDR7 7

extern volatile uint8_t EEAR;

extern volatile uint8_t EEARL;
#define EEAR0 0
#define EEAR1 1
#define EEAR2 2
#define EEAR3 3
#define EEAR4 4
#define EEAR5 5
#define EEAR6 6
#define EEAR7 7

extern volatile uint8_t EEARH;
#define EEAR8 0
#define EEAR9 1

#define _EEPROM_REG_LOCATIONS_ 1F2021

extern volatile uint8_t GTCCR;
#define PSRSYNC 0
#define PSRASY 1
#define TSM 7

extern volatile uint8_t TCCR0A;
#define WGM00 0
#define WGM01 1
#define COM0B0 4
#define COM0B1 5
#define COM0A0 6
#define COM0A1 7

extern volatile uint8_t TCCR0B;
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM02 3
#define FOC0B 6
#define FOC0A 7

extern volatile uint8_t TCNT0;
#define TCNT0_0 0
#define TCNT0_1 1
#define TCNT0_2 2
#define TCNT0_3 3
#define TCNT0_4 4
#define TCNT0_5 5
#define TCNT0_6 6
#define TCNT0_7 7

extern volatile uint8_t OCR0A;
#define OCR0A_0 0
#define OCR0A_1 1
#define OCR0A_2 2
#define OCR0A_3 3
#define OCR0A_4 4
#define OCR0A_5 5
#define OCR0A_6 6
#define OCR0A_7 7

extern volatile uint8_t OCR0B;
#define OCR0B_0 0
#define OCR0B_1 1
#define OCR0B_2 2
#define OCR0B_3 3
#define OCR0B_4 4
#define OCR0B_5 5
#define OCR0B_6 6
#define OCR0B_7 7

extern volatile uint8_t GPIOR1;
#define GPIOR10 0
#define GPIOR11 1
#define GPIOR12 2
#define GPIOR13 3
#define GPIOR14 4
#define GPIOR15 5
#define GPIOR16 6
#define GPIOR17 7

extern volatile uint8_t GPIOR2;
#define GPIOR20 0
#define GPIOR21 1
#define GPIOR22 2
#define GPIOR23 3
#define GPIOR24 4
#define GPIOR25 5
#define GPIOR26 6
#define GPIOR27 7

extern volatile uint8_t SPCR;
#define SPR0 0
#define SPR1 1
#define CPHA 2
#define CPOL 3
#define MSTR 4
#define DORD 5
#define SPE 6
#define SPIE 7

extern volatile uint8_t SPSR;
#define SPI2X 0
#define WCOL 6
#define SPIF 7

extern volatile uint8_t SPDR;
#define SPDR0 0
#define SPDR1 1
#define SPDR2 2
#define SPDR3 3
#define SPDR4 4
#define SPDR5 5
#define SPDR6 6
#define SPDR7 7

extern volatile uint8_t ACSR;
#define ACIS0 0
#define ACIS1 1
#define ACIC 2
#define ACIE 3
#define ACI 4
#define ACO 5
#define ACBG 6
#define ACD 7

extern volatile uint8_t SMCR;
#define SE 0
#define SM0 1
#define SM1 2
#define SM2 3

extern volatile uint8_t MCUSR;
#define PORF 0
#define EXTRF 1
#define BORF 2
#define WDRF 3

extern volatile uint8_t MCUCR;
#define IVCE 0
#define IVSEL 1
#define PUD 4
#define BODSE 5
#define BODS 6

extern volatile uint8_t SPMCSR;
#define SELFPRGEN                                     \
  0 /* only for backwards compatibility with previous \
     * avr-libc versions; not an official name */
#define SPMEN 0
#define PGERS 1
#define PGWRT 2
#define BLBSET 3
#define RWWSRE 4
#define SIGRD 5
#define RWWSB 6
#define SPMIE 7

extern volatile uint8_t WDTCSR;
#define WDP0 0
#define WDP1 1
#define WDP2 2
#define WDE 3
#define WDCE 4
#define WDP3 5
#define WDIE 6
#define WDIF 7

extern volatile uint8_t CLKPR;
#define CLKPS0 0
#define CLKPS1 1
#define CLKPS2 2
#define CLKPS3 3
#define CLKPCE 7

extern volatile uint8_t PRR;
#define PRADC 0
#define PRUSART0 1
#define PRSPI 2
#define PRTIM1 3
#define PRTIM0 5
#define PRTIM2 6
#define PRTWI 7

#define __AVR_HAVE_PRR ((1 << PRADC) | (1 << PRUSART0) | (1 << PRSPI) | (1 << PRTIM1) | (1 << PRTIM0) | (1 << PRTIM2) | (1 << PRTWI))
#define __AVR_HAVE_PRR_PRADC
#define __AVR_HAVE_PRR_PRUSART0
#define __AVR_HAVE_PRR_PRSPI
#define __AVR_HAVE_PRR_PRTIM1
#define __AVR_HAVE_PRR_PRTIM0
#define __AVR_HAVE_PRR_PRTIM2
#define __AVR_HAVE_PRR_PRTWI

extern volatile uint8_t OSCCAL;
#define CAL0 0
#define CAL1 1
#define CAL2 2
#define CAL3 3
#define CAL4 4
#define CAL5 5
#define CAL6 6
#define CAL7 7

extern volatile uint8_t PCICR;
#define PCIE0 0
#define PCIE1 1
#define PCIE2 2

extern volatile uint8_t EICRA;
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

extern volatile uint8_t PCMSK0;
#define PCINT0 0
#define PCINT1 1
#define PCINT2 2
#define PCINT3 3
#define PCINT4 4
#define PCINT5 5
#define PCINT6 6
#define PCINT7 7

extern volatile uint8_t PCMSK1;
#define PCINT8 0
#define PCINT9 1
#define PCINT10 2
#define PCINT11 3
#define PCINT12 4
#define PCINT13 5
#define PCINT14 6

extern volatile uint8_t PCMSK2;
#define PCINT16 0
#define PCINT17 1
#define PCINT18 2
#define PCINT19 3
#define PCINT20 4
#define PCINT21 5
#define PCINT22 6
#define PCINT23 7

extern volatile uint8_t TIMSK0;
#define TOIE0 0
#define OCIE0A 1
#define OCIE0B 2

extern volatile uint8_t TIMSK1;
#define TOIE1 0
#define OCIE1A 1
#define OCIE1B 2
#define ICIE1 5

extern volatile uint8_t TIMSK2;
#define TOIE2 0
#define OCIE2A 1
#define OCIE2B 2

#ifndef __ASSEMBLER__
extern volatile uint16_t ADC;
#endif
extern volatile uint16_t ADCW;

extern volatile uint8_t ADCL;
#define ADCL0 0
#define ADCL1 1
#define ADCL2 2
#define ADCL3 3
#define ADCL4 4
#define ADCL5 5
#define ADCL6 6
#define ADCL7 7

extern volatile uint8_t ADCH;
#define ADCH0 0
#define ADCH1 1
#define ADCH2 2
#define ADCH3 3
#define ADCH4 4
#define ADCH5 5
#define ADCH6 6
#define ADCH7 7

extern volatile uint8_t ADCSRA;
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE 3
#define ADIF 4
#define ADATE 5
#define ADSC 6
#define ADEN 7

extern volatile uint8_t ADCSRB;
#define ADTS0 0
#define ADTS1 1
#define ADTS2 2
#define ACME 6

extern volatile uint8_t ADMUX;
#define MUX0 0
#define MUX1 1
#define MUX2 2
#define MUX3 3
#define ADLAR 5
#define REFS0 6
#define REFS1 7

extern volatile uint8_t DIDR0;
#define ADC0D 0
#define ADC1D 1
#define ADC2D 2
#define ADC3D 3
#define ADC4D 4
#define ADC5D 5

extern volatile uint8_t DIDR1;
#define AIN0D 0
#define AIN1D 1

extern volatile uint8_t TCCR1A;
#define WGM10 0
#define WGM11 1
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

extern volatile uint8_t TCCR1B;
#define CS10 0
#define CS11 1
#define CS12 2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

extern volatile uint8_t TCCR1C;
#define FOC1B 6
#define FOC1A 7

extern volatile uint16_t TCNT1;

extern volatile uint8_t TCNT1L;
#define TCNT1L0 0
#define TCNT1L1 1
#define TCNT1L2 2
#define TCNT1L3 3
#define TCNT1L4 4
#define TCNT1L5 5
#define TCNT1L6 6
#define TCNT1L7 7

extern volatile uint8_t TCNT1H;
#define TCNT1H0 0
#define TCNT1H1 1
#define TCNT1H2 2
#define TCNT1H3 3
#define TCNT1H4 4
#define TCNT1H5 5
#define TCNT1H6 6
#define TCNT1H7 7

extern volatile uint16_t ICR1;

extern volatile uint8_t ICR1L;
#define ICR1L0 0
#define ICR1L1 1
#define ICR1L2 2
#define ICR1L3 3
#define ICR1L4 4
#define ICR1L5 5
#define ICR1L6 6
#define ICR1L7 7

extern volatile uint8_t ICR1H;
#define ICR1H0 0
#define ICR1H1 1
#define ICR1H2 2
#define ICR1H3 3
#define ICR1H4 4
#define ICR1H5 5
#define ICR1H6 6
#define ICR1H7 7

extern volatile uint16_t OCR1A;

extern volatile uint8_t OCR1AL;
#define OCR1AL0 0
#define OCR1AL1 1
#define OCR1AL2 2
#define OCR1AL3 3
#define OCR1AL4 4
#define OCR1AL5 5
#define OCR1AL6 6
#define OCR1AL7 7

extern volatile uint8_t OCR1AH;
#define OCR1AH0 0
#define OCR1AH1 1
#define OCR1AH2 2
#define OCR1AH3 3
#define OCR1AH4 4
#define OCR1AH5 5
#define OCR1AH6 6
#define OCR1AH7 7

extern volatile uint16_t OCR1B;

extern volatile uint8_t OCR1BL;
#define OCR1BL0 0
#define OCR1BL1 1
#define OCR1BL2 2
#define OCR1BL3 3
#define OCR1BL4 4
#define OCR1BL5 5
#define OCR1BL6 6
#define OCR1BL7 7

extern volatile uint8_t OCR1BH;
#define OCR1BH0 0
#define OCR1BH1 1
#define OCR1BH2 2
#define OCR1BH3 3
#define OCR1BH4 4
#define OCR1BH5 5
#define OCR1BH6 6
#define OCR1BH7 7

extern volatile uint8_t TCCR2A;
#define WGM20 0
#define WGM21 1
#define COM2B0 4
#define COM2B1 5
#define COM2A0 6
#define COM2A1 7

extern volatile uint8_t TCCR2B;
#define CS20 0
#define CS21 1
#define CS22 2
#define WGM22 3
#define FOC2B 6
#define FOC2A 7

extern volatile uint8_t TCNT2;
#define TCNT2_0 0
#define TCNT2_1 1
#define TCNT2_2 2
#define TCNT2_3 3
#define TCNT2_4 4
#define TCNT2_5 5
#define TCNT2_6 6
#define TCNT2_7 7

extern volatile uint8_t OCR2A;
#define OCR2_0 0
#define OCR2_1 1
#define OCR2_2 2
#define OCR2_3 3
#define OCR2_4 4
#define OCR2_5 5
#define OCR2_6 6
#define OCR2_7 7

extern volatile uint8_t OCR2B;
#define OCR2_0 0
#define OCR2_1 1
#define OCR2_2 2
#define OCR2_3 3
#define OCR2_4 4
#define OCR2_5 5
#define OCR2_6 6
#define OCR2_7 7

extern volatile uint8_t ASSR;
#define TCR2BUB 0
#define TCR2AUB 1
#define OCR2BUB 2
#define OCR2AUB 3
#define TCN2UB 4
#define AS2 5
#define EXCLK 6

extern volatile uint8_t TWBR;
#define TWBR0 0
#define TWBR1 1
#define TWBR2 2
#define TWBR3 3
#define TWBR4 4
#define TWBR5 5
#define TWBR6 6
#define TWBR7 7

extern volatile uint8_t TWSR;
#define TWPS0 0
#define TWPS1 1
#define TWS3 3
#define TWS4 4
#define TWS5 5
#define TWS6 6
#define TWS7 7

extern volatile uint8_t TWAR;
#define TWGCE 0
#define TWA0 1
#define TWA1 2
#define TWA2 3
#define TWA3 4
#define TWA4 5
#define TWA5 6
#define TWA6 7

extern volatile uint8_t TWDR;
#define TWD0 0
#define TWD1 1
#define TWD2 2
#define TWD3 3
#define TWD4 4
#define TWD5 5
#define TWD6 6
#define TWD7 7

extern volatile uint8_t TWCR;
#define TWIE 0
#define TWEN 2
#define TWWC 3
#define TWSTO 4
#define TWSTA 5
#define TWEA 6
#define TWINT 7

extern volatile uint8_t TWAMR;
#define TWAM0 0
#define TWAM1 1
#define TWAM2 2
#define TWAM3 3
#define TWAM4 4
#define TWAM5 5
#define TWAM6 6

extern volatile uint8_t UCSR0A;
#define MPCM0 0
#define U2X0 1
#define UPE0 2
#define DOR0 3
#define FE0 4
#define UDRE0 5
#define TXC0 6
#define RXC0 7

extern volatile uint8_t UCSR0B;
#define TXB80 0
#define RXB80 1
#define UCSZ02 2
#define TXEN0 3
#define RXEN0 4
#define UDRIE0 5
#define TXCIE0 6
#define RXCIE0 7

extern volatile uint8_t UCSR0C;
#define UCPOL0 0
#define UCSZ00 1
#define UCPHA0 1
#define UCSZ01 2
#define UDORD0 2
#define USBS0 3
#define UPM00 4
#define UPM01 5
#define UMSEL00 6
#define UMSEL01 7

extern volatile uint16_t UBRR0;

extern volatile uint8_t UBRR0L;
#define UBRR0_0 0
#define UBRR0_1 1
#define UBRR0_2 2
#define UBRR0_3 3
#define UBRR0_4 4
#define UBRR0_5 5
#define UBRR0_6 6
#define UBRR0_7 7

extern volatile uint8_t UBRR0H;
#define UBRR0_8 0
#define UBRR0_9 1
#define UBRR0_10 2
#define UBRR0_11 3

extern volatile uint8_t UDR0;
#define UDR0_0 0
#define UDR0_1 1
#define UDR0_2 2
#define UDR0_3 3
#define UDR0_4 4
#define UDR0_5 5
#define UDR0_6 6
#define UDR0_7 7

extern uint8_t interruptsEnabled;
extern uint8_t numInterruptsTriggered;

void sei();
void cli();

#endif  // MOCK_AVR_IO_H
