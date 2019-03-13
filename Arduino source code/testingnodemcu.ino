#include <ESP8266WiFi.h>
 
String apiKey = "BWHO48MDSCU52YQI";

const char *ssid =  "Prabhu D";
const char *pass =  "Prabhu D.sp.9468";
const char* server = "api.thingspeak.com";

int air = A0;

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(100);
      pinMode(air, INPUT);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
            //WiFi.begin(ssid, pass);
     }
      Serial.println("");
      Serial.println("WiFi connected");
}
 
void loop() 
{
  int analogSensor = analogRead(air);
  Serial.print("sensor adc");
  Serial.print(analogSensor);
  float per = analogSensor/10.24;
  Serial.println(per);
  int t = (int)per;
  //int t = random(100);
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
    
     String postStr = apiKey;
     postStr +="&field1=";
     postStr += String(t);
     postStr +="&field2=";
     postStr += String(analogSensor);
     postStr += "\r\n\r\n";
  
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);
  
     Serial.println("Polluted Air: ");
     Serial.print(t);
     Serial.print("%");
    }
  client.stop();
  Serial.println("Refreshing...");
  delay(5000);
}
