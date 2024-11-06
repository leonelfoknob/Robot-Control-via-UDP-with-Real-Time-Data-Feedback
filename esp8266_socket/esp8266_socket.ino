#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "SUPERONLINE_Wi-Fi_2PK4";
const char* password = "ZCU5bzKC9RUf";

WiFiUDP udp;
unsigned int localUdpPort = 12345;  // Match the port with the Python script
char incomingPacket[255];
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize built-in LED
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.println(WiFi.localIP());

  // Start listening on UDP
  udp.begin(localUdpPort);
  Serial.printf("Listening on UDP port %d\n", localUdpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Receive incoming UDP packet
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null-terminate the string
    }
    
    Serial.printf("Received packet: %s\n", incomingPacket);
    
    // Check for "TOGGLE" command
    if (strcmp(incomingPacket, "TOGGLE") == 0) {
      ledState = !ledState;                   // Toggle LED state
      digitalWrite(LED_BUILTIN, ledState);     // Turn on/off LED
      Serial.println("LED state toggled");
    }
  }
  delay(500);
}
