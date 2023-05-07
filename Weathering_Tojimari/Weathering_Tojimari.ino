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

#define LED_PIN 10
#define DOOR_PIN 26
#define KEY_PIN 0
#define KEY_TIME 20    //seconds
#define weatherapi 30 //minutes

//regular weather notice time
#define seth 7 //hour
#define setm 0 //min
#define ntptime 5//min

//define global scope
//weather.ino
int weathertime;
int weatherflag=0;
//ntp.ino
int forecast=0;
char timenow[30];
int nowy,nowmon,nowd,nowh,nowm,nows,reg;
int systime=millis()/1000;

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
    ntpsetup();
}

//unflag is to notify "Umbrella" only once in the loop
int unflag=0;

void loop(){
    M5.update();
    if(digitalRead(KEY_PIN)==1){
        print_unlock();
        //weather
        if(weatherflag==1&&unflag==0){
            unotice();
            unotice();
            unflag=1;
        }
    }else{
        print_locked();
        unflag=0;
    }
    if(digitalRead(DOOR_PIN)==1){
        //weather
        if(weatherflag==1){
            unotice();
            unotice();
        }
        while(1){
            print_open();
            if(digitalRead(DOOR_PIN)==0){
                break;
            }
            delay(1000);
        }
        int seccount=0;
        while(seccount<KEY_TIME){
            print_unlock();
            if(digitalRead(KEY_PIN)==0){
                print_locked();
                break;
            }
            delay(1000);
            seccount++;
        }
        if(digitalRead(KEY_PIN)==1){
            print_unlock_notice();
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
    //weather reget
    if(weatherapi<(millis()-weathertime)/(60*1000)){
        weatherget();
        weathertime=millis();
    }
    delay(1000);
}