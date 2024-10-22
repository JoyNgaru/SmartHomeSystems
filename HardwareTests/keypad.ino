#include <Keypad.h>

// Define the number of rows and columns for the 4x4 keypad
const byte ROWS = 4; 
const byte COLS = 4; 

// Define the symbols on the buttons of the keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad rows and columns to these Arduino pins
byte rowPins[ROWS] = {14, 12, 11, 9}; // Rows connected to Arduino pins
byte colPins[COLS] = {45, 41, 34, 21}; // Columns connected to Arduino pins

// Initialize the Keypad library with the row and column pin configuration
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Begin serial communication
}

void loop() {
  char key = keypad.getKey();  // Get the key pressed on the keypad

  if (key) {  // If a key is pressed, print it to the serial monitor
    Serial.println(key);
  }
}

 
