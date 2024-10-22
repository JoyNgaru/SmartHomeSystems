#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid     = "Nana";
const char* password = "qwertyuiop";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000); // Offset by 3600 seconds (1 hour for GMT+1)

// DHT sensor setup
#define DHTPIN 4         // Pin where the DHT sensor is connected
#define DHTTYPE DHT22    // DHT 22 (AM2302) sensor type, use DHT11 if you're using a DHT11 sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables to save date, time, temperature, and humidity
String timeStamp;
float temperature;
float humidity;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize NTPClient to get time
  timeClient.begin();

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Update time from NTP server
  timeClient.update();

  // Get formatted time (HH:MM:SS)
  timeStamp = timeClient.getFormattedTime();
  
  // Read temperature and humidity from DHT sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the time, temperature, and humidity
  Serial.print("Time: ");
  Serial.println(timeStamp);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(2000); // Wait for 2 seconds before updating the readings
}
