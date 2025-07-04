# 컴파일러와 옵션
CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -O2

# 디렉토리
SRC_DIR := .
OBJ_DIR := obj
BIN_DIR := bin

# 소스 및 오브젝트 파일
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 실행 파일
TARGET := $(BIN_DIR)/app.exe

# DirectX + WinAPI 관련 링커 옵션
LDLIBS := -ld3d11 -ldxgi -ld3dcompiler -ldinput8 -ldxguid -lwindowscodecs -lgdi32 -lole32 -luuid -luser32 -lkernel32

# 기본 타겟
all: $(TARGET)

# 링크
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# 개별 cpp → obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# obj, bin 디렉토리 생성
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# 강제 재컴파일
rebuild: clean all

# force 빌드 (모든 cpp 강제 컴파일)
force: FORCE $(OBJS) $(TARGET)
FORCE:

# 정리
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean rebuild force