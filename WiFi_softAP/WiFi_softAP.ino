#include <WiFi.h>
#include <WebSocketServer.h>

#define ANSWERTIME 10000 //10 seconds *1000milliseconds
#define MAXPLAYERS 5

// #define UDPBUFSIZE 15

enum {red, blue, green, yellow, purple};
const char *ssid = "stayhydrated";
const char *pwd = "123456";
const int udpBufSize = 15;
 
WiFiServer server(80);
WebSocketServer webSocketServer;
byte udpPuffer[udpBufSize];
boolean standby = false;

int votecount;
int questionTime;
bool nextQuestion = true;
String question = "Wait for the game to start";

int playerstats[] = {0, 0, 0, 0, 0};
int currentPlayerstats[] = {0, 0, 0, 0, 0};

/*
  create Server
*/
void createServer() {

  Serial.println("Starting server..");

  WiFi.setHostname(ssid);
  WiFi.softAP(ssid, pwd);
  Serial.println(ssid);
  IPAddress IP = WiFi.softAPIP();

  Serial.println(IP);

  server.begin();

  Serial.print("Server created\n");

}


void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  createServer(); // Serial.println(udpListener.begin(8888)?"UDP listener started":"failed to start UDP listener");
}

void loop() {
  WiFiClient client = server.available();
 
  if (client.connected() && webSocketServer.handshake(client)) {

    String msg;
    
    while (client.connected()) {
 
      msg = webSocketServer.getData();
 
      if (data.length() > 0) {
         Serial.println(msg);
         if (msg.equals("STATUS")) {
           webSocketServer.sendData("OK");
         }
         if (msg.equals("QUESTION")) {
           webSocketServer.sendData(question);
         }
         if (msg.equals("RED")) {
           currentPlayerstats[red] += 1;
           playerstats[red] += 1;
           votecount++;
         }
         if (msg.equals("BLUE")) {
           currentPlayerstats[blue] += 1;
           playerstats[blue] += 1;
           votecount++;
         }
         if (msg.equals("GREEN")) {
           currentPlayerstats[green] += 1;
           playerstats[green] += 1;
           votecount++;
         }
         if (msg.equals("YELLOW")) {
           currentPlayerstats[yellow] += 1;
           playerstats[yellow] += 1;
           votecount++;
         }
         if (msg.equals("PURPLE")) {
           currentPlayerstats[purple] += 1;
           playerstats[purple] += 1;
           votecount++;
         }
      }
 
      delay(10); // Delay needed for receiving the data correctly
   }

  //conditions for result fulfilled
  if (millis() > questionTime + ANSWERTIME || votecount >= MAXPLAYERS) {

    //show voting result, turn rotor etc

    do {

      //check if standby

    } while (standby);

    nextQuestion = true;
  }

  if (nextQuestion) {
    question = ""
    
    questionTime = millis();
    nextQuestion = false;
  }
}
