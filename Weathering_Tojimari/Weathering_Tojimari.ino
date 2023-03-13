#include <Arduino.h>
#include "M5StickCPlus.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> 
char str[100];
/*
When this code write to M5Stick, remove GND pin from M5Stick.
Then Err won't occurred
*/
//LED of M5StickC voltage is opposite to M5Stack
const char* ssid     = "";//<-- WiFi SSID
const char* password = "";//<-- WiFi password
const char* host     = "notify-api.line.me";
const char* token    = "";//<-- LineNotify Token
const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=tokyo,jp&APPID=";
const String key = "";//<-- openwhether api token
int weathertime;
int weatherflag=0;

#define LED_PIN 10
#define DOOR_PIN 26
#define KEY_PIN 0
#define KEY_TIME 30    //seconds
#define weatherapi 30 //minutes


boolean line_notify(String msg) {
  WiFiClientSecure client;
  client.setInsecure();
  if(!client.connect(host, 443)) {
    Serial.println("connect error!");
    return false;
  }
  String query = String("message=") + msg;
  String request = String("")
              + "POST /api/notify HTTP/1.1\r\n"
              + "Host: " + host + "\r\n"
              + "Authorization: Bearer " + token + "\r\n"
              + "Content-Length: " + String(query.length()) +  "\r\n"
              + "Content-Type: application/x-www-form-urlencoded\r\n\r\n"
              + query + "\r\n";
  client.print(request);
  return true;
}

void weatherget(){
    HTTPClient http;
 
    http.begin(endpoint + key); //URLを指定
    int httpCode = http.GET();  //GETリクエストを送信
 
    if (httpCode > 0) { //返答がある場合
 
        String payload = http.getString();  //返答（JSON形式）を取得
        M5.Lcd.println(httpCode);
        M5.Lcd.println(payload);

        //jsonオブジェクトの作成
        DynamicJsonBuffer jsonBuffer;
        String json = payload;
        JsonObject& weatherdata = jsonBuffer.parseObject(json);

        //パースが成功したかどうかを確認
        if(!weatherdata.success()){
          //M5.Lcd.println("parseObject() failed");
        }

        //各データを抜き出し
        const char* weather = weatherdata["weather"][0]["main"].as<char*>();
        const double temp = weatherdata["main"]["temp"].as<double>();
        /*
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(10,10);
        M5.Lcd.print("weather:");
        M5.Lcd.println(weather);
        M5.Lcd.print("temperature:");
        M5.Lcd.println(temp-273.15);
        */
        if(weather=="shower rain"||weather=="rain"||weather=="thunderstorm"||weather=="snow"){
            weatherflag=1;
        }else{
            weatherflag=0;
        }
    }
    //For Debug
    //weatherflag=1;
}
void unotice(){
    delay(900);
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(10,10);
    M5.Lcd.printf("Umbrella!");
    digitalWrite(LED_PIN, HIGH);
    M5.Beep.beep();
    delay(300);
    digitalWrite(LED_PIN, LOW);
    M5.Beep.mute();
    delay(300);
    digitalWrite(LED_PIN, HIGH);
    M5.Beep.beep();
    delay(300);
    digitalWrite(LED_PIN, LOW);
    M5.Beep.mute();
    delay(300);
}

void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);
    pinMode(DOOR_PIN, INPUT_PULLUP);
    pinMode(KEY_PIN, INPUT_PULLUP);
    pinMode(LED_PIN,OUTPUT);
    M5.Lcd.fillScreen(BLACK);
    //wifi
    M5.Lcd.printf("WIFI START:%s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.print(".");
    }
    M5.Lcd.println(" - READY");
    //weather
    weatherget();
    weathertime=millis();
}
int unflag=0;

void loop(){
    M5.update();
    if(digitalRead(KEY_PIN)==1){
        digitalWrite(LED_PIN, LOW);
        M5.Lcd.fillScreen(GREEN);
        M5.Lcd.setCursor(10,10);
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setTextSize(5);
        M5.Lcd.print("Unlock");
        //weather
        if(weatherflag==1&&unflag==0){
            unotice();
            unflag=1;
            unotice();
        }
    }else{
        digitalWrite(LED_PIN, HIGH);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(10,10);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setTextSize(5);
        M5.Lcd.print("Locked");
        unflag=0;

    }
    //display Umbrella in key status page
    if(weatherflag==1){
        M5.Lcd.setCursor(10,50);
        M5.Lcd.setTextSize(4);
        M5.Lcd.setTextColor(BLUE);
        M5.Lcd.print("Umbrella");
    }else{
        M5.Lcd.setCursor(10,50);
        M5.Lcd.setTextSize(3);
        M5.Lcd.print("Good Weather");
    }
    if(digitalRead(DOOR_PIN)==1){
        M5.Lcd.fillScreen(BLUE);
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setTextSize(5);
        M5.Lcd.setCursor(10,10);
        M5.Lcd.printf("Open");
        //weather
        if(weatherflag==1){
            unotice();
            unotice();
        }
        while(1){
            if(digitalRead(DOOR_PIN)==0){
                /*
                M5.Lcd.fillScreen(GREEN);
                M5.Lcd.setCursor(10,10);
                M5.Lcd.setTextColor(BLACK);
                M5.Lcd.setTextSize(5);
                M5.Lcd.print("Closed");
                */
                break;
            }
        }
        int seccount=0;
        while(seccount<KEY_TIME){
            if(digitalRead(KEY_PIN)==0){
                digitalWrite(LED_PIN, HIGH);
                M5.Lcd.fillRect(0,0,320,120,BLACK);
                M5.Lcd.setCursor(10,10);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(5);
                M5.Lcd.print("Locked");
                break;
            }
            delay(1000);
            seccount++;
        }
        if(digitalRead(KEY_PIN)==1){
            M5.Lcd.fillScreen(RED);
            M5.Lcd.setTextColor(BLACK);
            M5.Lcd.setTextSize(5);
            M5.Lcd.setCursor(10,10);
            M5.Lcd.printf("Unlock!!!");
            //line api
            String msg = "戸締まり忘れ検知!";
            line_notify(msg);
            while(1){
                digitalWrite(LED_PIN, HIGH);
                M5.Beep.beep();
                delay(500);
                digitalWrite(LED_PIN, LOW);
                M5.Beep.mute();
                delay(500);
                if(digitalRead(KEY_PIN)==0){
                    break;
                }
            }
        }
    }
    //weather
    if(weatherapi<(millis()-weathertime)/(60*1000)){
        weatherget();
        weathertime=millis();
    }
    delay(1000);
}