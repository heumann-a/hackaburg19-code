
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


const char *ssid = "stayhydrated";

WiFiServer server(80);




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
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Request detected");
    String curLine = "";                // save incoming data to String
    if (client.connected()) {
      while (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') { 
          if (curLine.endsWith("connetionTest")) {
            client.println("connected");
          }
      }
    }
  }
}
