#include "alarm.h"
#include "ui.h"
#include "sensor.h"
#include "logging.h"
#include "ntp.h"

// Initialize the sensors, alarm, and UI
void setup() {
  Serial.begin(115200);
  
  setupAlarm();
  setupUI();
  setupSensors();
  setupNTP();
}

void loop() {
  // Monitor sensors
  monitorSensors();
  
  // Check if alarm needs activation
  checkAlarm();
  
  // Handle UI inputs (keypad)
  handleUI();
  
  // Log events
  logEvent();
  
  delay(100);  // Avoid unnecessary processing load
}
