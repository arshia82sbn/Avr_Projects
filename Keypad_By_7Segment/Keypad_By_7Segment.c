#include <mega16.h>
#include <alcd.h>
#include <delay.h>

// Define your global variables and functions here

// Function to read the keypad
int key_pad(void) {
   if (PINA.0 == 0) return 1;
    if (PINA.1 == 0) return 2;
    if (PINA.2 == 0) return 3;
    PORTA = 0b11110111; // Row 1 (PA3) low, others high
    delay_ms(10); // Small delay for debounce
    if (PINA.0 == 0) return 4;
    if (PINA.1 == 0) return 5;
    if (PINA.2 == 0) return 6;
    PORTA = 0b11111011; // Row 2 (PA4) low, others high
    delay_ms(10); // Small delay for debounce
    if (PINA.0 == 0) return 7;
    if (PINA.1 == 0) return 8;
    if (PINA.2 == 0) return 9;
    PORTA = 0b11111101; // Row 3 (PA5) low, others high
    delay_ms(10); // Small delay for debounce
    if (PINA.1 == 0) return 0;
    if (PINA.2 == 0) return 10; // For clearing display or another function
}

// Function to display the key pressed on LCD
void lcd_display(int key) {
    if (key == 1) lcd_putsf("1");
    if (key == 2) lcd_putsf("2");
    if (key == 3) lcd_putsf("3");
    if (key == 4) lcd_putsf("4");
    if (key == 5) lcd_putsf("5");
    if (key == 6) lcd_putsf("6");
    if (key == 7) lcd_putsf("7");
    if (key == 8) lcd_putsf("8");
    if (key == 9) lcd_putsf("9");
    if (key == 0) lcd_putsf("0");
    if (key == 10) lcd_clear(); // Clear display if special key pressed
}

void main(void) {
    int key;

    // Port A initialization
    DDRA = 0b01111000; // Rows (PA3-PA6) as output, Columns (PA0-PA2) as input
    PORTA = 0b11111111; // Enable pull-up resistors for columns

    // Port C initialization for LCD
    DDRC = 0xFF; // Set PORTC as output for LCD
    PORTC = 0x00; // Initialize PORTC

    // Initialize the LCD
    lcd_init(16);

    while (1) {
        key = key_pad(); // Read the keypad
        if (key != 12) { // If a valid key is pressed
            lcd_display(key); // Display the key on LCD
            PORTD & = ~(1<<EN);
        }
        delay_ms(350); // Delay to debounce keypad inputs
    }
}
