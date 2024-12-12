#include "header.h"

void setup() {
  Serial.begin(115200);
  splashScreenOled();
  sht20.begin();
  ldr.begin();

  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinPompaRelay, OUTPUT);

  clientMQTT.connect_to_AP(ssid, password);
  clientMQTT.init_to_broker(mqttServer, mqttPort);
  clientMQTT.connect_to_broker(myClientID, MQTTUser, MQTTPass);
}

void loop() {
  temperature = sht20.readTemperature();
  humidity = sht20.readHumidity();
  intensitas = ldr.readIntensitas();
  nilaiWaterSensor = analogRead(pinWaterSensor);
  nilaiSoilMoisture = analogRead(pinSoilMoisture);

  bool buzzerNyala = false; 
  if (nilaiWaterSensor > 300) {
    digitalWrite(pinLED, HIGH);
    digitalWrite(pinBuzzer, HIGH);
    clientMQTT.mqtt_publish(Topic_8, "LED Menyala");
    clientMQTT.mqtt_publish(Topic_9, "Buzzer Menyala");
    buzzerNyala = true; 
    //delay(1000);
    //digitalWrite(pinLED, LOW);
    //digitalWrite(pinBuzzer, LOW);
    clientMQTT.mqtt_publish(Topic_8, "LED Mati");
    clientMQTT.mqtt_publish(Topic_9, "Buzzer Mati");
    buzzerNyala = false; 
    delay(1000); 
  } else {
    digitalWrite(pinBuzzer, LOW); 
    digitalWrite(pinLED, LOW);   
    clientMQTT.mqtt_publish(Topic_8, "LED Mati");
    clientMQTT.mqtt_publish(Topic_9, "Buzzer Mati");
    buzzerNyala = false;
  }

  bool pompaNyala = false; 
  if (nilaiSoilMoisture > 3000) {
    digitalWrite(pinPompaRelay, HIGH); 
    clientMQTT.mqtt_publish(Topic_7, "Relay Menyala"); 
    pompaNyala = true;
  } else {
    digitalWrite(pinPompaRelay, LOW);
    clientMQTT.mqtt_publish(Topic_7, "Relay Mati");
    pompaNyala = false;
  }

  doc["temp"] = temperature;
  doc["hum"] = humidity;
  doc["inten"] = intensitas;
  doc["water"] = nilaiWaterSensor;
  doc["soil"] = nilaiSoilMoisture;
  doc["pompa"] = pompaNyala ? "ON" : "OFF"; 
  doc["buzzer"] = buzzerNyala ? "ON" : "OFF";

  jsonPayload = "";  
  serializeJson(doc, jsonPayload); 

  clientMQTT.mqtt_publish(Topic_4, String(jsonPayload)); 
  clientMQTT.mqtt_publish(Topic_5, String(nilaiWaterSensor));
  clientMQTT.mqtt_publish(Topic_6, String(nilaiSoilMoisture));

  display.clearDisplay();
  displaySensorReadings(temperature, humidity, nilaiSoilMoisture, nilaiWaterSensor, intensitas);
  delay(1000);

  display.clearDisplay();
  displayStatus(pompaNyala, buzzerNyala); 
  delay(1000);
}