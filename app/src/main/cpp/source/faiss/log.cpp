
#ifndef __ANDROID__
#include "../log.h"


// 定义一个辅助函数来递归处理参数
void log_helper(std::ostream& os) {
    // 递归终止条件，不做任何事
}

template <typename T, typename... Args>
void log_helper(std::ostream& os, const T& value, const Args&... args) {
    os << value << " "; // 打印当前参数
    log_helper(os, args...); // 递归调用以处理剩余参数
}

// 定义一个可变参数的 log 函数
template <typename... Args>
void custom_log(const char* tag, Args... args) {
    std::ostringstream stream;
    stream << tag << ": ";
    log_helper(stream, args...); // 使用辅助函数处理参数
    std::cerr << stream.str() << std::endl; // 输出到 stderr
}


// 显式实例化
template void custom_log(const char* tag, const char* arg1);
template void custom_log(const char* tag, const char* arg1, const char* arg2);
template void custom_log(const char* tag, const char* arg1, const char* arg2, const char* arg3);
template void custom_log<char const*, char const*, long>(char const* tag, char const* arg1, char const* arg2, long arg3);
template void custom_log<char const*, char const*, int>(char const* , char const*, char const*, int);
template void custom_log<char const*, char const*, int, float, float>(char const*, char const*, char const*, int, float, float);
template void custom_log<char const*, char const*, long, float>(char const*, char const*, char const*, long, float);

#endif