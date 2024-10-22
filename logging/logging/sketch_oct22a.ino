logging.h 

// logging.h 

#ifndef LOGGING_H 

#define LOGGING_H 

  

void logEvent(); 

void setupLogging(); 

  

#endif 

  

// logging.cpp 

#include "logging.h" 

#include <NTPClient.h> 

#include <WiFiUdp.h> 

  

WiFiUDP ntpUDP; 

NTPClient timeClient(ntpUDP); 

  

void setupLogging() { 

  timeClient.begin(); 

  timeClient.setTimeOffset(10800);  // Adjust time offset for your timezone 

} 

  

void logEvent() { 

  timeClient.update(); 

  Serial.print("Event at: "); 

  Serial.println(timeClient.getFormattedTime()); 

} 
