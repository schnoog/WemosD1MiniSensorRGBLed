// Copyright Nat Weerawan 2015-2016
// MIT License

#include <ESP8266WiFi.h>
#include <CMMC_OTA.h>

#ifndef WIFI_SSID
  #define WIFI_SSID       "Nat"
  #define WIFI_PASSPHRASE "1234567890"
#endif

CMMC_OTA ota;

void init_hardware()
{
  WiFi.disconnect(true);
  Serial.begin(115200);
  Serial.flush();
  Serial.println();
  Serial.println();
  Serial.println("being started...");
  delay(100);

  WiFi.begin(WIFI_SSID, WIFI_PASSPHRASE);
  while (WiFi.status() != WL_CONNECTED) {
   Serial.printf("connecting %s:%s \r\n", WIFI_SSID, WIFI_PASSPHRASE);
   delay(100);
 }

  Serial.print("READY!! IP address: ");

  Serial.println(WiFi.localIP());
}

void setup()
{
  init_hardware();

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

void loop()
{
  ota.loop();
}
