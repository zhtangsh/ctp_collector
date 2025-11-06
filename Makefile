# 编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -L. -l:LinuxDataCollect.so

# 目标文件名称
TARGET = data_collector
SRCS = main.cpp base64.cpp

# 默认目标
all: $(TARGET)

# 编译目标 - 添加RPATH
$(TARGET): $(SRCS) DataCollect.h base64.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS) -Wl,-rpath,.

# 创建符号链接版本（备选方案）
symlink: 
	ln -sf LinuxDataCollect.so libDataCollect.so
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) -L. -lDataCollect -Wl,-rpath,.

# 清理编译产物
clean:
	rm -f $(TARGET) libDataCollect.so

# 安装库到系统（可选）
install-libs:
	@echo "将库文件复制到系统库目录的示例命令："
	@echo "sudo cp LinuxDataCollect.so /usr/lib/"
	@echo "sudo ldconfig"

# 显示依赖信息
show-deps:
	@echo "检查可执行文件依赖："
	@ldd $(TARGET) || echo "可执行文件 $(TARGET) 不存在，请先编译"

.PHONY: all clean install-libs show-deps symlink