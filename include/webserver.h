#include <ArduinoJson.h>
#include "names.h"
#include "web_admin.h"
#include "web_interface.h"
#include "web_iro_js.h"



ESP8266WebServer server(80);

// this is a modified version of https://gist.github.com/hdznrrd/656996
RGB hsvToRgb(double h, double s, double v) {
  int i;
  double f, p, q, t;
  byte r, g, b;

  h = max(0.0, min(360.0, h));
  s = max(0.0, min(100.0, s));
  v = max(0.0, min(100.0, v));

  s /= 100;
  v /= 100;

  if (s == 0) {
    // Achromatic (grey)
    r = g = b = round(v * 255);
    return {0,0,0};
  }

  h /= 60; // sector 0 to 5
  i = floor(h);
  f = h - i; // factorial part of h
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - s * (1 - f));
  switch (i) {
    case 0:
      r = round(255 * v);
      g = round(255 * t);
      b = round(255 * p);
      break;
    case 1:
      r = round(255 * q);
      g = round(255 * v);
      b = round(255 * p);
      break;
    case 2:
      r = round(255 * p);
      g = round(255 * v);
      b = round(255 * t);
      break;
    case 3:
      r = round(255 * p);
      g = round(255 * q);
      b = round(255 * v);
      break;
    case 4:
      r = round(255 * t);
      g = round(255 * p);
      b = round(255 * v);
      break;
    default: // case 5:
      r = round(255 * v);
      g = round(255 * p);
      b = round(255 * q);
  }

  return {r, g, b};
}

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266 wifi rgb!");
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleApiRequest() {

  SERIAL.println("### API Request:");
    /* 
    // DEBUG CODE
    String headers;
    headers += "HTTP Headers:\n";
    headers += server.headers();
    headers += "\n";

    for (uint8_t i = 0; i < server.headers(); i++) {
      headers += " " + server.headerName(i) + ": " + server.header(i) + "\n";
    }
    SERIAL.println(headers);
    */
    if (server.hasArg("plain") == false) { //Check if body received
      server.send(200, "text/plain", "Body not received");
      return;
    }

    /*
    // DEBUG CODE
    String message;
    headers += "HTTP args:\n";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    SERIAL.println(message);
    SERIAL.println(server.arg("plain"));
    */
    
    const size_t bufferSize = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 70;
    DynamicJsonBuffer jsonBuffer(bufferSize);
    JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));

    SERIAL.println("JSON Body: ");
    root.printTo(SERIAL);
    SERIAL.println();

    const char* state = root["state"]; // "ON" or "OFF"
    if(strcmp("OFF", state) == 0) {
       SERIAL.println("State OFF found: switching off");
      // Set Output
      analogWrite(PinRed, 0);
      analogWrite(PinGreen, 0);
      analogWrite(PinBlue, 0);
      server.send(200, "application/json", server.arg("plain"));
      return;
    }

    int brightness = root["brightness"];
    SERIAL.print("Brightness: ");
    SERIAL.println(brightness);

    // DEBUG: color
    SERIAL.print("Color: ");
    root["color"].printTo(SERIAL);
    SERIAL.println();

    RGB rgb = {0, 0, 0};
    JsonObject& color = root["color"];
        
    // If RGB mode: Parse RGB values
    if(color["mode"] == "rgb") { 
      // Indeed, the JsonVariant returned by root["..."] has a special implementation of the == operator that knows how to compare string safely. 
      // See https://arduinojson.org/faq/why-does-my-device-crash-or-reboot/
      SERIAL.println("Reading RGB values...");
      rgb.r = color["r"];
      rgb.b = color["b"];
      rgb.g = color["g"];
    }

    // If HSV mode: Parse HSV values
    if(color["mode"] == "hsv") {  
      // Indeed, the JsonVariant returned by root["..."] has a special implementation of the == operator that knows how to compare string safely. 
      // See https://arduinojson.org/faq/why-does-my-device-crash-or-reboot/
      SERIAL.println("Reading HSV values...");
      rgb = hsvToRgb(color["h"], color["s"], color["v"]);
    }

    // DEBUG: Parsed values
    SERIAL.println("Parsed Values:");
    SERIAL.print("r=");
    SERIAL.print(rgb.r);
    SERIAL.print(", g=");
    SERIAL.print(rgb.g);
    SERIAL.print(", b=");
    SERIAL.println(rgb.b);

    // Map Brightness
    byte mappedRed = map(rgb.r, 0, 100, 0, brightness);
    byte mappedGreen = map(rgb.g, 0, 100, 0, brightness);
    byte mappedBlue = map(rgb.b, 0, 100, 0, brightness);

    // DEBUG: Brighness Mapped values
    SERIAL.println("Brighness Mapped RGB Values:");
    SERIAL.print("r=");
    SERIAL.print(mappedRed);
    SERIAL.print(", g=");
    SERIAL.print(mappedGreen);
    SERIAL.print(", b=");
    SERIAL.println(mappedBlue);


    // TODO: support different modes
    const char* jsonrgbmode = root["mode"]; // "SOLID"

    // Set Output
    analogWrite(PinRed, mappedRed);
    analogWrite(PinGreen, mappedGreen);
    analogWrite(PinBlue, mappedBlue);
    LevelRed = (int)mappedRed;
    LevelGreen = (int)mappedGreen;
    LevelBlue = (int)mappedBlue;

    server.send(200, "application/json", server.arg("plain"));
}

void resetOutputs() {
  analogWrite(PinRed, 255);
  analogWrite(PinGreen, 255);
  analogWrite(PinBlue, 255);
  
  analogWrite(PinRed, 0);
  analogWrite(PinGreen, 0);
  analogWrite(PinBlue, 0);
    LevelRed = 0;
    LevelGreen = 0;
    LevelBlue = 0;  
}














void webserver_setup(){
  // Root and 404
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  // iro.js User Interface and Javascript
  server.on("/ui", HTTP_GET, []() {
    server.send_P(200, "text/html", WEBINTERFACE);
  });
  server.on("/admin", HTTP_GET, []() {
    server.send_P(200, "text/html", WEBADMIN);
  });
  server.on("/iro.min.js", HTTP_GET, []() {
    server.send_P(200, "application/javascript", IRO_JS);
  });
   
  // REST-API
  server.on("/api/v1/state", HTTP_POST, handleApiRequest);
  server.on("/api/v1/reset", HTTP_GET, resetOutputs);

  server.begin();
}

void webserver_loop(){
    server.handleClient();
}