#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "SUPERONLINE_Wi-Fi_2PK4";
const char* password = "ZCU5bzKC9RUf";

WiFiUDP udp;
unsigned int localUdpPort = 12345;
char incomingPacket[255];

int In1 = D1 ;
int In2 =D2 ;
int EnA =D0 ;
int In3 =D3 ;
int In4 =D4 ;
int EnB =D5 ;

int hiz = 150;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print(WiFi.localIP());
  
  udp.begin(localUdpPort);
  Serial.printf("Listening on UDP port %d\n", localUdpPort);

//motor settings
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = '\0';
    }
    Serial.printf("Received: %s\n", incomingPacket);
    
    // Parse data example
    //axis0 : volant , axis1 iere geri
    float axis0 = 0.0, axis1 = 0.0;
    int button0 = 0;
    sscanf(incomingPacket, "A0:%f,A1:%f,B0:%d", &axis0, &axis1, &button0);
    
    // Use axis/button values to control robot
    Serial.printf("Axis0: %.2f, Axis1: %.2f, Button0: %d\n", axis0, axis1, button0);
    
    // Add motor control or action based on axis/button values here

    if(axis0 > 0.2){
      left();
    }
    else if(axis0 < -0.2){
      right(); 
    }
    else if(axis1 > 0.2){
      back();
    }
    else if(axis1 < -0.2){
      forward();
    }
    else{
      stoped();
    }
  }
}


//motor function

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
