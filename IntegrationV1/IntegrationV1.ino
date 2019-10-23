#include <LiquidCrystal.h>

/*
Code for CE3002 Demo:
 */

/*
 * Variables Declaration
 */

#define PUSH1 12 //low hb push button
#define PUSH2 13 //high hb push button

#define BLUE 3 // select the pin for the green LED
#define GREEN 2 // select the pin for the red LED
#define RED 11 // select the pin for the blue LED
#define BUZZ 10 //BUZZ to arduino pin 9 

//LCD pins
#define LCD_RS 9
#define LCD_EN 8
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//Time keeping
unsigned long StartTime;
unsigned long CurrentTime;
unsigned long ElapsedTime;

//Signals and Flags
int sig = 0; //sensor output
int weakhb; //pushbuttonLow
int stronghb; //pushbuttonHigh
int flag=0; //up/down
int hbeat=0; //pulse
int realhbeat=1; //real hearbeat

//max, min beats
int maxb;
int minb;


void setup () {
  Serial.println("Connected");
  pinMode(PUSH1, INPUT);
  pinMode(PUSH2, INPUT);

  pinMode (GREEN, OUTPUT);
  pinMode (BLUE, OUTPUT);
  pinMode (RED, OUTPUT);
  pinMode (BUZZ, OUTPUT);

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Please Insert");
  lcd.setCursor(0,1);
  lcd.print("Your Finger!");
  Serial.begin(1200);

  pinMode(A0,INPUT); //data collected from the ADC 
  
  //if no value from sensor, polling until there is value.
  while (sig = 0)
    sig = analogRead(A0);
  
  //Calibrating otherwise
  //Warm up 5s from when signal is detected
  for (int counter = 5; counter > 0; counter--){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Calibrating...:");
    lcd.setCursor(0,1);
    lcd.print(10+counter);
    lcd.print(" sec");
    delay(1000);
  }

  maxb= minb = 10; //ensure max or min value is at least/at most 10        
  for(int counter = 10; counter > 0; counter--){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Calibrating...:");
    lcd.setCursor(0,1);
    lcd.print(counter);
    lcd.print(" sec");

    for (int sample = 100; sample>0; sample--){
      sig = analogRead(A0); //Read in signal first
      maxb = max(sig, maxb); //find max, min peak of graph
      minb = min (sig, minb);
      delay(10); //collecting 100 Samples in 10ms each => 1000ms = 1sec
    }
    //reapeat until 10 sec pass
  }
  Serial.println(maxb); //For debug purpose
  StartTime = millis();
  lcd.clear();
  lcd.print("Reading...");
}
 
void loop () {

  //For simulation testing | COMMENT OUT
  maxb = 900;
  sig= 1000;
  //sig=analogRead(A0);

  weakhb=digitalRead(PUSH1); //read button LOW
  stronghb=digitalRead(PUSH2); // read button HIGH
  if (weakhb == stronghb){
    if(sig >=(maxb-50) && flag ==0)//&& weakhb<500 && stronghb<500 )
    {
        
      analogWrite (RED,  100);      //red
      delay(10);
      tone(BUZZ, 1000); // Send 1KHz sound signal...
      analogWrite (RED,  0);      //red
      delay(80);        // ...for 80m sec
      
      noTone(BUZZ);     // Stop sound...
      delay(10);        // ...for 10m sec 
    
      flag=1;
      hbeat++;
      
    }
    //for simulation purpose | COMMENT OUT
    delay(1000);
    maxb = 1100;

    if ( sig <=(maxb-50) && flag == 1)
      flag=0;
    
    CurrentTime = millis();
    ElapsedTime = CurrentTime - StartTime;
    //Serial.println(hbeat);
    if (ElapsedTime>=10000){
    lcd.clear();
    realhbeat=hbeat*6;
    hbeat=0;
    StartTime = millis(); 
    CurrentTime=0;
    ElapsedTime=0;
    lcd.print("HeartBeat:");
    lcd.setCursor(0,1);
    lcd.print(realhbeat);
    lcd.print(" BPM");
    //Serial.println(realhbeat);
      }  
}
 
        // Serial.println(ElapsedTime);
 
        //delay(1000);
        
 //Serial.println(sig);
  else{
    if(weakhb)
    {
        analogWrite (BLUE,  255);      //blue
        delay(10);
        tone(BUZZ, 1000); // Send 1KHz sound signal...
        delay(20);        // ...for 80m sec
        //noTone(BUZZ);     // Stop sound...
        delay(10);        // ...for 10m sec 
        lcd.clear();
        lcd.print("Weak heartbeat!!!");
    }

    else if (stronghb)
    {
        analogWrite (RED,  255);      //green
        delay(68);
        tone(BUZZ, 1000); // Send 1KHz sound signal...
        delay(60);        // ...for 80m sec
        noTone(BUZZ);     // Stop sound...
        delay(20);        // ...for 10m sec 
        lcd.clear();
        lcd.print("Strong heartbeat!!!");   
    }
    analogWrite(BLUE, 0);
    analogWrite(RED, 0);
  }
}