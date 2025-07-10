/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/1/2024
Author  : 
Company : 
Comments: 


Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/
#include <mega16a.h>
#include <stdio.h>
#include <delay.h>
#include <stdint.h>
// Alphanumeric LCD functions
#include <alcd.h>
char str[30];
eeprom uint32_t sec = 0;
eeprom uint32_t min = 0;
eeprom uint32_t h = 0;
void init_ports(void) {
    // Input/Output Ports initialization
    DDRA = (1 << DDA7) | (1 << DDA6) | (1 << DDA5) | (1 << DDA4) | (0 << DDA3) | (1 << DDA2) | (1 << DDA1) | (1 << DDA0);
    PORTA = 0x00;

    DDRB = 0x00;
    PORTB = 0x00;

    DDRC = (0 << DDC7) | (1 << DDC6) | (1 << DDC5) | (1 << DDC4) | (1 << DDC3) | (0 << DDC2) | (0 << DDC1) | (0 << DDC0);
    PORTC = 0x00;

    DDRD = 0x00;
    PORTD = 0x00;
}


void handle_input(void) {
    if (PINB.0 == 1) {
        sec+= 1;
        PORTD.5 = 1; // Indicator for seconds
    } else if (PINB.1 == 1) {
        min += 1;
        PORTD.3 = 1; // Indicator for minutes
    } else if (PINB.2 == 1) {
        h += 1;
        PORTD.4 = 1; // Indicator for hours
    } else if (PINB.3 == 1) {
        // Reset
        min = 0;
        sec = 0;
        h = 0;
        
        PORTD.6 = 1; // Indicator for reset
    } else {
        PORTD.6 = 0;
        PORTD.5 = 0;
        PORTD.4 = 0;
        PORTD.3 = 0;
    }
}
void update_display(void) {
    
    if(sec == 60)
    {
     sec = 0;
     min++;
    }
    else if(min == 60)
    {
     min = 0;
     h++;
    }
    else if(h == 24)
    {
     h = 0;
    }
     

    sprintf(str, "Time:%02d:%02d:%02d", h, min, sec);
    lcd_gotoxy(0, 0);
    lcd_puts(str);
}

// Declare your global variables here

void main(void) {
    // Alphanumeric LCD initialization
    lcd_init(16);
    
    init_ports(); // Initialize ports

    while (1) {
        update_display(); // Update LCD display
        handle_input(); // Handle button inputs
        delay_ms(1000);
        sec++;
        lcd_clear();
    }
}

