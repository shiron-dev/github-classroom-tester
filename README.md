# github-classroom-tester

github-classroom-tester は GithubClassroom の Autograding をローカル環境でテストできるツールです。あくまで、テストケースの入出力に従ってローカル環境でテストをするだけで、Github 上での結果と必ず一致するわけではありません。

現在 Windows 上での実行のみ対応しています。

## 実行方法

### セットアップ

Releases にある実行ファイルをダウンロードしていただくか、ソースコードをコンパイルしていただき、実行ファイルをテストしたいリポジトリに配置するか、環境変数を実行ファイルに通してください。

### 実行

テストをする際には次のコマンドをコマンドラインから入力してください。

```sh
 gc-tester.exe
```

## 開発環境について

現在、Microsoft Windows のみでコンパイル及び実行ができます。

### リント

[cpplint](https://github.com/cpplint/cpplint)を利用しています。

#### 導入方法

導入には Python が必要です。

```sh
pip install cpplint
```

#### 実行方法

```sh
cpplint --filter=-legal --recursive src/
```

### コンパイル

[CMake](https://cmake.org/)を使ってコンパイルします。実行ファイルは`build/Debug/`に生成されます。

#### Configure

```sh
cmake . -B build
```

#### Generate

```sh
cmake --build build
```

### バッチファイルについて

Windows 環境ではバッチファイルにより、一つのコマンドで`cpplint`から`cmake`まで可能です。

```sh
.\lint-cmake.bat
```

#### オプション

- Configure しない

  ```sh
  .\lint-cmake.bat --no-conf
  ```

- Generate のメッセージを出力させない

  ```sh
  .\lint-cmake.bat --no-msg
  ```

## 使用ライセンス
The project contains the nlohmann/json from Niels Lohmann which is licensed under the MIT License. Copyright © 2013-2022 Niels Lohmann

The project contains the UTF-8 Decoder from Bjoern Hoehrmann which is licensed under the MIT License. Copyright © 2008-2009 Björn Hoehrmann bjoern@hoehrmann.de

The project contains a slightly modified version of the Grisu2 algorithm from Florian Loitsch which is licensed under the MIT License. Copyright © 2009 Florian Loitsch

The project contains a copy of Hedley from Evan Nemerson which is licensed as CC0-1.0.

The project contains parts of Google Abseil which is licensed under the Apache 2.0 License.
