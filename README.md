# github-classroom-tester

## 開発環境について

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
