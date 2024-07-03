//
// Created by luojinlong on 2020/5/28.
//

#ifndef ANDROID_FAISS_LOG_H
#define ANDROID_FAISS_LOG_H

#ifdef __ANDROID__

#include <android/log.h>

#define TAG "faiss"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)


#else

#define TAG "faiss"
#include <iostream>
#include <sstream>

// 定义一个辅助函数来递归处理参数
void log_helper(std::ostream& os);

template <typename T, typename... Args>
void log_helper(std::ostream& os, const T& value, const Args&... args);

// 定义一个可变参数的 log 函数
template <typename... Args>
void custom_log(const char* tag, Args... args);


#define LOGD(...) custom_log("DEBUG",TAG ,__VA_ARGS__)
#define LOGI(...) custom_log("INFO",TAG ,__VA_ARGS__)
#define LOGE(...) custom_log("ERROR",TAG ,__VA_ARGS__)

#endif

#endif //ANDROID_FAISS_LOG_H