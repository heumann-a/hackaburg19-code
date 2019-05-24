
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


const char *ssid = "stayhydrated";

ESP8266WebServer server(80);


void handleRoot() {
  server.send(200, "text/html", "Get information from here.");
}
void handleConnectionTest() {
  server.send(200, "text/html", "<p>Connection established</p>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  WiFi.softAP(ssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(IP);
  server.on("/", handleRoot);
  server.on("/test", handleConnectionTest);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
