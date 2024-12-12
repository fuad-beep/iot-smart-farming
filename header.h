#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Edspert_sht20.h>
#include <LDR.h>
#include <EdspertPubSub.h>
#include <ArduinoJson.h>

//========= JSON Declaration ================//
StaticJsonDocument<200> doc;
String jsonString,jsonPayload;

//========= Connection Declaration ================//
// Wifi Setting
char* ssid = "OPPO Naon What"; 
char* password = "fu123456"; 

// MQTT Setting
char *mqttServer = "192.168.1.220";  
int mqttPort = 1883;
String myClientID = "mqtt_MZF"; 
String Topic_1 = "edspert/data/temp";
String Topic_2 = "edspert/data/hum";
String Topic_3 = "edspert/data/intensitas";
String Topic_4 = "edspert/data/data";
String Topic_5 = "edspert/data/water";
String Topic_6 = "edspert/data/soil";
String Topic_7 = "edspert/data/relay"; 
String Topic_8 = "edspert/data/led";
String Topic_9 = "edspert/data/buzzer";

extern String callBackPayload; 
extern String callBackTopic;   

EdspertPubSub clientMQTT;
String MQTTUser = "ff01"; 
String MQTTPass = "ff01"; 

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//========= SHT Declaration ================//
HardwareSerial serial(1); 
Edspert_sht20 sht20(&serial, 9600, 16, 17); 

//========= LDR Declaration ================//
#define pinLDR 33
LDR ldr(pinLDR);

//=========  Pin untuk sensor, buzzer, dan LED ================//
#define pinWaterSensor 34
#define pinSoilMoisture 35
#define pinBuzzer 15
#define pinLED 2
#define pinPompaRelay 13 

float temperature, humidity, intensitas;
int nilaiWaterSensor, nilaiSoilMoisture;