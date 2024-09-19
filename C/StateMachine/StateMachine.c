#include <Keypad.h>

// Define the row and column pins
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define the row and column pin connections
byte rowPins[ROWS] = {5, 8, 7, 6}; // Connect to the row pins of the keypad
byte colPins[COLS] = {9, 10, 0, 2};  // Connect to the column pins of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char key = keypad.getKey(); // Get the key pressed
