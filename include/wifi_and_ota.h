
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ArduinoOTA.h>

#include <TelnetSpy.h>
TelnetSpy SerialAndTelnet;
#define SERIAL  SerialAndTelnet


void waitForConnection() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    SERIAL.print(".");
  }
  SERIAL.println(" Connected!");
}

void waitForDisconnection() {
  while (WiFi.status() == WL_CONNECTED) {
    delay(500);
    SERIAL.print(".");
  }
  SERIAL.println(" Disconnected!");
}

void telnetConnected() {
  SERIAL.println("Telnet connection established.");
}

void telnetDisconnected() {
  SERIAL.println("Telnet connection closed.");
}


void telnet_setup(){
  
}

void telnet_loop(){
  SerialAndTelnet.handle(); 
}


void ota_setup(){
  ArduinoOTA.setPort(8266);
  ArduinoOTA.setPassword("1234567890");
      ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
          type = "sketch";
        } else { // U_SPIFFS
          type = "filesystem";
        }

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type);
      });
      ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
      });
      ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      });
      ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
          Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
          Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
          Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
          Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
          Serial.println("End Failed");
        }
      });
      ArduinoOTA.begin();
      Serial.println("Ready");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    
}



void wifi_setup(){
    SerialAndTelnet.setWelcomeMsg("Welcome to the TelnetSpy example\n\n");
    SerialAndTelnet.setCallbackOnConnect(telnetConnected);
    SerialAndTelnet.setCallbackOnDisconnect(telnetDisconnected);
    SERIAL.begin(115200);
    delay(100); // Wait for serial port  
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();
    wifiManager.autoConnect("AutoConnectAP");
    SERIAL.println (WiFi.localIP());
    SERIAL.println("connected...yeey :)");
    ota_setup();
    telnet_setup();
}

void wifi_loop(){
  ArduinoOTA.handle();
  telnet_loop();
}
