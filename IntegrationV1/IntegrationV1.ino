#include <LiquidCrystal.h>

/*
Code for CE3002 Demo:
 */

/*
 * Variables Declaration
 */

#define BLUE 3 // select the pin for the green LED
#define GREEN 2 // select the pin for the red LED
#define RED 1 // select the pin for the blue LED
#define BUZZ 10 //BUZZ to arduino pin 9 

#define LCD_RS 9
#define LCD_EN 8
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


unsigned long StartTime;
unsigned long CurrentTime;
unsigned long ElapsedTime;
int sig;
int flag=0;
int hbeat=0;
int realhbeat=1;


void setup () {
  pinMode (GREEN, OUTPUT);
  pinMode (BLUE, OUTPUT);
  pinMode (RED, OUTPUT);
  pinMode (BUZZ, OUTPUT);
  lcd.begin(16,2);
  Serial.begin(1200);
  pinMode(A0,INPUT); //connected to D7
  lcd.print("Insert Your Finger! ");
  StartTime = millis();
}

 
void loop () {
 // sig= 1000;
  //read in signal 0 - 1023 for PPG
  
  sig=analogRead(A0);
  if(sig!=0){
    lcd.clear();
    lcd.print("HeartBeat:");
    lcd.print(sig);
  }
  
  if(sig >=1000 && flag ==0)
  {
      
    analogWrite (RED,  100);      //red
    delay(10);
    tone(BUZZ, 1000); // Send 1KHz sound signal...
    delay(90);        // ...for 1 sec
    noTone(BUZZ);     // Stop sound...
    delay(10);        // ...for 1sec 
    flag=1;
    hbeat++;
    
  }
  else if ( sig >=700 && flag == 1)
          flag=0;

 CurrentTime = millis();
 ElapsedTime = CurrentTime - StartTime;

 if (ElapsedTime>=10000){
 //realhbeat=hbeat*6;
 // hbeat=0;
 StartTime = millis(); 
 CurrentTime=0;
 ElapsedTime=0;
 //Serial.println(realhbeat);
 }
 //Serial.println(ElapsedTime);
 
 //delay(1000);
        
  Serial.println(sig);

 
 // analogWrite (GREEN,   100);  //green
  //analogWrite (BLUE, 100);    //blue
 // analogWrite (RED,  100);      //red

  /*  tone(BUZZ, 1000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(BUZZ);     // Stop sound...
      delay(500);        // ...for 1sec 
      */
 
}
