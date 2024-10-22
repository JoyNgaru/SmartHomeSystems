// Define the pin where the analog output of MQ2 is connected
int gasSensorPin = 39;

void setup() {
  Serial.begin(9600);  // Start the serial communication at 9600 baud rate
  pinMode(gasSensorPin, INPUT);  // Set the gas sensor pin as input
}

void loop() {
  int gasSensorValue = analogRead(gasSensorPin);  // Read the analog value from the gas sensor
  Serial.print("MQ2 Gas Sensor Value: ");
  Serial.println(gasSensorValue);  // Print the gas sensor value

  // Simple delay for readability in the serial monitor
  delay(1000);  // Wait for 1 second before reading the value again
}
