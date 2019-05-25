#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Stepper.h>


#define ANSWERTIME 10000        //10 seconds *1000milliseconds
#define MAXPLAYERS 5

const float STEPS_PER_REV = 32;
double stepsPerRevolution = 2048;

const int stepsBetween = stepsPerRevolution/MAXPLAYERS;



enum {red, blue, green, yellow, purple};
boolean standby = false;

int votecount;
int questionTime;
bool nextQuestion = true;
String question = "Wait for the game to start";

int playerstats[] = {0, 0, 0, 0, 0};
int currentPlayerstats[] = {0, 0, 0, 0, 0};

int nextQuestionRecieved = 0;

int currQuestion=0;
String questionField[] = {"Who makes the most commits",
"First Commit?",
"Who drinks the most coffee?",
"Who writes the worst code?",
"Worst commit messages?",
"Mr. Neversleep?",
"Apple Fanboy",
"Who would mess up prod?",
"Most bugs?",
"The Laziest?"};

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot();              // function prototypes for HTTP handlers
void handleQuestion();
void handleAnswer();
void handleConnected();

const char *ssid = "HydrationGame"; // The name of the Wi-Fi network that will be created
const char *password = "123456789";  // The password required to connect to it

int player;
int dif;
int targetPlayer;
int toSteps(int, int);
Stepper myStepper(stepsPerRevolution, 5, 4, 14, 12);

void setup(void){
  Serial.begin(9600);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("stayhydrated")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/question", HTTP_GET, handleQuestion);
  server.on("/answer", HTTP_POST, handleAnswer); // Call the 'handleLogin' function when a POST request is made to URI "/login"
  server.on("/connected", HTTP_GET, handleConnected);
  server.onNotFound(handleNotFound);           // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                            // Actually start the server
  Serial.println("HTTP server started");

  myStepper.setSpeed(15);
  player = 0;
}
void loop(void){
  server.handleClient();                     // Listen for HTTP requests from clients
  
  //conditions for result fulfilled
  if ((millis() > questionTime + ANSWERTIME && votecount>0) || votecount >= MAXPLAYERS) {

    //show voting result, turn rotor etc
    
    do {
      targetPlayer=mostVoted(playerstats);
      myStepper.step(toSteps(player,targetPlayer));
      

    } while (player!=targetPlayer);

    nextQuestion = true;
  }

  if (nextQuestion) {
    question = questionField[currQuestion]; // Get next Question from sd card
    currQuestion++;
    if(currQuestion>9)currQuestion=0;
    questionTime = millis();
    nextQuestion = false;
    votecount = 0;
    for(int i=0;i<MAXPLAYERS;i++){
      playerstats[i]=0;
    }
  }
}



/*
 * HANDLER FUNCTIONS
 */
void handleRoot(){
  server.send(200, "text/html","<h1>You are connected to StayHydrated AP!</h1>");
}
void handleQuestion(){
  String msg = "";
  if(millis()-questionTime<1000)msg += question;
  server.send(200, "text/html",msg);
}
void handleAnswer(){
  String msg;
  String text = "<p>You voted for: ";
  if(server.arg("answer") != NULL){ //192.168.4.1/answer?answer=RED
    msg = server.arg("answer");
    Serial.println(msg);
    text += msg;
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
  text += "</p>";

  server.send(200, "text/html", text);
}
void handleConnected(){
  Serial.println("Device Detected");
  server.send(200, "text/html", "");
}
void handleNotFound(){
  server.send(404, "text/html", "<p>404: Not found</p>"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}


int toSteps(int start, int goal){
  player = goal;
  dif = (start-player);
  if(dif==4){
    Serial.println("case 4");
    return -1*stepsBetween;
  }
  if(dif==-4){
    Serial.println("case -4");
    return 1*stepsBetween;
  }
  if(dif==3){
    Serial.println("case 3");
    return -2*stepsBetween;
  }
  if(dif==-3){
    Serial.println("case -3");
    return 2*stepsBetween;
  }
  Serial.println("Spieler ueberfahren:");
  Serial.println(dif);
  return dif*stepsBetween;
}

int mostVoted(int votes[]){
  int index = 0;
  for(int i=1;i<MAXPLAYERS;i++){
    if(votes[index]<votes[i]) index=i;
  }
  Serial.println("Winner is:");
  Serial.println(index);
  return index;
}
