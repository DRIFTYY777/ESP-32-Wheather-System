#pragma once

#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <Wire.h>
#include "DHT.h"
#include <WiFi.h>
#include <NTPClient.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>

// ___________details about firebase project and wifi name and pass___________
#define WIFI_SSID "test"                                  // username of wifi
#define WIFI_PASSWORD "voidmain"                          // password
#define API_KEY "AIzaSyBfppxm4qqUo60xeV2k7Ztr9z2qHc0lT6I" // key for connection
#define FIREBASE_PROJECT_ID "that-esp"                    // project name on server
#define USER_EMAIL "gbjhasd344@gmail.com"                 // lincked account with project for sec..
#define USER_PASSWORD "mmmmmmmmmm777"
// ___________details about firebase project and wifi name and pass___________

//___________________________Defining wind_direction pins total 8 pins___________________________

#define N 10   // North         Defining pins for win direction
#define N_E 9  // North_East    Defining pins for win direction
#define E 13   // East          Defining pins for win direction
#define E_S 12 // East_South    Defining pins for win direction
#define S 14   // South         Defining pins for win direction
#define S_W 27 // South_West    Defining pins for win direction
#define W 26   // West          Defining pins for win direction
#define W_N 25 // West_North    Defining pins for win direction

//___________________________Defining wind_direction pins total 8 pins___________________________

//___________________Variables to store sensor readings and defning pins (dht,wind,direction)___________________

#define windSen 0   // Define pin numbers diy wind speed sensor another pin goes to GND
#define DHT11PIN 22 // Define pin numbers dht sensor
#define SD_CS 5
#define uS_TO_S_FACTOR 1000000ULL // Conversion factor for micro seconds to seconds
int wind = 0;                     // global variable for wind speed
unsigned long firstMillis = 0;    // Timers for the wind speed calculation
unsigned long lastMillis = 0;     // global timer for firebase upload speed
unsigned long lastIntTime = 0;    // global timer for firebase upload speed
unsigned long dataMillis = 0;     // global timer for firebase upload speed
int counter = 0;                  // global variable for wind speed calculation
//___________________Variables to store sensor readings and defning pins (dht,wind,direction)___________________

//___________________________Defining Some_things about firebase and dht sensor___________________________
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
DHT dht(DHT11PIN, DHT11); // Define global Again dht sensor

//___________________________Defining Some_things about firebase and dht sensor___________________________

// void IRAM_ATTR isr(); // defining functions cause its C
// void calcWind();      // defining functions

String formattedDate; // parr____________________________________
String dayStamp;
String timeStamp; // parr____________________________________
String dataMessage;
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP); // parr____________________________________

void IRAM_ATTR isr() // Interrupt routine run with each reed switch interrupt
{
    unsigned long intTime = millis();
    if (intTime - lastIntTime > 150) // Debounce the reed switch input
    {
        if (counter == 0)
        {
            firstMillis = millis();
        }
        counter++; // Add each revolution
        lastMillis = millis();
        Serial.println(counter);
    }
    lastIntTime = intTime; // Capture the first and last revolution time
}

class main_parr // we created a class called main_parr
{

public:                 // defining all functions are public
    void under_setup1() // this function contains all things which run one time and  this function goes in void setup(){}
    {
        timeClient.begin(); // server on
        timeClient.setTimeOffset(19800);
        SD.begin(SD_CS); // checking sd card
        if (!SD.begin(SD_CS))
        {
            Serial.println("Card Mount Failed");
            return;
        }
        uint8_t cardType = SD.cardType(); // checking sd card type
        if (cardType == CARD_NONE)
        {
            Serial.println("No SD card attached");
            return;
        }
        Serial.println("Initializing SD card...");
        if (!SD.begin(SD_CS)) // checking sd card type dont match with defined parameters change paramaters in codes i think up there or in another file if not create one
        {
            Serial.println("ERROR - SD card initialization failed!");
            return; // init failed
        }
        File file = SD.open("/data.txt"); // simple C if you studdied opening file if not showing error file not exist
        if (!file)
        {
            Serial.println("File doens't exist");
            Serial.println("Creating file...");
        }
        else
        {
            Serial.println("File already exists");
        }
        file.close(); // also you can use fs.close i know it when i practise C language
    }
    void under_setup2()
    {
        pinMode(N, INPUT_PULLUP);   // defining electrical inputs. memic wind direction
        pinMode(N_E, INPUT_PULLUP); // defining electrical inputs. memic wind direction
        pinMode(E, INPUT_PULLUP);   // defining electrical inputs. memic wind direction
        pinMode(E_S, INPUT_PULLUP); // defining electrical inputs. memic wind direction
        pinMode(S, INPUT_PULLUP);   // defining electrical inputs. memic wind direction
        pinMode(S_W, INPUT_PULLUP); // defining electrical inputs. memic wind direction
        pinMode(W, INPUT_PULLUP);   // defining electrical inputs. memic wind direction
        pinMode(W_N, INPUT_PULLUP); // defining electrical inputs. memic wind direction
    }

