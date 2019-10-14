#include <LiquidCrystal.h>

/*
Code for CE3002 Demo:
 */

/*
 * Variables Declaration
 */
 
#define groundpin 8 // write 0 to get ground
#define bluepin 9 // select the pin for the green LED
#define greenpin 10 // select the pin for the red LED
#define redpin 11 // select the pin for the blue LED
#define buzzer 4 //buzzer to arduino pin 9 
#define grd 6 // grd for buzzer

#define LCD_RS 0
#define LCD_EN 1
#define LCD_D4 2
#define LCD_D5 3
#define LCD_D6 12
#define LCD_D7 13

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


unsigned long StartTime;
unsigned long CurrentTime;
unsigned long ElapsedTime;
int sig;
int flag=0;
int hbeat=0;
int realhbeat=1;


void setup () {
  pinMode (greenpin, OUTPUT);
  pinMode (bluepin, OUTPUT);
  pinMode (redpin, OUTPUT);
  pinMode (groundpin, OUTPUT);
 
  pinMode (buzzer, OUTPUT);
  pinMode (grd, OUTPUT);
  
  digitalWrite (groundpin, LOW);
  digitalWrite (grd, LOW);

  lcd.begin(16,2);
  

  Serial.begin(1200);
  pinMode(A0,INPUT); //connected to D7
  StartTime = millis();
}

 
void loop () {
  lcd.clear();
 // sig= 1000;
  sig=analogRead(A0);
  lcd.print("HeartBeat:");
  lcd.print(sig);
  
  if(sig >=1000 && flag ==0)
  {
      
    analogWrite (redpin,  100);      //red
    delay(10);
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(90);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
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

 
 // analogWrite (greenpin,   100);  //green
  //analogWrite (bluepin, 100);    //blue
 // analogWrite (redpin,  100);      //red

  /*  tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(500);        // ...for 1sec 
      */
 
}
