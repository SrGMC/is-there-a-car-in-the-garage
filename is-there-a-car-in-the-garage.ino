#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <HCSR04.h>              //https://github.com/Martinsos/arduino-lib-hc-sr04

int TRIG = D1;
int ECHO = D2;
int LENGTH = 280;

// Change this to whitelist IP
int source[4] = {192,168,1,2};

// Change this
const char* username = "home";
const char* password = "93bf2mpcddtu9kc3";

// Setup the Ultrasonic sensor and WebServer
UltraSonicDistanceSensor distanceSensor(TRIG, ECHO);
ESP8266WebServer server(80);

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
    wifiManager.setSTAStaticIPConfig(IPAddress(192,168,1,14), IPAddress(192,168,1,1), IPAddress(255,255,255,0));

    // WiFi Manager will try to connect to the latest WiFi connection. Otherwise, an AP will be created
    // to set up the wireless conncetion
    wifiManager.autoConnect("garage-sensor");

    Serial.printf("*WM: Succesfully Connected\n");

    /*
     * Server setup
     */
    server.on("/", []() {
        IPAddress remote = server.client().remoteIP();
        Serial.printf("Request from %i.%i.%i.%i\n", remote[0], remote[1], remote[2], remote[3]);
        if(remote[0] == source[0] && remote[1] == source[1] && 
           remote[2] == source[2] && remote[3] == source[3]) {
            return server.send(200, "text/plain", checkSensor());
        } else {
            if (!server.authenticate(username, password)) {
                return server.requestAuthentication();
            } else {
                return server.send(200, "text/plain", checkSensor()); 
            }
        }
    });
    server.onNotFound([]() {
        server.send(404, "text/plain", "Error");
    });
    server.begin();
    checkSensor();
}

void loop() {
    server.handleClient();
}

String checkSensor(){
    double distance = distanceSensor.measureDistanceCm();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("mm.");
    if(distance <= (LENGTH/2)) {
        Serial.println("true");
        return "true";
    } else {
        Serial.println("true");
        return "false";
    }
}
