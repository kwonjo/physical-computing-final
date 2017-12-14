// This #include statement was automatically added by the IDE.
#include "SharpIR.h"
#include <SharpIR.h>
#define ir A0
#define model 1080
#include <math.h> 

// Servo motor(Sun comes up)
Servo myservo;  // create servo object to control a servo
int potpin = A4;  // A4 analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int mappedVal; // mapped value for servo

// InfraIR(Sun to Apple)
int sensorPin = A0; //Anologue
SharpIR SharpIR(ir, model);
float reading;
int dist_cm;

// ButtonLED(Pikachu eats Apple)
int buttonPin1 = D7;

// ButtonLED(Thunder bolt)
int ledPin = D1;
int buttonPin2 = D0;//pepper button

// HTML(On Going)
int page = 1; //starts with 1.html and changes over reaction

void setup(){
    Serial.begin(9600);
// HTML
    Particle.variable("page", page);
// Servo motor  
    myservo.attach(D2);  // attaches the servo on D2 to the servo object
// InfraIR
   for(int i=4; i<7; i++){
        pinMode(i, OUTPUT); //D4, D5, D6
    }
// ButtonLED(Pikachu eats Apple)
    pinMode(buttonPin1, INPUT_PULLUP);

// ButtonLED(Thunder bolt)
  pinMode(buttonPin2, INPUT_PULLUP); 
  pinMode(ledPin, OUTPUT); 
  pinMode(potpin, INPUT);
}


void loop()
{
    Serial.print("Page: ");
    Serial.println(page);
    // servo motor
    val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
    Serial.println(val);
    mappedVal = map(val, 0, 4095, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(mappedVal);                  // sets the servo position according to the scaled value
    delay(15);                           // waits for the servo to get there

    if(val >= 5  && val < 500)
    {
        page=2;//html
    } 
    if(val >= 500 && val < 1000)
    {
        page=3;//html
    } 
    // InfraIR
    reading = analogRead(sensorPin); //read the sensorPin
    int dist_cm = SharpIR.distance();  
        
    if(dist_cm>=0 && dist_cm<11)
    {
        for(int i=4; i<7; i++)
        {
            digitalWrite(i, HIGH); //all lights are ON 
        }
        Particle.publish("light_status", "less than 10cm");
    }
    else
    {
        for(int i=4; i<7; i++)
        {
            digitalWrite(i, LOW); //D4, D5, D6 is OFF
        }
    }
    delay(50);
    
    //Button change page
    int buttonState1 = digitalRead(buttonPin1);
    if(buttonState1 == LOW)
    {
        page=4; //html
    }
    
    //ButtonLED (thunderblot attack)
    int buttonState2 = digitalRead(buttonPin2);
    if(buttonState2 == LOW)
    {
        digitalWrite(ledPin, HIGH);
        page=5; //html
    }else
    {
        digitalWrite(ledPin, LOW);
    }
    
    //potentionmeter state sun down
    if(val>=3000)    
    {
        page=6; //html
    }
}
