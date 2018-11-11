#ifndef CMMC_OTA_H
#define CMMC_OTA_H

#include <Arduino.h>
#include <functional>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

#ifdef CMMC_OTA_DEBUG
    #define CMMC_OTA_PRINTER Serial
    #define CMMC_OTA_PRINT(...) { CMMC_OTA_PRINTER.print(__VA_ARGS__); }
    #define CMMC_OTA_PRINTLN(...) { CMMC_OTA_PRINTER.println(__VA_ARGS__); }
#else
    #define CMMC_OTA_PRINT(...) { }
    #define CMMC_OTA_PRINTLN(...) { }
#endif

    typedef std::function<void(void)> THandlerFunction;
    typedef std::function<void(ota_error_t)> THandlerFunction_Error;
    typedef std::function<void(unsigned int, unsigned int)> THandlerFunction_Progress;

class CMMC_OTA {
  private:
    bool _initialised = false;

  THandlerFunction _user_on_start_callback;
  THandlerFunction _user_on_end_callback;
  THandlerFunction_Error _user_on_error_callback;
  THandlerFunction_Progress _user_on_progress_callback;

  public:


    CMMC_OTA* init() {
      static CMMC_OTA* s_instance = this;
      if (!_initialised)  {
        ArduinoOTA.onStart([]() {
          if (s_instance->_user_on_start_callback != NULL) {
            s_instance->_user_on_start_callback();
          }
        });

        ArduinoOTA.onEnd([]() {
          if (s_instance->_user_on_end_callback != NULL) {
            s_instance->_user_on_end_callback();
          }
        });

        ArduinoOTA.onProgress([&](unsigned int progress, unsigned int total) {
          if (s_instance->_user_on_progress_callback != NULL) {
            s_instance->_user_on_progress_callback(progress, total);
          }
        });

        ArduinoOTA.onError([](ota_error_t error) {
          if (s_instance->_user_on_error_callback != NULL) {
            s_instance->_user_on_error_callback(error);
          }
        });

        ArduinoOTA.begin();
        _initialised = true;
      }
      return s_instance;
    }

    void loop();
    void on_start(THandlerFunction fn);
    void on_end(THandlerFunction fn);
    void on_progress(THandlerFunction_Progress fn);
    void on_error(THandlerFunction_Error fn);
    bool initialized();

    CMMC_OTA();
    ~CMMC_OTA();

};

// CMMC_OTA* CMMC_OTA::s_instance = NULL;

#endif /* CMMC_OTA */
