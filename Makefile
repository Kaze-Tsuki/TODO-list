# 編譯器與選項
CXX = g++
CXXFLAGS = -Wall -g -std=c++17
BUILD_DIR = build
TARGET = task.exe  # 可執行檔放在根目錄

# 搜尋所有 .cpp 檔案
SRCS = main.cpp $(wildcard dependency/*.cpp)
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# 預設目標：編譯可執行檔
all: $(TARGET)

# 生成可執行檔
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 生成 .o 檔案，確保 build/ 目錄存在
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)  # <- 確保整個目錄結構存在
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清除編譯產物
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
