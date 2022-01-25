//
// Created by finnley on 2022/1/25.
//

#ifndef STATUS_H
#define STATUS_H

#include "stdio.h"

/**
 * 状态码
 */
// 真/是
#define TRUE    1
// 假/否
#define FALSE   0
// 通过/成功
#define OK      1
// 错误/失败
#define ERROR   0

// 系统中已有此状态码定义，要防止冲突（这个我不明白作用是做什么的）
#ifndef OVERFLOW
// 堆栈上溢
#define OVErFLOW    -2
#endif

// 定义新的类型 Status 用户标识方法返回状态等
typedef int Status;

// 定义新类型 布尔类型
typedef int Boolean;

// 设置全局变量
// 是否开启 debug 模式
extern Boolean debug;

#endif //STATUS_H
