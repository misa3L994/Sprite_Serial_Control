

/*
   Programa de prueba para la cabecera medeaWize.h
   Misael Reyes
   25/ENE/2023

*/
#include "medeaWiz.h"
//#include <SoftwareSerial.h>

byte answerVal; 
Sprite sprite(CMD_ADD_E1);
//SoftwareSerial Serial1(8, 9); // RX, TX

char c;
void setup() {

  Serial.begin(115200);// Serial debug
  Serial1.begin(9600);// Serial to Sprite
  sprite.begin(Serial1);// inicia comunicación con sprite
  
   menu('?'); // print the menu options.
}

void loop() {
  
  answerVal = sprite.answerSprite();

  if(answerVal != 0)
  {
    Serial.print(" Respuesta : 0x");
    Serial.println(answerVal,HEX);
  }
  
  if(Serial.available())
  {
    c = Serial.read();
    menu(c);
  }

}
void menu(char op){
  // Menu
  switch (op){
    case '?':
    case 'h':
        Serial.println("Serial Control Sprite Basic Commands:");
        Serial.println(" ? - Display Menu options. ");
        Serial.println(" P - Play 03 file");
        Serial.println(" S - Play 01 file in loop");
        Serial.println(" V - Play 01 file, full volume ");
        Serial.println(" p - Play");
        Serial.println(" a - pause");
        Serial.println(" > - Next");
        Serial.println(" < - Previous");
        Serial.println(" + - Volume UP");
        Serial.println(" - - Volume DOWN");
        Serial.println(" t - Query total file count");
        break;

    case 'P':
        Serial.println("Play");
        sprite.play(0x01);
        break;

   

    case 'S':
        Serial.println("Play loop");
        sprite.playLoop(0x01);
        break;

    case 'V':
        Serial.println("Play file at full volume");
        sprite.setFullVolume();
        sprite.play(0x01);
        break;


    case 'p':
        Serial.println("Play");
       sprite.play();
        break;

    case 'a':
        Serial.println("Pause");
        sprite.pause();
        break;


    case '>':
        Serial.println("Next");
        sprite.playNext();
        break;

    case '<':
        Serial.println("Previous");
        sprite.playPrevious();
        break;

    case '+':
        Serial.println("Volume UP");
        sprite.volUp();
        break;

    case '-':
        Serial.println("Volume Down");
        sprite.volDown();
        break;


    case 't':
        Serial.println("Query total file count");
        sprite.qTFiles();
        break;

    
  }
}
