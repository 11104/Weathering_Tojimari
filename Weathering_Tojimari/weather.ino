void weatherget(){
    HTTPClient http;
 
    http.begin(endpoint + key); //URLを指定
    int httpCode = http.GET();  //GETリクエストを送信
 
    if (httpCode > 0) { //返答がある場合
 
        String payload = http.getString();  //返答（JSON形式）を取得
        //M5.Lcd.println(httpCode);
        //M5.Lcd.println(payload);

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
        //Co=temp-273.15
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
    delay(1000);
}