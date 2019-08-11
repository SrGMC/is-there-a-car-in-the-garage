#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <HCSR04.h>              //https://github.com/Martinsos/arduino-lib-hc-sr04

int TRIG = D1;
int ECHO = D2;
int LENGTH = 280;

// Change this
const char* username = "arduino";
const char* password = "arduino";

/*
 * Sensor polling settings
 */
// Current time
unsigned long sensorCurrentTime = millis();
// Timeout (30min)
const long sensorTimeout = 30000;

// Setup the Ultrasonic sensor and WebServer
UltraSonicDistanceSensor distanceSensor(TRIG, ECHO);
ESP8266WebServer server(80);

// Stores if there's a car or not
String isThereCar = "true";

void setup() {
    // Serial connection used for debugging
    Serial.begin(115200);

    /*
     * WiFi management
     */
    WiFiManager wifiManager;
    // Uncomment to reset config
    //wifiManager.resetSettings();
    
    // Uncomment to set a static IP config. Can also be set in the captive portal under the
    // Configure WiFI (No Scan) option
    //wifiManager.setSTAStaticIPConfig(IPAddress(192,168,1,14), IPAddress(192,168,1,1), IPAddress(255,255,255,0));

    // WiFi Manager will try to connect to the latest WiFi connection. Otherwise, an AP will be created
    // to set up the wireless conncetion
    wifiManager.autoConnect("garage-sensor");

    Serial.printf("*WM: Succesfully Connected\n");

    /*
     * Server setup
     */
    server.on("/", []() {
        if (!server.authenticate(username, password)) {
            return server.requestAuthentication();
        }
        server.send(200, "text/plain", isThereCar);
    });
    server.onNotFound([]() {
        server.send(404, "text/plain", "Error");
    });
    server.begin();
    checkSensor();
}

void loop() {
    server.handleClient();
    checkSensor();
}

void checkSensor(){
    if((millis() - sensorCurrentTime) >= sensorTimeout) {
        double distance = distanceSensor.measureDistanceCm();
        if(distance <= (LENGTH/2) && !isThereCar) {
            isThereCar = "true";
        } else if (distance > (LENGTH/2) && isThereCar) {
            isThereCar = "false";
        }
        sensorCurrentTime = millis();
        Serial.println(isThereCar);
    }
}
