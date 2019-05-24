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


    randomSeed(second()); 
    
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

void getQuestion(fs::FS &fs, const char * path, int maxindex){
  
  int index = random(0,maxindex);
  File file = fs.open(path);
  
  for(int i = 0; i < index; i++){
    if(file.available()){
      file.read();  
    }
  }
  
  
}


void loop() {
  const char* fragedatei = "/questions.txt";
  Serial.println(fragedatei);
  Serial.println("Test");
  if(!TestFile(SD, fragedatei)){
    Serial.println("Datei nicht gefunden!!");
  }
  char * test = new char[5];
  delay(5000);
 
}
