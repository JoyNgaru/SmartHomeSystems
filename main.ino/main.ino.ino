#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>
#include <Keypad.h>

// Pin definitions for gas sensor
int gasSensorPin = 39;

// Pin definitions for DHT22 sensor and buzzer
#define DHTPIN 4          // Pin connected to the DHT sensor
#define DHTTYPE DHT22     // DHT 22 (AM2302) sensor type
#define buzzerPin 19      // Pin connected to the buzzer

// Wi-Fi credentials
const char* ssid     = "wifi_username";   // Replace with your Wi-Fi SSID
const char* password = "password";         // Replace with your Wi-Fi password

// NTP client settings
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 10800);  // UTC +3 for Nairobi

// Initialize the DHT22 sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables to store temperature, humidity, and gas detection
float temperature = 0.0;
float humidity = 0.0;
bool gasDetected = false;  // Flag to indicate gas detection
bool alarmActive = false;  // Flag to control buzzer activation

// Keypad setup
#define ROW_NUM 4  // Four rows
#define COLUMN_NUM 4  // Four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};

byte pin_rows[ROW_NUM] = {1, 10, 9, 11}; // GPIO1, GPIO10, GPIO9, GPIO11 connect to the row pins
byte pin_column[COLUMN_NUM] = {12, 14, 21, 34};  // GPIO12, GPIO14, GPIO21 connect to the column pins
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

String enteredPassword = "";  // Store keypad input
String correctPassword = "4";  // Set the correct password

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Gas sensor setup
  pinMode(gasSensorPin, INPUT);

  // Initialize DHT22 sensor
  dht.begin();

  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);  // Ensure the buzzer is off at the start

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize NTP client for time
  timeClient.begin();
  timeClient.setTimeOffset(10800);  // UTC +3 for Nairobi
}

void loop() {
  // Update time from NTP server
  timeClient.update();

  // Get gas sensor reading
  int gasSensorValue = analogRead(gasSensorPin);
  
  // Detect gas: set gasDetected flag if gas sensor value is high
  if (gasSensorValue > 500) {  // You can adjust the threshold based on your environment
    gasDetected = true;
    alarmActive = true;
    Serial.println("Gas detected! Alarm activated.");
  }

  // Get temperature and humidity readings from the DHT22
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Check if any readings failed
  if (!isnan(temperature) && !isnan(humidity)) {
    // Get the current timestamp from NTP server
    String formattedTime = timeClient.getFormattedTime();

    // Print temperature, humidity, and timestamp to Serial Monitor
    Serial.print("Timestamp: ");
    Serial.println(formattedTime);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Activate the buzzer if gas is detected or temperature is too high
    if (gasDetected || temperature > 26.0) {
      tone(buzzerPin, 1000);  // Play a 1000Hz tone if gas is detected or temperature exceeds 26°C
      Serial.println("Buzzer ON: Alarm activated");
    }
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  // Keypad input handling to deactivate the alarm
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {  // Check for enter key ('#')
      if (enteredPassword == correctPassword) {
        Serial.println("Correct password! Alarm deactivated.");
        gasDetected = false;
        alarmActive = false;
        noTone(buzzerPin);  // Stop the buzzer
      } else {
        Serial.println("Incorrect password! Try again.");
      }
      enteredPassword = "";  // Reset password input
    } else {
      enteredPassword += key;  // Add entered key to the password
      Serial.print("Entered: ");
      Serial.println(enteredPassword);
    }
  }

  // Simple delay for readability in the serial monitor
  delay(1000);  // Shorter delay for faster keypad responsiveness
}