    int wind_direction_fun() // function for wind direction using if elseif
    {
        int location;
        int Location_N = digitalRead(N);     // North         defining again for take readings or i dont know
        int Location_N_E = digitalRead(N_E); // North_East    defining again for take readings or i dont know
        int Location_E = digitalRead(E);     // East          defining again for take readings or i dont know
        int Location_E_S = digitalRead(E_S); // East_South    defining again for take readings or i dont know
        int Location_S = digitalRead(S);     // South         defining again for take readings or i dont know
        int Location_S_W = digitalRead(S_W); // South_West    defining again for take readings or i dont know
        int Location_W = digitalRead(W);     // West          defining again for take readings or i dont know
        int Location_W_N = digitalRead(W_N); // West_North    defining again for take readings or i dont know

        if (Location_N == LOW) // take... low as True. one vale at one time
        {
            location = 1; // 1 = north
        }
        else if (Location_N_E == LOW)
        {
            location = 2; // 2 = north east
        }
        else if (Location_E == LOW)
        {
            location = 3; // 3 = east
        }
        else if (Location_E_S == LOW)
        {
            location = 4; // 4 = east south
        }
        else if (Location_S == LOW)
        {
            location = 5; // 5 = south
        }
        else if (Location_S_W == LOW)
        {
            location = 6; // 6 = south west
        }
        else if (Location_W == LOW)
        {
            location = 7; // 7 = west
        }
        else if (Location_W_N == LOW)
        {
            location = 8; // 8 = west north    //__________  more accuracy need more pins or a special IC desighn for task like that____________
        }
        return location;
    }

    void calcWind() // Function to calculate the wind speed or wind map
    {
        int ave = 5000;
        if (counter != 0)
        {
            ave = (lastMillis - firstMillis) / counter;
        }
        if (ave < 200)
        {
            ave = 200;
            wind = map(ave, 200, 4000, 16, 3);
        }
        else if (ave > 4000)
        {
            wind = 0;
        }
        else
        {
            wind = map(ave, 200, 4000, 16, 3);
        }
    }

    void connection_windsepeed() // function who connect to wifi or start temp... sensor
    {
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // checking wifi pass,name or runing wifi
        while (WiFi.status() != WL_CONNECTED) // searching wifi or connecting
        {
            delay(200); // wating for connection
        }
        dht.begin(); // runing dht sensor
        WiFi.setAutoConnect(true);
        pinMode(windSen, INPUT_PULLUP);         // telling about winspeed pin
        attachInterrupt(windSen, isr, FALLING); // Define interrupt pin
    }

    void firebase() // this man for "checking all details are genune or not" .... simply for firebase account or project id
    {
        config.api_key = API_KEY;
        auth.user.email = USER_EMAIL;
        auth.user.password = USER_PASSWORD;
        config.token_status_callback = tokenStatusCallback;
        Firebase.begin(&config, &auth);
        Firebase.reconnectWiFi(true);
    }

    void windspeed() // calculating win speed for wind
    {
        delay(200); // Wait for wind speed readings to be taken
        calcWind();
        counter = 0;
    }

    void appendFile(fs::FS &fs, const char *path, const char *message) // ok not joke here this guy simply for print data in sd card or print in next line
    {
        Serial.printf("Appending to file: %s\n", path);
        File file = fs.open(path, FILE_APPEND);
        if (!file)
        {
            Serial.println("Failed to open file for appending");
            return;
        }
        if (file.print(message))
        {
            Serial.println("Message appended");
        }
        else
        {
            Serial.println("Append failed");
        }
        file.close();
    }

    void getTimeStamp() // this man taking time from server and store it in its own global variables
    {
        while (!timeClient.update()) // loop for updating time
        {
            timeClient.forceUpdate();
        }
        formattedDate = timeClient.getFormattedDate();
        Serial.println(formattedDate);
        int splitT = formattedDate.indexOf("T");
        dayStamp = formattedDate.substring(0, splitT);
        Serial.println(dayStamp);
        timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
        Serial.println(timeStamp);
    }

    void upload_data() // simply upload data in sd card + online server called firestore
    {
        int wind_direction;                                                                                                                                                                                                                        // variable for wind direction
        wind_direction = wind_direction_fun();                                                                                                                                                                                                     // calling wind direction fun.. casue we want wind dire....
        float humi = dht.readHumidity();                                                                                                                                                                                                           // variable for temperature value store
        float temp = dht.readTemperature();                                                                                                                                                                                                        // variable for humidity value store
        int wind_speed = wind;                                                                                                                                                                                                                     // variable for Wind_Speed value store
        dataMessage = "Day =  " + String(dayStamp) + "  Time =  " + String(timeStamp) + "    T = " + String(temp) + "     H = " + String(humi) + "     Wind_Speed = " + String(wind) + "     wind_direction = " + String(wind_direction) + "\r\n"; // this is printing data in sd card with date and time
        Serial.print("Save data: ");
        Serial.println(dataMessage);
        appendFile(SD, "/data.txt", dataMessage.c_str());

        if (Firebase.ready() && (millis() - dataMillis > 4000 || dataMillis == 0))
        {
            dataMillis = millis();
            FirebaseJson content;
            String documentPath = "kharwan/Roof_1";                                                                                                                  // defining document path only checking
            content.set("fields/temperature/doubleValue", String(temp).c_str());                                                                                     // uploading temp to temp variable
            content.set("fields/humidity/doubleValue", String(humi).c_str());                                                                                        // uploading humi to humi variable
            content.set("fields/wind_speed/doubleValue", String(wind_speed).c_str());                                                                                // uploading wind_speed to wind variable
            content.set("fields/wind_direction/doubleValue", String(wind_direction).c_str());                                                                        // uploading direction to wind_direction variable
            Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "temperature,humidity,wind_speed,wind_direction"); // checking document exist if exist upload or create one then upload
            Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw());                                                  // checking document exist or not if not then create one
        }
        if (Firebase.ready() == false)
            Serial.printf("Failed to upload");
    }

    void fucking_wifi() // this angry guy just sit for wifi
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            while (WiFi.status() != WL_CONNECTED)
            {
                delay(240000);
                ESP.restart();
                // WiFi.scanNetworks();
                // WiFi.mode(WIFI_STA);
                // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
            }
        }
    }
};
