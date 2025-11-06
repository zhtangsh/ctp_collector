#include <iostream>
#include <string>
#include <sstream>
#include "DataCollect.h"
#include "base64.h"

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
        std::cout << "原始数据长度: " << len << " 字节" << std::endl;
        
        // 将原始数据进行Base64编码
        std::string raw_data(buffer, len);
        std::string encoded_data = base64_encode(reinterpret_cast<const unsigned char*>(raw_data.c_str()), raw_data.length());
        
        std::cout << "Base64编码后的数据:" << std::endl;
        std::cout << encoded_data << std::endl;
        
        // 如果需要，也可以解码验证
        // std::string decoded_data = base64_decode(encoded_data);
        // std::cout << "解码后长度: " << decoded_data.length() << " 字节" << std::endl;
    } else {
        std::cout << "系统信息采集失败!" << std::endl;
        std::cout << parseErrorCode(result) << std::endl;
    }

    return 0;
}