#include <iostream>
#include <string>
#include <sstream>
#include "DataCollect.h"

// 解析错误码的函数
std::string parseErrorCode(int errorCode) {
    if (errorCode == 0) return "采集成功";
    
    std::ostringstream oss;
    oss << "采集失败，错误码: " << errorCode << "\n详细错误信息:\n";

    if (errorCode & (0x01 << 0)) oss << "  - 终端类型未采集到\n";
    if (errorCode & (0x01 << 1)) oss << "  - 信息采集时间获取异常\n";
    if (errorCode & (0x01 << 2)) oss << "  - IP获取失败\n";
    if (errorCode & (0x01 << 3)) oss << "  - MAC获取失败\n";
    if (errorCode & (0x01 << 4)) oss << "  - 设备名获取失败\n";
    if (errorCode & (0x01 << 5)) oss << "  - 操作系统版本获取失败\n";
    if (errorCode & (0x01 << 6)) oss << "  - 硬盘序列号获取失败\n";
    if (errorCode & (0x01 << 7)) oss << "  - CPU序列号获取失败\n";
    if (errorCode & (0x01 << 8)) oss << "  - BIOS获取失败\n";

    return oss.str();
}

int main() {
    // 获取版本信息
    const char* version = CTP_GetDataCollectApiVersion();
    std::cout << "数据采集API版本: " << (version ? version : "未知") << std::endl;

    // 准备缓冲区 - 至少270字节，建议更大以确保安全
    char buffer[2048] = {0};
    int len = sizeof(buffer) - 1;

    // 调用采集函数
    int result = CTP_GetSystemInfo(buffer, len);

    if (result == 0) {
        std::cout << "系统信息采集成功!" << std::endl;
        std::cout << "采集到的数据长度: " << len << " 字节" << std::endl;
        std::cout << "系统信息: " << std::string(buffer, len) << std::endl;
    } else {
        std::cout << "系统信息采集失败!" << std::endl;
        std::cout << parseErrorCode(result) << std::endl;
    }

    return 0;
}