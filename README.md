# まほうのしょ / microbit_spellbook
motion detector with micro:bit using neural network libraries<br>
micro:bitにSony Neural Network Librariesで生成したAIを載せてモーション検出する<br>

## 必要なもの
- micro:bit x 2台
- スピーカー x 1台
- micro:bitとスピーカーをつなぐワニ口クリップ

## predict
## 本側のmicro:bit用モジュール
モーションを検知し、無線通信を送信するためのプログラムです。<br>
Neural Network Librariesから出力した学習済みモデルのソースを使います。<br>
独自に学習させたソースを使用する場合は"predict/cruntime"の中身を入れ替えてください。<br>


### ビルド方法
ビルド済みバイナリファイルは下記においています。<br>
"predict/build/bbc-microbit-classic-gcc/source/predict-combined.hex"<br>
<br>
※micro:bitオフラインコンパイル環境(環境構築方法は文末のリンク参照)でビルドします。<br>
"predict"フォルダで下記コマンドを実行する。<br>
`yt target bbc-microbit-classic-gcc`<br>
`yt build`<br>
生成された"predict/build/bbc-microbit-classic-gcc/source/predict-combined.hex"をmicro:bitにコピーする。<br>
<br>
※初回だけ `yt target bbc-microbit-classic-gcc` の後で<br>
"predict/yotta_modules/microbit-dal/inc\core/MicroBitConfig.h"を編集し、<br>
#define MICROBIT_BLE_ENABLED の値を1から0に変更します。<br>
Bluetoothと無線通信は同時に使えないため、Bluetoothを無効に設定するための変更です。<br>

## receive
## スピーカー側のmicro:bit用モジュール
無線通信を受け取り、音声を再生するためのプログラムです。<br>

### ビルド方法
MicroPythonで書かれたソースです。<br>
[Mu](https://codewith.mu/)を使ってmicro:bitに転送してください。<br>


## collector
## (参考)データ収集に使用するmicro:bit用モジュール
AIに学習させるための加速度データを収集するためのプログラムです。<br>
シリアル通信で出力される内容を保存して使います。<br>
Aボタン、Bボタンを押している間はデータの末尾に識別番号が付きます。<br>

### 収集するデータの調整
現在は80ms間隔で6セットの加速度データを使用しています。<br>
下記の定数を変更することで調整できます。<br>
※変更した場合、predictモジュールも同様に変更してください。<br>
<br>
"main.cpp"<br>
#define INTERVAL_OF_GET に、何ミリ秒間隔でデータを収集するかを指定します。<br>
#define NUM_OF_VALUES に、何個の加速度データを一連のデータとして使用するかを指定します。<br>

### ビルド方法
ビルド済みバイナリファイルは下記においています。<br>
"collector/build/bbc-microbit-classic-gcc/source/collector-combined.hex"
<br>
※micro:bitオフラインコンパイル環境(環境構築方法は文末のリンク参照)でビルドします。<br>
"collector"フォルダで下記コマンドを実行する。<br>
`yt target bbc-microbit-classic-gcc`<br>
`yt build`<br>
生成された"collector/build/bbc-microbit-classic-gcc/source/collect-combined.hex"をmicro:bitにコピーする。<br>

# 関連リンク
Paddle 作品共有サイト<br>
https://paddle.prokids.jp/work/show/296<br>
<br>
YouTube 作品紹介動画<br>
https://www.youtube.com/watch?v=Ggl_MrOXplU&feature=youtu.be<br>
<br>
Qiita micro:bitでNeural Network Librariesを使う方法(オフラインコンパイル環境の構築)<br>
https://qiita.com/moto2g/items/703b10d4aff1fd1e1f23<br>
