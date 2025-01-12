#include <WiFi.h>
#define BLYNK_PRINT Serial

// Define from Blynk
#define BLYNK_TEMPLATE_ID "TMPL6DJg4bSfC"
#define BLYNK_TEMPLATE_NAME "ESP32 PROJECT"
#define BLYNK_AUTH_TOKEN "sVRn--qn7YlZxfYun8SKLJBQfuGdW_vL"

#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN; // Auth Token from Blynk
char ssid[] = "_guyae";         // WiFi SSD
char pass[] = "guyapisit";      // WiFi password

// Define pin for each equipment
int in1 = 33; 
int in2 = 25; 
int in3 = 26; 
int in4 = 27;
int pump = 14;
int pumpStatus = 0;

// Define initial value
int direction1 = 0;
int direction2 = 2;
int direction3 = 4;
int direction4 = 6;

void setup() {
  // Define pin mode
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);
  pinMode(pump, OUTPUT);
  
  Serial.begin(9600);  // Start Serial Monitor
  Blynk.begin(auth, ssid, pass);  // connect to Blynk

  // Check that wifi connect yet
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Check that blynk connect yet
  while (!Blynk.connected()) {
    delay(1000);
    Serial.println("Connecting to Blynk...");
  }
  Serial.println("Connected to Blynk");
}

// Definr function for control direction
void Forward() 
  { 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,LOW); 
  } 
void Backward() 
  { 
  digitalWrite(in1,LOW); 
  digitalWrite(in2,HIGH); 
  digitalWrite(in3,LOW); 
  digitalWrite(in4,HIGH); 
  } 
void Stop() 
  { 
  digitalWrite(in1,LOW); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,LOW); 
  digitalWrite(in4,LOW); 
  } 
void Right() 
  { 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,LOW); 
  digitalWrite(in4,LOW); 
  } 
void Left() 
  { 
  digitalWrite(in1,LOW); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,LOW); 
  }

void loop() {
  Blynk.run();  // Start Blynk
}

BLYNK_WRITE(V0) {
  direction1 = param.asInt(); // Get value from Blynk
  Serial.println(direction1); // Display value on serial monitor
  
  // If direction1 == 1 it will go forward
  if (direction1 == 1)
    Forward();
  // If false then stopped it
  else if (direction1 == 0)
    Stop();
}  

BLYNK_WRITE(V1) {
  direction2 = param.asInt(); // Get value from Blynk
  Serial.println(direction2); // Display value on serial monitor

  // If direction1 == 3 it will go backward
  if (direction2 == 3)
    Backward();
  // If false then stopped it
  else if (direction2 == 2)
    Stop();
}

BLYNK_WRITE(V2) {
  direction3 = param.asInt(); // Get value from Blynk
  Serial.println(direction3); // Display value on serial monitor

  // If direction1 == 5 it will go backward
  if (direction3 == 5)
    Right();
  // If false then stopped it
  else if (direction3 == 4)
    Stop();
}

BLYNK_WRITE(V3) {
  direction4 = param.asInt(); // Get value from Blynk
  Serial.println(direction4); // Display value on serial monitor

  // If direction1 == 7 it will go backward
  if (direction4 == 7)
    Left();
  // If false then stopped it
  else if (direction4 == 6)
    Stop();
}

BLYNK_WRITE(V4) {
  pumpStatus = param.asInt(); // Get value from Blynk
  Serial.println(pumpStatus); // Display value on serial monitor

  // If pumpStatus it will shoou water out
  if (pumpStatus) {
      digitalWrite(pump, 1);
  // If false then stopped it
  } else {
      digitalWrite(pump, 0);
      
  }
}
