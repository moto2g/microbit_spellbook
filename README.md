# microbit_spellbook
motion detector with Micro:bit using neural network libraries

# predict
モーションを検知し、無線通信を送信するためのプログラムです。
これに加えて、Neural Network Librariesから出力した学習済みモデルのソースが必要です。

# receiver
無線通信を受け取り、音声を再生するためのプログラムです。

# collector(参考)
AIに学習させるための加速度データを収集するためのプログラムです。
シリアル通信で出力される内容を保存して使います。

# ビルド方法
predict、collectorはC言語で書かれたソースのため、オフラインコンパイル環境でビルドします。
環境構築方法は[こちら](https://qiita.com/moto2g/items/703b10d4aff1fd1e1f23)を参考にしてみてください。
predictはバイナリファイルもおいています。

receiverはMicroPythonで書かれたソースのため、Muでビルドします。
