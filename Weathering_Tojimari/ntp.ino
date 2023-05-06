void ntpsetup() {
    char* ntpserver = "ntp.nict.jp";
    configTime(9 * 3600, 0, ntpserver);//GMTとの時差(秒) が9*3600, サマータイムで進める時間(秒)が0

    struct tm localTime;
    getLocalTime(&localTime);
    nowy=localTime.tm_year + 1900;
    nowmon=localTime.tm_mon + 1;
    nowd=localTime.tm_mday;
    nowh=localTime.tm_hour;
    nowm=localTime.tm_min;
    nows=localTime.tm_sec;
    //sprintf(timenow, "%04d/%02d/%02d\n  %02d:%02d:%02d",
    sprintf(timenow, "%04d/%02d/%02d\n  %02d:%02d",
        nowy,
        nowmon,
        nowh,
        nowh,
        nowm
        //,nows
    );
}

void timeget(){
    //time change
    if(systime-millis()/1000>=1){
        nows++;
    }
    if(nows>=60){
        nows=0;
        nowm++;
        if(nowm>=60){
        nowh++;
        nowm=0;
        ntpsetup();
        }
        if(nowh>=24){
        ntpsetup();
        systime=millis()/1000;
        }
    }
    //sprintf(timenow, "%04d/%02d/%02d\n  %02d:%02d:%02d",
    sprintf(timenow, "%04d/%02d/%02d\n  %02d:%02d",
        nowy,
        nowmon,
        nowd,
        nowh,
        nowm
        //,nows
    );

    //For weather api
    if(nowm!=setm){
      reg=0;
    }
    //reget ntp
    if(millis()/1000-systime>=ntptime*60){
      ntpsetup();
      systime=millis()/1000;
    }
}