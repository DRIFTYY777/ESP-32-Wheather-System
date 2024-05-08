# ESP32 DHT11, Wind Speed, and Firebase Data Logger

This project utilizes an ESP32 microcontroller to collect data from a DHT11 sensor (temperature and humidity), a wind speed sensor, and upload it to a Firebase Realtime Database over Wi-Fi. Additionally, the project saves data locally on an SD card for later analysis, including timestamps synchronized with an NTP time server. The collected data can be visualized using an Android application (link provided below).

## Features

Measures temperature, humidity, and wind speed using DHT11 and a wind speed sensor
Uploads data to a Firebase Realtime Database for real-time monitoring
Saves data locally on an SD card with timestamps for offline analysis
Synchronizes timestamps with an NTP time server for accurate data recording
Integrates with an Android application for data visualization (link provided below)
## Getting Started

1. Prerequisites

ESP32 development board (any model compatible with Arduino IDE)
DHT11 sensor
Wind speed sensor (model and connection details required)
MicroSD card (recommended size: 2GB or higher)
Breadboard and jumper wires
Wi-Fi network credentials (SSID and password)
A Firebase project with a Realtime Database (https://firebase.google.com/)
An NTP server address for time synchronization (e.g., pool.ntp.org)
Arduino IDE (https://www.arduino.cc/) installed on your computer
2. Hardware Setup

Connect the DHT11 sensor, wind speed sensor, and SD card to your ESP32 board following the specific wiring diagrams for each component. Refer to the datasheets or online tutorials for detailed instructions.
Connect the ESP32 board to your computer using a USB cable.
3. Software Setup

3.1. Install Libraries

Open the Arduino IDE and go to Sketch > Include Library > Manage Libraries.
Search and install the following libraries (if not already installed):
WiFi library
DHT library (version compatible with your DHT11 sensor)
SD library
Firebase ESP32 library
Time library (for NTP synchronization)
Replace placeholder values in the code with your Wi-Fi credentials, Firebase project details (database URL and credentials), NTP server address, and any sensor-specific settings.
3.2. Upload the Code

In the Arduino IDE, open the provided code (ESP32_DHT11_Wind_Firebase_SD.ino).
Select your ESP32 board and serial port from the Tools menu.
Click the Upload button to upload the code to your ESP32 board.
## Android Application

The provided link (Link) leads to the Android application that can be used to visualize the collected data from your Firebase Realtime Database. Download and install the application on your Android device to see the sensor readings in real time.

## Data Analysis

The data saved on the SD card can be accessed and analyzed using various tools such as Python libraries (e.g., pandas, matplotlib) or spreadsheet software (e.g., Microsoft Excel, Google Sheets). The timestamps will facilitate data exploration and visualization based on time periods.

## Additional Notes

Consider error handling and debugging mechanisms in your code for robustness.
Explore advanced features in the Firebase Realtime Database, such as data security rules.
For more complex data analysis, you might investigate integrating with cloud platforms like Google Cloud Platform or Amazon Web Services.
## Disclaimer

The provided Android application link (Link) has not been reviewed for security or functionality. Use it at your own discretion.

I hope this comprehensive README file empowers you to successfully set up and utilize your ESP32 data logger project!
