#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define BLYNK_PRINT Serial

#ifndef STASSID
#define STASSID "TP-Link_328C"
#define STAPSK  "72196663"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

char auth[] = "ix7srTNNI9DgkqYq2rIz4cvSCwC5fUEF";

int state;

void sensor();

BLYNK_CONNECTED(){
  Blynk.syncVirtual(V1);
}

BLYNK_WRITE(V1)
{
  state = param.asInt();
  digitalWrite(12,state);   
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(14,INPUT_PULLUP);
  pinMode(12,OUTPUT);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.encryptionType(2);
  
  //WiFi.softAP(ssid,password,1);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  

  Blynk.config(auth);

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  sensor();

}

void sensor()
{
   if(digitalRead(14)==LOW)
  {
    if(state==1)
    {
      state=0;
      digitalWrite(12,LOW);
      Blynk.virtualWrite(V1,state);
      Blynk.setProperty(V1,"offlabel","OFF");
    }
  }
}
