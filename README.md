## 天気の戸締まり Weathering_Tojimari v1.1.1
"[自宅警備員](https://github.com/11104/homeguard)"に機能を追加したものです。
ドアの鍵を閉め忘れたらLINEで通知します。
また、ドアを開けた際、天気予報が雨だった場合に、ブザーでお知らせします。

# What you need
- M5StickC Plus
- 磁気ドアスイッチx2
- [LineNotify](https://notify-bot.line.me/ja/)のToken
- [OpenWeatherApi](https://openweathermap.org)のToken

# How to use
12~17行目にWifi情報と各種Tokenを入力してM5StickCに書き込んでください。
書き込む際は"[Weathering_Tojimari.ino](https://github.com/11104/Weathering_Tojimari/blob/main/Weathering_Tojimari/Weathering_Tojimari.ino)"を指定してください。(他のファイルはコンパイル時に自動的にマージされます。)
ドア通知の猶予時間は20秒、天気予報の取得は30分がデフォルトになっています。

# Movie
[動作例](https://youtu.be/q4lDglBBaFI)

"[天気予報が雨の時、傘を持つように促す装置を作った](https://qiita.com/nih/items/5b122e9b43f3f10e7acf)"

# Attention
- M5StickCでは書き込み時にGND接続を外して下さい。
- M5Stickは、M5StackとLEDの電圧設定が逆です。

## Version History
- v1.0.0 - 23/3/13 release
- v1.1.0 - 23/5/4 display time
- v1.1.1 - 23/5/6 fix some bug