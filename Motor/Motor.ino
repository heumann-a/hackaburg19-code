// Stepper Bibliothek
#include <Stepper.h>

// Anzahl der Schritte pro interner Motorumdrehung
const float STEPS_PER_REV = 32; 

//Modulo Wert der ganzen Umdrehungen
int modulo;

//max nummer an spielern
const int maxPlayers = 5;


//player the arrow is pointing at
int player;

void Modulo(int);
int toSteps(int, int);

double stepsPerRevolution = 2048;
//steps zwischen spielern
const int step = stepsPerRevolution / maxPlayers;

// IN 1 -> Dig. PIN 27, IN 2 -> Dig. PIN 25, IN 3 -> Dig. PIN 26, IN 4 -> Dig. PIN 33
Stepper myStepper(stepsPerRevolution, 27, 26, 25, 33);
void setup() {
  // 1000Hz/4096 Halbschritte = 0.244 Hz = ca. 15 RPM
  myStepper.setSpeed(15);
  Serial.begin(9600);
  player = 1;
}
void loop() {
  
  

 //Serial.println(toSteps(player,5));
  myStepper.step(toSteps(player,5));
  Serial.println("step1");
  delay(3000);

 //Serial.println(toSteps(player,5));
  myStepper.step(toSteps(player,2));
  Serial.println("step2");
  delay(3000);
  
  //Serial.println(toSteps(player,5));
  myStepper.step(toSteps(player,1));
  Serial.println("step3");
  delay(3000);


  
}

void Modulo(int steps){
  modulo = (modulo + steps)% 2048;
}

int toSteps(int start, int goal){
  player = goal;
  if(start==goal)return 0;
  if(goal>start){
    Serial.println((goal-start)*step);
    return (goal-start)*step;   
  }
  Serial.println(-1*(start-goal));
  return -1*(start-goal)*step;
}
