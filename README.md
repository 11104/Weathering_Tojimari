# 天気の戸締まり Weathering_Tojimari v1.0
"[自宅警備員](https://github.com/11104/homeguard)"に機能を追加したものです。
ドアの鍵を閉め忘れたらLINEで通知します。
また、ドアを開けた際、天気予報が雨だった場合に、ブザーでお知らせします。

## What you need
- M5StickC Plus
- 磁気ドアスイッチx2
- [LineNotify](https://notify-bot.line.me/ja/)のToken
- [OpenWeatherApi](https://openweathermap.org)のToken

## How to use
12~17行目にWifi情報と各種Tokenを入力してM5StickCに書き込んでください。
ドア通知の猶予時間は30秒、天気予報の取得は30分がデフォルトになっています。

解説記事-->"[天気予報が雨の時、傘を持つように促す装置を作った](https://qiita.com/nih/items/5b122e9b43f3f10e7acf)"

## Version History
- v1.0 - 23/3/13 release