/*
  SD card file dump

  This example shows how to read a file from the SD card using the
  SD library and send it over the serial port.

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created  22 December 2010
  by Limor Fried
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include "FS.h"
#include <SD.h>
#include <time.h>
#include <string.h>

void setupSD() {


    randomSeed(5); 
    
    Serial.begin(115200);
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    /*
    //DEBUG INFOS 
    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
    //ENDE DEBUG INFOS
    */
    
}

void setup(){
  setupSD();
}

bool TestFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return false;
    }
    /*
    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    } */
    file.close();
    return true;
}

String getQuestion(fs::FS &fs, const char * path, int maxindex){

  int index = random(0,maxindex-1);
  String question;
  char c;
  static int lastquestions[2] = {-1};
  File file = fs.open(path);
 if(!file){
    Serial.println("Failed to open file for appending");
    return "0";
  
  }

  //Check if Question was in last 2 Questions
  for(int k = 0; k < 2; k++){
    if(index == lastquestions[k]){
      index = random(0,maxindex-1);  
      k = 0;
    }else if(lastquestions[k] == -1){
      lastquestions[k] = index;
    }else{
      lastquestions[k] = index;  
    }
  }

  Serial.println(index);
  int i = -1;
  do{
    question = file.readStringUntil('\n');
    ++i;
  }while(file.available() && (i < index) );
  
  
  
  Serial.println(question);
  return question;
}


void appendQuestion(fs::FS &fs, const char * path, const char * message){
  
    Serial.printf("Appending to file: %s Question: %s\n", path,message);
    
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    file.print('\n');
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

int getQuestionNumber(fs::FS &fs, const char * path){

  File file = fs.open(path);
  return file.parseInt();
  
}


void loop() {
  const char* fragedatei = "/questions.txt";
  const char* anzahlfragendatei = "/questionsnumbers.txt";
  int anzahlfragen = 0;
  String frage;
  Serial.println("Test");
  Serial.println(fragedatei);

  anzahlfragen = getQuestionNumber(SD,anzahlfragendatei);
  frage = getQuestion(SD, fragedatei, anzahlfragen);
  //appendQuestion(SD, fragedatei, "hat das alles geklappt?");

  Serial.println(frage);
  delay(5000);
 
}
