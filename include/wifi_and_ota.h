
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <CMMC_OTA.h>
CMMC_OTA ota;




void wifi_setup(){
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();
    wifiManager.autoConnect("AutoConnectAP");
    Serial.println (WiFi.localIP());
    Serial.println("connected...yeey :)");
}

void otasetup(){
  ota.on_start([]() {

  });

  ota.on_end([]() {

  });

  ota.on_progress([](unsigned int progress, unsigned int total) {
      Serial.printf("_CALLBACK_ Progress: %u/%u\r\n", progress,  total);
  });

  ota.on_error([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
  });

  ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname("cmmc-ota-esp8266");

  // No authentication by default
  ArduinoOTA.setPassword((const char *)"1234567890");

  ota.init(); 
}