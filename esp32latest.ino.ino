

//---------------------------------------------------------------
// This example uses an ESP8266 or ESP32 Board to connect to shiftr.io.
// Modified by Ilias Lamprou at sep/25/2018
// You can check on your device after a successful connection here: https://shiftr.io/try.
// Original example by Joël Gähwiler https://github.com/256dpi/arduino-mqtt
//---------------------------------------------------------------

//#include <ESP8266WiFi.h>  // ESP8266
#include <WiFi.h>       // for ESP32 enable this line and disable the previous
#include <MQTTClient.h>
#include <SoftwareSerial.h>
SoftwareSerial sw(3,1); // RX, TX
int a=1;
//------ wifi settings
char ssid[] = "Epic Lab"; //  Change this to your network SSID (name).
char pass[] = "@@ataikram@@";  // Change this your network password

//------ MQTT broker settings and topics
const char* broker = "broker.shiftr.io"; 
char mqttUserName[] = "virtuinos";         
char mqttPass[] = "12345678";               

const char* topic_pub_temperature = "input_1"; 

String arr[100];
String payload1;
int count=0;
WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;

//========================================= connect
void connect() {
  Serial.print("\nconnecting to wifi.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
  //--- create a random client id
  char clientID[] ="ESP8266_0000000000";  // For random generation of client ID.
  for (int i = 8; i <18 ; i++) clientID[i]=  char(48+random(10));
    
  Serial.print("\nconnecting to broker...");
  while (!client.connect(clientID,mqttUserName,mqttPass)) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nconnected!");
  client.subscribe("input_1");
  // client.unsubscribe("motor_command");
}

//========================================= messageReceived
void messageReceived(String &topic, String &payload) {
 // Serial.println(payload);

//&& payload!=arr[count-1]
  
    if(payload!="0"  ){
       payload1=payload;
         arr[count]=payload;
         
         Serial.println(arr[count]);
         
         client.unsubscribe("input_1");
         count=count+1;
         Serial.println(count);
   
         payload="0";
        // delay(1000);
     }
  
  
  
}

//========================================= setup
//=========================================
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass); // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino. You need to set the IP address directly.
  client.begin(broker, net);
//  pinMode(D4,OUTPUT);
  client.onMessage(messageReceived);
  connect();
  // sw.begin(115200);
   pinMode(4,OUTPUT);
}
//========================================= loop
//=========================================
void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  if (!client.connected()){
  connect();
  
  }
  client.subscribe("input_1");
  

       if(payload1=="2")
  {
     Serial.println("da");
        digitalWrite(4,HIGH);
        delay(1000);
        digitalWrite(4,LOW);
      //client.unsubscribe("input_1");
     payload1="0";
   // delay(1000);
  }

 if (Serial.available() > 0) {
     char bfr[501];
     char bfr1[501];
     memset(bfr,0, 501);
     Serial.readBytesUntil( '\n',bfr,500);
    // publishSerialData(bfr);
     Serial.print("data=");
     Serial.println(bfr);
     String phrase;

phrase = String(phrase + bfr);
int b=phrase.length();
Serial.println(b);
for(int j=0;j<count;j++)
{

//if(b==5)
//{
int a= phrase.compareTo(arr[j]);
     if(a==13)
     
     {
        Serial.println("da");
        digitalWrite(4,HIGH);
     delay(5000);
     digitalWrite(4,LOW);
     delay(5000);
     }
//     if(==1)
//     {
//
//          Serial.println("da");
//     }
//}

//     if(phrase==arr[j])
//     
//     {
//          Serial.print("da");
//     }
  
}  }
 
}
