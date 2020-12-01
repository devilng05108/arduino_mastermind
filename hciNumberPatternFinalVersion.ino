#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
 {'1','4','7','*'},
 {'2','5','8','0'},
 {'3','6','9','#'},
 {'A','B','C','D'}
};


byte rowPins[ROWS] = { 8, 9, 10, 11};
byte colPins[COLS] = { 4, 5, 6, 7 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledpin 13

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 102;
const int colorG = 255;
const int colorB = 179;

String playerPattern=""; //Stores the player's number
int count=0;
int randNumber = 1; //Stores digits of random number
String randPattern;
int score=0;
int player1score=0;
int player2score=0;
int turn = 0; //0 is player 1 ,1 is player 2 , 2 is both turns done
int newGame=0;
boolean done= false;
boolean goon=false;
boolean newgame=true;
boolean no_key= true;
boolean endgame=false;
boolean cont = false;



void setRandom()
{
  for(int x=0;x<randNumber;x++)
  {
    randPattern = randPattern + String(random(10));
  }
   
}

void displayPattern(){
  lcd.clear();
  lcd.print(randPattern);
  delay(3000);
  lcd.clear();
}

void setup()
{
    pinMode(ledpin,OUTPUT);
    digitalWrite(ledpin, HIGH);
    Serial.begin(9600);

  // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
}


void check(){
  
    
  if(playerPattern ==randPattern){
    if(turn==0){
      player1score= player1score+5;
      score=player1score;
    }
    if(turn==1){
      player2score = player2score+5;
      score=player2score;
    }
    lcd.clear();
    lcd.print("Correct!");
    lcd.setCursor(0,1);
    
    lcd.print("Score :"+String(score));
    delay(2000);
    if(score==50){
      turn = turn+1;
    }
  }
  else{
    if(turn==0){
      score=player1score;
    }
    if(turn==1){
      score=player2score;
    }
    lcd.clear();
    lcd.print("Incorrect");
    lcd.setCursor(0,1);
    lcd.print("Score :"+String(score));
    delay(2000);
    turn= turn+1;

  }
  playerPattern ="";
}

void loop()
{

  if(done==false){

    if(endgame==false){
    
     if(newgame==true){
            lcd.clear();
              lcd.print("New game starts!");
              delay(2000);
               randPattern="";
               newgame=false;
      }


          randPattern="";
          if(turn==0){
            lcd.clear();
            lcd.print("Player 1's turn");
            delay(2000);
          }
          if(turn==1){
            lcd.clear();
            lcd.print("Player 2's turn");
            delay(2000);
          }
          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter game level");
          lcd.setCursor(0,1);
          lcd.print("based on dice");


    }//ends endgame
          no_key=true;
    
    
    while(no_key){
      char gameLevel = kpd.getKey();
    if(gameLevel) {
      no_key=false;
      goon=true;
      switch (gameLevel)
      {
        case '1':
        randNumber =6;
        endgame=false;
        cont=false;
        break;
        
        case '2':
        randNumber =7;
        endgame=false;
        cont=false;
        break;
        
        case '3':
        randNumber =8;
        endgame=false;
        cont=false;
        break;
  
        case '4':
        randNumber =9;
        endgame=false;
        cont=false;
        break;
  
        case '5':
        randNumber =10;
        endgame=false;
        cont=false;
        break;
  
        case '6':
        randNumber =11;
        endgame=false;
        cont=false;
        break;

        case 'B':
        endgame=true;
        done=false;
        newgame=true;
        cont=false;
        break;

        case 'A':
        newgame=true;
        cont=true;
        break;
  
        default:
        randNumber=12;
        endgame=false;
        cont=false;
        break;
        
      }//closed switch statement
      if(endgame==false){
        setRandom();
        displayPattern();
        lcd.print("Enter number");
        lcd.setCursor(0,1);
        lcd.print("pattern");
        done=true;
      }
      if(endgame==true and cont==false){
        lcd.clear();
        lcd.print("Bye! Exit game");
        lcd.setCursor(0,1);
        lcd.print("press A to play");
        delay(3000);
      }
      if(cont==true){
        done=false;
        endgame=false;
        newgame=true;
        turn=0;
        player1score=0;
        player2score=0;
        score=0;
      }
    }//closed if statement
    }//closed while loop
     

     

  }
  
  if(done==true){
    char key = kpd.getKey();
    if(key) 
    {
        playerPattern = playerPattern +String(key);
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print(String(playerPattern));
        count++;
         if(count==randNumber){
            check();
            
            if(turn==2){
              if(player1score > player2score){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Player 1 -" + String(player1score));
                lcd.setCursor(0,1);
                lcd.print("Player 2 -" + String(player2score));
                delay(2000);
              
                lcd.clear();
                lcd.print("Player 1 wins!");
                lcd.blink();
                delay(1500);
                lcd.noBlink();
                
              }
              if(player2score >player1score){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Player 1 -" + String(player1score));
                lcd.setCursor(0,1);
                lcd.print("Player 2 -" + String(player2score));
                delay(2000);
                lcd.clear();
                lcd.print("Player 2 wins!");
                delay(1500);
              }
              if(player1score==player2score){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Player 1 -" + String(player1score));
                lcd.setCursor(0,1);
                lcd.print("Player 2 -" + String(player2score));
                delay(2000);
                lcd.clear();
                lcd.print("Same scores");
                delay(1500);
              }
              turn=0;
              newgame=true;
              player1score=0;
              player2score=0;

            }
            
            count=0;
            done =false;
          }
    }
  }//closed done
}
