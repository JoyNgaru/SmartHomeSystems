#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>

// Pin definitions
#define DHTPIN 4          // Pin connected to the DHT sensor
#define DHTTYPE DHT22     // DHT 22 (AM2302) sensor type

// Wi-Fi credentials
const char* ssid     = "Wifi_name";   // Replace with your Wi-Fi SSID
const char* password = "wifi_password";   // Replace with your Wi-Fi password

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
  
  // Wait before reading again
  delay(5000);  // Update every 5 seconds
}
