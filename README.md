
---

# **Smart Home Systems Project**

## **Project Overview**

The **Smart Home Systems** project is designed to detect fire using an over-temperature detector and a gas detector. When either or both conditions are met, the system activates an alarm, which can be deactivated by entering a special code on the keypad. This project utilizes an ESP32 microcontroller and incorporates various modular functionalities for easier code management and expansion.

## **Goals**

1. Detect fire conditions using a gas detector (MQ-2) and temperature sensor (DHT22).
2. Trigger an audible and visual alarm (buzzer and LED) when a fire is detected.
3. Deactivate the alarm using a code entered on a keypad.
4. Log system events with timestamps using the NTP Client.
5. Modularize the system for easier maintenance and future improvements.
6. Collaborate effectively using GitHub with well-defined branches and roles.

## **Components**

- **ESP32**: The brain of the system.
- **Keypad**: For user input to deactivate the alarm.
- **Gas Sensor (MQ-2)**: Detects gas leaks.
- **Temperature Sensor (DHT22)**: Monitors temperature levels to detect over-temperature.
- **Buzzer**: Sounds the alarm when fire is detected.
- **LED**: Visual indicator for the alarm status.
- **NTP Client (ESP32)**: Provides the current time and date for event logging.

## **Functionality**

The system is divided into several functionalities, each handled by a modular piece of code:
1. **Alarm Management**: Handles the buzzer and LED for signaling fire detection.
2. **User Interface**: Manages keypad input and LED indicators.
3. **Sensor Management**: Reads data from the gas and temperature sensors.
4. **Event Logging**: Logs detected events and timestamps them using NTP.
5. **Time Management**: Fetches the current date and time using the NTP client.

## **Project Iterations**

1. **Alarm Activation**:
   - If gas is detected, the alarm is triggered, and the LED blinks every second.
   - If the temperature exceeds a threshold, the LED blinks every 500 ms.
   - If both gas and over-temperature are detected, the LED blinks rapidly (100 ms on/off).
   
2. **Keypad Input**:
   - The alarm can be deactivated by entering a code on the keypad. Number keys set the code, and any other key acts as the Enter key.

3. **Event Logging**:
   - The system logs the alarm activation and deactivation events along with timestamps provided by the NTP Client.

4. **Modular Code**:
   - The system is modularized into separate files, each handling specific functionality, making it easier to maintain and expand.

## **System Setup**

### **Hardware Connections**

1. **ESP32**: Connects to the sensors, keypad, buzzer, and LED.
2. **Gas Sensor (MQ-2)**: Connected to an analog pin.
3. **Temperature Sensor (DHT22)**: Connected to a digital pin.
4. **Keypad**: Connected to digital pins for user input.
5. **Buzzer**: Connected to a digital pin for the alarm sound.
6. **LED**: Connected to a digital pin for visual indication.

### **Software Setup**

1. Install necessary libraries:
   - **DHT Sensor Library** for temperature sensing.
   - **Keypad Library** for handling the keypad.
   - **NTP Client Library** for time synchronization.
   - **WiFi.h** for ESP32 to connect to Wi-Fi and fetch NTP data.

2. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/SmartHomeSystems.git
   ```

3. Open the project in the Arduino IDE and upload the code to the ESP32.

### **NTP Setup**
Make sure the ESP32 is connected to a Wi-Fi network to fetch date and time from the NTP server.

## **GitHub Collaboration**

### **Repository Setup**

1. **Create a new repository**: One team member should create the repository on GitHub named `SmartHomeSystems`.
2. **Add a README.md** file with the project details (like this file).
3. **Set up branch structure**:
   - Each member should create a branch for the functionality they are working on.
   - Naming convention: `<your-name>-<feature>` (e.g., `john-fire-alarm`).

### **Branching Strategy**

1. **Main Branch**: Integrates all the modules and manages system events.
2. **Feature Branches**: Each feature or subsystem is developed on its own branch. Examples include:
   - `fire-alarm`: Manages the fire alarm system.
   - `user-interface`: Handles the user interface (LEDs and keypad).
   - `sensor-management`: Reads from gas and temperature sensors.
   - `event-logging`: Manages event logs and timestamps.
   - `time-management`: Fetches date and time using NTP.
   
4. **Pull Requests**: Each branch should be merged into the main branch via pull requests, and all team members should review the code before merging.

## **Contributing**

1. **Fork the repository** and create your feature branch.
   ```bash
   git checkout -b <your-name>-<feature>
   ```

2. **Commit your changes**:
   ```bash
   git commit -m "Added <feature> functionality"
   ```

3. **Push your branch** to the repository:
   ```bash
   git push origin <your-name>-<feature>
   ```

4. Open a pull request and tag team members for review.

## **License**

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

This **README.md** file provides a clear and organized view of the project and how to set it up, making it easy for team members and future collaborators to understand its goals and structure.
