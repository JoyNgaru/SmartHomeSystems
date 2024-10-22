#include <Keypad.h>

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  4 // four columns
char keys[ROW_NUM][COLUMN_NUM] = {
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};
byte pin_rows[ROW_NUM] = {1, 10, 9, 11}; // GPIO1, GPIO10, GPIO9, GPIO11 connect to the row pins
byte pin_column[COLUMN_NUM] = {12, 14, 21, 34};  // GPIO12, GPIO14, GPIO21 connect to the column pins
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  Serial.begin(9600); // Initialize the serial communication
}

void loop() {
  char key = keypad.getKey(); // Get the pressed key

  if (key) { // If a key is pressed
    Serial.print("Pressed: "); // Print the key press
    Serial.println(key);
  }
}
