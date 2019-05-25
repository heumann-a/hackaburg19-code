// Stepper Bibliothek
#include <Stepper.h>




// Anzahl der Schritte pro interner Motorumdrehung
const float STEPS_PER_REV = 32; 

//Modulo Wert der ganzen Umdrehungen
int modulo;

//max nummer an spielern
const int maxPlayers = 5;

//number of players playing
int numberPlayers = 5;

//array mit den votes pro spieler
int points[5];

//player the arrow is pointing at
int player;

void Modulo(int);
int toSteps(int, int);
void spin(int);
int mostVoted(int[]);

double stepsPerRevolution = 2048;
//steps zwischen spielern
const int step = stepsPerRevolution / maxPlayers;




// IN 1 -> Dig. PIN 27, IN 2 -> Dig. PIN 25, IN 3 -> Dig. PIN 26, IN 4 -> Dig. PIN 33
Stepper myStepper(stepsPerRevolution, 5, 4, 14, 12);
void setup() {
  // 1000Hz/4096 Halbschritte = 0.244 Hz = ca. 15 RPM
  myStepper.setSpeed(15);
  Serial.begin(9600);
  player = 1;
  Serial.println("Setup erledigt");
}
void loop() {
  Serial.println("loop beginnt");
 
  myStepper.step(2048);
  
  Serial.println("loop endet");
  delay (500);

}



int toSteps(int start, int goal){
  player = goal;
  if(start==goal)return 0;
  if(goal>start){
    Serial.println((goal-start)*step);
    return (goal-start)*step;   
  }
  Serial.println(-1*(start-goal)*step);
  return -1*(start-goal)*step;
}

void spin (int numberOfRounds){
  for(int i=1; i<=numberOfRounds; i++){
    Serial.println(i);
  if(random(0, 2)<1){
  myStepper.step(numberOfRounds * stepsPerRevolution);
  }else{
   myStepper.step(-numberOfRounds * stepsPerRevolution); 
    }
  }
}

int mostVoted(int votes[],int arrayLength){
    int index = 0; 
    for(int i = 0; i<arrayLength; i++){
      
      if(index<votes[i]) index = i;
    }
  return index;
}

void time (long tmp){
  unsigned long currentMillis = millis();
  unsigned long startMillis = millis();

    do{
      currentMillis = millis();
    }while(currentMillis-startMillis > tmp);
      
    
  

}
