#include<ESP8266WiFi.h>
#include<Servo.h>
#include<ThingSpeak.h>

WiFiClient client;
Servo myservo;


int pos;
long ChannelNo=  1226908;
char myAPIKey[]= "NJ4XMG411ENBPI7S";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(D6);
  WiFi.begin("BOSS", "Rahul_2000");
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print("...");
    delay(100);
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float x= analogRead(A0);
  Serial.print("Moisture value=");Serial.println(x);
  ThingSpeak.writeField(ChannelNo, 1, x, myAPIKey);
  if(x >= 700)
  {
    for(pos=0; pos<=180; pos+= 1)
    {
      myservo.write(pos);
      delay(10);
    }
    Serial.print("Watering");
    while(x>=350)
    {
      Serial.print("...");
      x= analogRead(A0);
      delay(1000);
    }
    Serial.print("Done watering :)");
    for(pos=180; pos>=0; pos-=1)
    {
      myservo.write(pos);
      delay(10);
    }
  }
  delay(50);
}
