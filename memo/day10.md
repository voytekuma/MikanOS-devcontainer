## ポーリングでマウス入力
- xHCを検索
    - ベースクラス0x0cはシリアルバスコントローラ
    - サブクラス0x03はUSBコントローラ
    - インターフェース0x30はxHCI
- MMIO
    - メモリアドレス空間にあるレジスタ
    - メモリアドレスが付与されているのでアドレスでアクセスできる
    - PCIコンフィギュレーション空間のBase Address Register0にMMIOのアドレスが記録されている
    - Bar0の値を使ってxHC（ホストコントローラ）を初期化

- マウスの検索
    - xHCを使ってすべてのポートの中から何かが接続されているポートを見つける
    - それがUSBマウスだった場合、マウスからのデータを受信する関数を登録しておく

- マウスの移動
    - マウスイベントはxHCに溜まっていくので、whileで繰り返し処理する
    - 処理すべきイベントが溜まっていた場合は、登録した関数が実行される
    - このようにイベントの有無を能動的に調べる方法をポーリングと呼ぶ
    - もちろんマウスイベントの取得には適していないので後で割り込み方式へ変更する

- ログ関数
    - print系関数にログレベルという値を追加
    - SetLogLevel()で設定した閾値と比較され、閾値以上ならば表示する

- ~static_cast<uint64_t>(0xf)
    - 下位4ビットが0である64ビット整数
    - 他の64ビット整数と&をとることで下位4ビットを0にマスクすることができる
    - 0xfは1111なので反転させることで下位4ビットが0になる
    - だがコンパイラは0xfを32ビットとして解釈してしまうので、そのままでと64ビット整数に対するマスクにならない
    - なので明示的にuint64_tへキャストしている
