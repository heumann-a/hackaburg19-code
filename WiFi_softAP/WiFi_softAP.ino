#include <WiFi.h>
#include <WiFiUdp.h>

#define ANSWERTIME 5000
#define MAXPLAYERS 6

#define UDPBUFSIZE 15

enum {red,blue,green,yellow,purple};
const char *ssid = "stayhydrated";
const char *pwd = "123456";
WiFiServer server(80);
WiFiUDP udpListener();
char *udpPuffer[UDPBUFSIZE];
boolean standby = false;

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
  createServer();

  Serial.println(udpListener.begin(8888)?"UDP listener started":"failed to start UDP listener");
}

void loop() {
  if(udpListener.parsePacket()>0){
    udpListener.read(updPuffer,UDPBUFSIZE);
  }
  String msg="";
  for(int i = 0;i<UDPBUFSIZE;i++){
    msg+=updPuffer[i];
  }
  Serial.println(msg);
  if (msg.equals("STATUS")) {
    //returnr 'OK' to client
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
    //push  next question to clients
    questionTime = millis();
    nextQuestion = false;
  }

  //conditions for result fulfilled
  if(millis()>questionTime+ANSWERTIME||votecount>=MAXPLAYERS){
    
    //show voting result, turn rotor etc
    
    do{
      
      //check if standby
      
    } while(standby);
    
    nextQuestion = true;
  }
}

  
  
  
  
