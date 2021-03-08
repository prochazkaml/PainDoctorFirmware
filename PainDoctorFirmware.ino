#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Fonts/FreeMonoBold18pt7b.h>

#include "logo.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Adafruit_MPU6050 mpu;

IPAddress apIP(192, 168, 69, 123);
AsyncWebServer server(80);

const char *ssid = "PainDoctor";
const char *password = "WorkoutOrDie";

int setupDone = 0, setupPain = 0, setupTime = 0;

#define hm_to_sec(h, m) ((h * 60 + m) * 60)

int setupTimeSeconds[11] = {
  hm_to_sec(0, 5), hm_to_sec(0, 10), hm_to_sec(0, 15), hm_to_sec(0, 20), hm_to_sec(0, 30),
  hm_to_sec(0, 45), hm_to_sec(1, 0), hm_to_sec(1, 30), hm_to_sec(2, 0), hm_to_sec(4, 0),
  hm_to_sec(100, 0)
};

void printfCentered(int y, char *fmt, ...) {
  char buffer[64];
  va_list argptr;
  va_start(argptr, fmt);
  vsnprintf(buffer, 64, fmt, argptr);
  va_end(argptr);

  display.setCursor(64 - strlen(buffer) * 3, y);
  display.print(buffer);
}

void error(char *str) {
  display.clearDisplay();
  printfCentered(28, str);
  display.display();
  
  while (1) {
    delay(10);
  }
}

void setup() {
  char buffer[64];

  pinMode ( LED_BUILTIN, OUTPUT );
  digitalWrite ( LED_BUILTIN, 1 );

  // Initialize LCD and display splash screen

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.drawBitmap(0, 0, bootlogo, 128, 64, 1);
  display.display();

  // Initialize accelerometer

  if (!mpu.begin()) {
    error("Accelerometer error!");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Initialize filesystem

  if(!SPIFFS.begin()){
    error("SPI FS error!");
  }

  delay(3000);

  // Initialize server
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->args()) {
      char buffer[16];
      snprintf(buffer, 16, "OK%c%c", request->arg("l").charAt(0), request->arg("t").charAt(0));
      
      request->send_P( 200, "text/plain", buffer);
      setupDone = 1;
      setupPain = request->arg("l").charAt(0) - 'A';
      setupTime = request->arg("t").charAt(0) - 'A';
    } else {
      request->send(SPIFFS, "/PainDoctor.apk", "application/octet-stream");     
    }
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send_P(404, "text/plain", "404: File not found");
  });
  
  server.begin();

  // Display connect screen

  display.clearDisplay();
  
  printfCentered(8, "Please connect to");
  printfCentered(16, "the PainDoctor.");
  printfCentered(40, "SSID: %s", ssid);
  printfCentered(48, "Pass: %s", password);

  display.display();

  // Wait for a device to connect

  while(!WiFi.softAPgetStationNum()) { delay(100); }

  display.clearDisplay();
  printfCentered(16, "Please open the");
  printfCentered(24, "PainDoctor Companion");
  printfCentered(32, "app and follow the");
  printfCentered(40, "on-screen prompts.");
  display.display();

  while(!setupDone) delay(100);

  delay(1000);

  WiFi.mode(WIFI_OFF);

  unsigned long oldmillis;

  int i;
  for(i = 9; i >= 0; i--) {
    oldmillis = millis();
    
    display.clearDisplay();
    display.setFont();
    printfCentered(0, "Put down the phone");
    printfCentered(48, "and get ready!");
    display.setFont(&FreeMonoBold18pt7b);
    display.setCursor(0, 38);
    display.printf("00m%02ds", i);
    display.display();
    
    while((oldmillis + 1000) > millis()) delay(100);
  }

  int shocks = 0;

  for(i = setupTimeSeconds[setupTime] - 1; i >= 0; i--) {
    oldmillis = millis();
    
    display.clearDisplay();
    display.setFont();
    printfCentered(0, "Move!");
    printfCentered(48, "Got %d shocks", shocks);
    display.setFont(&FreeMonoBold18pt7b);
    display.setCursor(0, 38);

    if(i < 3600)
      display.printf("%02dm%02ds", i / 60, i % 60);
    else
      display.printf("%02dh%02dm", i / 3600, (i / 60) % 60);
      
    display.display();
    
    while((oldmillis + 1000) > millis()) delay(100);
  }

  display.clearDisplay();
  display.setCursor(0, 31);
  display.print("You're");
  display.setCursor(0, 63);
  display.print("winner");
  display.display();
}

void loop() {
  delay(100);
}
