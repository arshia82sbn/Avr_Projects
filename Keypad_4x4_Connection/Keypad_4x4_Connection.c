/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 6/3/2024
Author  : 
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>

// Alphanumeric LCD functions
#include <alcd.h>

#include <delay.h>

#include <stdio.h>

#define R1 PORTC.0
#define R2 PORTC.1
#define R3 PORTC.2
#define R4 PORTC.3
#define C1 PINC.4
#define C2 PINC.5
#define C3 PINC.6
#define C4 PINC.7
// Declare your global variables here
unsigned char keypad(void);
unsigned char key;
char s[4];


void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

DDRC=(1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0) | (0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4);
PORTC=(1<<PORTC7) | (1<<PORTC6) | (1<<PORTC5) | (1<<PORTC4);


// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);


// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 16
lcd_init(16);

while (1)
      {
      key = keypad();
      if(key != 16)
      {sprintf(s, "%d" , key);
      lcd_puts(s); }
     else
       { 
    if (key == 10) lcd_putchar('/');
    if (key == 11) lcd_putchar('*');
    if (key == 12) lcd_putchar('-');
    if (key == 13) lcd_putchar('43');
    if (key == 14) lcd_putchar('=');
    if (key == 15) lcd_clear();
       }

      }
}
unsigned char keypad(void)
{
unsigned char K = 16;
PORTC = 0xFF;
R1 = 0;
delay_ms(3);
if(C1 == 0) { K = 7; while(C1 == 0);}
if(C2 == 0) { K = 8; while(C2 == 0);}
if(C3 == 0) { K = 9; while(C3 == 0);}
if(C4 == 0) { K = 10; while(C4 == 0);}
R1 = 1;

R2 = 0;
delay_ms(3); 
if(C1 == 0) { K = 4; while(C1 == 0);}
if(C2 == 0) { K = 5; while(C2 == 0);}
if(C3 == 0) { K = 6; while(C3 == 0);}
if(C4 == 0) { K = 11; while(C4 == 0);}
R2 = 1;

R3 = 0;
delay_ms(3);
if(C1 == 0) { K = 1; while(C1 == 0);}
if(C2 == 0) { K = 2; while(C2 == 0);}
if(C3 == 0) { K = 3; while(C3 == 0);}
if(C4 == 0) { K = 12; while(C4 == 0);}
R3 = 1;

R4 = 0;
delay_ms(3);
if(C1 == 0) { K = 15; while(C1 == 0);}
if(C2 == 0) { K = 0; while(C2 == 0);}
if(C3 == 0) { K = 14; while(C3 == 0);}
if(C4 == 0) { K = 13; while(C4 == 0);}
R4 = 1;
return K;
}