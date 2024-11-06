#include <ESP8266WiFi.h>
 
const char* ssid = "SUPERONLINE_Wi-Fi_2PK4";
const char* password = "ZCU5bzKC9RUf";

int In1 = D1 ;
int In2 =D2 ;
int EnA =D0 ;
int In3 =D3 ;
int In4 =D4 ;
int EnB =D5 ;

int hiz = 150;
 
/*int ledPin = 2;*/ 


 
void setup() {
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
Serial.begin(115200);
delay(10);
 
// Wifi bağlantısı
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.print(WiFi.localIP());
 
}
 
void loop() {
forward();
delay(1500);
stoped();
delay(3000);
back();
delay(1000);
right();
delay(1000);
left();
delay(1000);
stoped();
delay(3000);

}

void stoped(){
  analogWrite(EnA,0);
  digitalWrite(In1,0);
  digitalWrite(In2,1);
  analogWrite(EnB,0);
  digitalWrite(In3,0);
  digitalWrite(In4,1);
}

void back(){
  analogWrite(EnA,hiz);
  digitalWrite(In1,1);
  digitalWrite(In2,0);
  analogWrite(EnB,hiz);
  digitalWrite(In3,0);
  digitalWrite(In4,1);
}

void forward(){
  analogWrite(EnA,hiz);
  digitalWrite(In1,0);
  digitalWrite(In2,1);
  analogWrite(EnB,hiz);
  digitalWrite(In3,1);
  digitalWrite(In4,0);
}

void right(){
  analogWrite(EnA,hiz);
  digitalWrite(In1,0);
  digitalWrite(In2,1);
  analogWrite(EnB,hiz);
  digitalWrite(In3,0);
  digitalWrite(In4,1);
}

void left(){
  analogWrite(EnA,hiz);
  digitalWrite(In1,1);
  digitalWrite(In2,0);
  analogWrite(EnB,hiz);
  digitalWrite(In3,1);
  digitalWrite(In4,0);
}
