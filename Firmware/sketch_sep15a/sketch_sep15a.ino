#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include "MAX17048.h"
#include <DNSServer.h>

const char* ssid = "KeyChain";
const char* password = "12345678";

WebServer server(80);
MAX17048 pwr_mgmt;
DNSServer dnsServer;

void handleRoot() {
  uint8_t battery = pwr_mgmt.percent();
  String html = "<html><body>";
  html += "<h1>Hello!</h1>";
  html += "<p>My name is Alimzhan Karash</p>";
  html += "<p>I am from Kazakhstan</p>";
  html += "<p>Here is my GitHub: <a href='https://github.com/zzertexx/'>github.com/zzertexx</a></p>";
  html += "<p>Battery: " + String(battery) + "%</p>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wire.begin(20, 21);
  pwr_mgmt.attatch(Wire);

  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());

  dnsServer.start(53, "*", apIP);

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
