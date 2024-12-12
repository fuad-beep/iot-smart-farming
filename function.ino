//================  OLED LCD ==========//
void splashScreenOled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25, 20);
  display.println("EDSPERT");
  display.setCursor(20, 35);
  display.println("BOOTCAMP");

  display.display();
  delay(5000);
  display.clearDisplay();
}

void displaySensorReadings(float a, float b, int c, int d, float e) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.print("Temp: ");
  display.print(a);
  display.println(" C");

  display.setCursor(10, 20);
  display.print("Hum : ");
  display.print(b);
  display.println(" %");

  display.setCursor(10, 30);
  display.print("Soil : ");
  display.println(c);

  display.setCursor(10, 40);
  display.print("Water: ");
  display.println(d);

  display.setCursor(10, 50);
  display.print("Inte: ");
  display.print(e);
  display.println(" Lux");

  display.display();
  delay(2000);
}

void displayStatus(bool pompaStatus, bool buzzerStatus) { 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 15);
  display.print("Pompa: ");
  display.println(pompaStatus ? "ON" : "OFF");

  display.setCursor(10, 30);
  display.print("Buzzer: ");
  display.println(buzzerStatus ? "ON" : "OFF"); 

  display.display();
}