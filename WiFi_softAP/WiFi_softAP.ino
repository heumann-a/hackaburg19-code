#include <WiFi.h>

#define ANSWERTIME 5000
#define MAXPLAYERS 6

enum {red,blue,green,yellow,purple};
const char *ssid = "stayhydrated";
const char *pwd = "123456";

boolean pause = false;

int votecount;
int questionTime;
bool nextQuestion = true;

int playerstats[] = {0,0,0,0,0};
int currentPlayerstats[] = {0,0,0,0,0};

/*
 * create Server
 */
void createServer(){

  Serial.println("Starting server..");

  WiFi.softAP(ssid, pwd, 7);

  IPAddress IP = WiFi.softAPIP();

  Serial.println(IP);

  server.begin();

  Serial.print("Server created\n");

}


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  createServer();
}

void loop() {
  
  String msg="";//
  if (msg.equals("STATUS")) {
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    ReplyBuffer =  "OK\r\n";
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  if (msg.equals("RED")){
    currentPlayerstats[red]+=1;
    playerstats[red]+=1;
    votecount++;
  }
  if (msg.equals("BLUE")){
    currentPlayerstats[blue]+=1;
    playerstats[blue]+=1;
    votecount++;
  }
  if (msg.equals("GREEN")){
    currentPlayerstats[green]+=1;
    playerstats[green]+=1;
    votecount++;
  }
  if (msg.equals("YELLOW")){
    currentPlayerstats[yellow]+=1;
    playerstats[yellow]+=1;
    votecount++;
  }
  if (msg.equals("PURPLE")){
    currentPlayerstats[purple]+=1;
    playerstats[purple]+=1;
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

  
  
  
  
