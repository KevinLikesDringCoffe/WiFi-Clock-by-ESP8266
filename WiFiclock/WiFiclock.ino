// a program to grab the time online
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include "OLEDDisplayFonts.h"

const char* ssid = "TP-LINK_6B7F";
const char* password = " ";
const char* url = "http://quan.suning.com/getSysTime.do";


WiFiClient client;
HTTPClient httpclient;
SSD1306Wire display(0x3c, SDA, SCL);

void setup() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  
  WiFi.mode(WIFI_STA);
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  
  Serial.println(ssid);
  display.drawString(64,20,"Connecting to");
  display.drawString(64,30,ssid);
  display.display();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
    
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println(WiFi.RSSI());
  display.drawString(64,50,"WiFi connected");
  display.display();
  delay(1000);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //client.setTimeout(HTTP_TIMEOUT);
}

void loop() {
  display.clear();
  if(WiFi.status() == WL_CONNECTED){
    Serial.println(WiFi.RSSI());
    WiFiStrengthToIcon(WiFi.RSSI());
    httpclient.begin(url);
    int httpcode = httpclient.GET();
    if(httpcode == HTTP_CODE_OK){
      String responsePayload = httpclient.getString();
      Serial.println(responsePayload);
      StaticJsonBuffer<200> jsonbuffer;
      JsonObject& root = jsonbuffer.parseObject(responsePayload);
      String onlinetime = root["sysTime2"];
      String date = onlinetime.substring(0,onlinetime.indexOf(" "));
      String time = onlinetime.substring(onlinetime.indexOf(" ") + 1,onlinetime.length());
      Serial.println(date);
      Serial.println(time);
      display.setFont(ArialMT_Plain_10);
      display.drawString(64, 20, date);
      
      display.setFont(ArialMT_Plain_24);
      display.drawString(64, 30, time);
    }
    else{
      Serial.println(httpcode);  
    }
  }
  else{
    Serial.println("WiFi disconnected");
    display.drawString(64,30,"WiFi disconnected!");
  }
  delay(100);
  display.display();
}

void WiFiStrengthToIcon(int rssi){
    if(rssi > -90 ){
       display.fillRect(5, 13, 3, 2);  
    }
    if(rssi > -80){
      display.fillRect(10, 10, 3, 5);  
    }
    if(rssi > -70){
      display.fillRect(15, 7, 3, 8);
    }
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 5, ssid);
    
}
