#include <WiFi.h>
#include <WiFiUdp.h>

#define ANSWERTIME 5000
#define MAXPLAYERS 6

enum {red,blue,green,yellow,purple};
const char *ssid = "stayhydrated";

boolean pause = false;

char* packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
String  ReplyBuffer = "OK\r\n";

unsigned int localPort = 8888;      // local port to listen on

int votecount;
int questionTime;
bool nextQuestion = true;

WiFiServer server(80);
IPAddress broadcastIp = WiFi.localIP();

int playerstats[] = {0,0,0,0,0};
int currentPlayerstats[] = {0,0,0,0,0};

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  WiFi.softAP(ssid);

  broadcastIp[3] = 255;
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(IP);
  
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
                  packetSize,
                  Udp.remoteIP().toString().c_str(), Udp.remotePort(),
                  Udp.destinationIP().toString().c_str(), Udp.localPort(),
                  ESP.getFreeHeap());

    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    String msg = "";
    for(int i = 0; i<n;i++){
      msg+=packetBuffer[i];
    }
    Serial.println("Contents:");
    Serial.println(String(msg));
    
    if (msg.equals("STATUS")) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      ReplyBuffer =  "OK\r\n";
      Udp.write(ReplyBuffer);
      Udp.endPacket();
    }
    if (msg.equals("RED")){
      currentPlayerstats[red]+=1;
      votecount++;
    }
    if (msg.equals("BLUE")){
      currentPlayerstats[blue]+=1;
      votecount++;
    }
    if (msg.equals("GREEN")){
      currentPlayerstats[green]+=1;
      votecount++;
    }
    if (msg.equals("YELLOW")){
      currentPlayerstats[yellow]+=1;
      votecount++;
    }
    if (msg.equals("PURPLE")){
      currentPlayerstats[purple]+=1;
      votecount++;
    }

    if(nextQuestion){
      Udp.beginPacket(broadcastIp);
      Udp.write("Question/r/n");
      Udp.endPacket();
      questionTime = millis();
      nextQuestion = false;
    }

    //conditions for result fulfilled
    if(millis()>questionTime+ANSWERTIME||votecount>=MAXPLAYERS){
      
      //show voting result, turn rotor etc
      
      do{
        
        //check if pause
        
      } while(pause);
      
      nextQuestion = true;
    }
  }
}
  
  
  
  
