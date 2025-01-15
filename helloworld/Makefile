# コンパイラとフラグの設定
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

# ディレクトリの設定
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

# ソースファイルとターゲット
SRCS = $(SRC_DIR)/helloworld1.c $(SRC_DIR)/calc_magicnumber.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)
TARGET = $(BIN_DIR)/helloworld

# デフォルトターゲット
all: $(TARGET)

# 実行バイナリの生成
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET)

# オブジェクトファイルの生成
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/calc_magicnumber.h
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -rf $(SRC_DIR)/*.o $(BIN_DIR)/*