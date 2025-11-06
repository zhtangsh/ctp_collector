CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -L. -l:LinuxDataCollect.so

# 目标文件
TARGET = data_collector
SRC = main.cpp

$(TARGET): $(SRC) DataCollect.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# 创建符号链接版本
$(TARGET)_symlink:
	ln -sf LinuxDataCollect.so libDataCollect.so
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -L. -lDataCollect

install-libs:
	# 将库文件复制到系统库目录（可选）
	# sudo cp LinuxDataCollect.so /usr/lib/
	# 或者复制到 /usr/local/lib/
	# sudo cp LinuxDataCollect.so /usr/local/lib/
	# sudo ldconfig

clean:
	rm -f $(TARGET) libDataCollect.so

.PHONY: clean install-libs