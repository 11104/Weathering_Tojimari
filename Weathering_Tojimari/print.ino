void print_weather(){
    //display Umbrella in key status page
    if(weatherflag==1){
        M5.Lcd.setCursor(10,50);
        M5.Lcd.setTextSize(4);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print("Umbrella");
    }else{
        M5.Lcd.setCursor(10,50);
        M5.Lcd.setTextSize(3);
        if(digitalRead(DOOR_PIN)==1){
            //while open only
            M5.Lcd.setTextColor(BLACK);
        }else{
            M5.Lcd.setTextColor(BLUE);
        }
        M5.Lcd.print("Good Weather");
    }
}

void print_locked(){
    digitalWrite(LED_PIN, HIGH);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10,10);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print("Locked");
    print_weather();
    timeget();
    M5.Lcd.setCursor(10,80);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println(timenow);
}

void print_unlock(){
    digitalWrite(LED_PIN, LOW);
    M5.Lcd.fillScreen(GREEN);
    M5.Lcd.setCursor(10,10);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print("Unlock");
    print_weather();
    timeget();
    M5.Lcd.setCursor(10,80);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println(timenow);
}

void print_open(){
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(10,10);
    M5.Lcd.printf("Open");
    print_weather();
    timeget();
    M5.Lcd.setCursor(10,80);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println(timenow);
}

void print_unlock_notice(){
    M5.Lcd.fillScreen(RED);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(10,10);
    M5.Lcd.printf("Unlock!!!");
}