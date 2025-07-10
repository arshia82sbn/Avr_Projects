#include <mega8.h>
#include <delay.h>
#include <stdint.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
char buffer[10];
char pass[5] = "1234";
uint8_t passLen = 10;


// get a character from numpad
char numpad() {
  static const char keypad[4][3] = {
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9',
    '*', '0', '#'
  }; 
  uint8_t x = 0;
  uint8_t y; 
  for (x; x < 4; x++) {
    PORTD = ~(1 << x);
    y = (~PIND & 0b01110000) >> 4; 
    if (y) return keypad[x][y >> 1];
  }
  return 0;
}

// Check if buffer is equal to the defined password
uint8_t checkPass(uint8_t len) {
  uint8_t i = 0;
  uint8_t r = 1;
  for (i; i < len; i++) {
    r &= (buffer[i] == pass[i]); 
  }
  return r;
}

// Display Prompt for Password
void promptPass() {
  lcd_clear();
  lcd_gotoxy(0,0);
  lcd_puts("Enter Password:");
  lcd_gotoxy(0,1);
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=Out 
DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=0 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=T Bit6=P Bit5=P Bit4=P Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTD=(0<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
lcd_init(16);
lcd_clear();

promptPass();
while (1) {
    // Get 4 inputs from numpad, save in buffer and echo on LCD 
    int i = 0;
    PORTC.0 = 0;
    PORTC.1 = 1;
    lcd_clear();
    while (i < 4) {
      char x = 0;
      x = numpad();
      if (x) {
        if (i == 0) promptPass(); 
        buffer[i] = x; 
        lcd_putchar(x);
        i++;
      }
      delay_ms(200);
    }
    
    // Check if the entered password is correct and display the resault
    lcd_clear();
    if (checkPass(passLen)) {
      lcd_puts("Password is \nCorrect!");
      PORTC.0 = 1;
      PORTC.1 = 0;
      delay_ms(5000);
      PORTC.0 = 0;
      PORTC.1 = 1;
    } else{
      lcd_puts("Password is \nWRONG!");
      PORTC.0 = 0;
      PORTC.1 = 1;
    }
  }
}
