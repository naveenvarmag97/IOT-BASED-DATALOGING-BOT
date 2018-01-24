
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT DebugSerial


// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#include "DHT.h"

#define DHTPIN 5   
#define DHTTYPE DHT11
#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "40fbe660c64c4c51a32dddb5d1dbb243";
DHT dht(DHTPIN, DHTTYPE);
const int trigPin = 6;
const int echoPin = 7;
// defines variables
long duration;
int distance;
void setup()
{
  // Debug console
  DebugSerial.begin(9600);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
   dht.begin();
  Blynk.begin(Serial, auth);
  
}

BLYNK_READ(V3)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
  Blynk.virtualWrite(V3,distance );
}
BLYNK_READ(V5)
{
   float t = dht.readTemperature();
  Blynk.virtualWrite(V5,t );
}
BLYNK_READ(V6)
{
   float h = dht.readHumidity();
  Blynk.virtualWrite(V6,h );
}
  BLYNK_WRITE(V1) // There is a Widget that WRITEs data to V1 
  {
    int v = param[0].asInt(); // get a RED channel value
    int h = param[1].asInt(); // get a GREEN channel value
  if(v==1&&h==1)
  {digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
    delay(1000);
  }
    if(v==2&&h==1)
  {digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
    delay(1000);
  }
    if(v==0&&h==1)
  {digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
    delay(1000);
  }
    if(v==1&&h==0)
  {digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
    delay(1000);
  }
    if(v==1&&h==2)
  {digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
    delay(1000);
  }
    if(v==2&&h==0)
  {digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
    delay(1000);
  }
    if(v==2&&h==2)
  {digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
    delay(1000);
  }
    if(v==0&&h==0)
  {digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
    delay(1000);
  }
    else
  {digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
    delay(1000);
  }
  }
  
void loop()
{
  Blynk.run();
}
