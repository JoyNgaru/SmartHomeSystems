// code to test temperature, humidity, wifi, date and time and buzzer
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>

// Pin definitions
#define DHTPIN 4          // Pin connected to the DHT sensor
#define DHTTYPE DHT22     // DHT 22 (AM2302) sensor type
#define buzzerPin 12      // Pin connected to the buzzer

// Wi-Fi credentials
const char* ssid     = "ALX The Piano 01";   // Replace with your Wi-Fi SSID
const char* password = "Thepiano01";         // Replace with your Wi-Fi password

// NTP client settings
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 10800);  // UTC +3 for Nairobi

// Initialize the DHT22 sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables to store temperature and humidity
float temperature = 0.0;
float humidity = 0.0;

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
  
  // Initialize DHT22 sensor
  dht.begin();

  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);

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
  
  // Get temperature and humidity readings from the DHT22
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  // Check if any readings failed and exit loop if so
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

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

  // Buzzer logic: trigger buzzer if temperature exceeds 30°C
  if (temperature > 26.0) {
    tone(buzzerPin, 1000);  // Play a 1000Hz tone if temperature exceeds 30°C
    Serial.println("Buzzer ON: Temperature exceeded 30°C");
  } else {
    noTone(buzzerPin);  // Stop the buzzer if temperature is below 30°C
    Serial.println("Buzzer OFF: Temperature is safe");
  }
  
  // Wait before reading again
  delay(5000);  // Update every 5 seconds
}
