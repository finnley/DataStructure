//
// Created by finnley on 2022/1/25.
//

#ifndef STATUS_H
#define STATUS_H

#include "stdio.h"

/**
 * 函数结果状态码
 */
#define TRUE    1       // 真/是
#define FALSE   0       // 假/否
#define OK      1       // 通过/成功
#define ERROR   0       // 错误/失败
#define	INFEASIBLE	-1	//不可行

// 系统中已有此状态码定义，要防止冲突（这个我不明白作用是做什么的）
#ifndef OVERFLOW
#define OVERFLOW    -2  // 堆栈上溢
#endif

// typedef 作用：基于一个类型的别名
// Status 是函数的类型，其值是函数结果状态码
typedef int Status;

// 定义新类型 布尔类型
typedef int Boolean;

// 设置全局变量
// 是否开启 debug 模式
extern Boolean debug;

/*
 * 摁下回车键以继续运行。
 *
 * 通常在测试阶段时，需要让每一步测试都暂停下来，以观察其输出，此时可以让debug=TRUE。
 * 在发布时，可以让debug=FALSE，此时各个测试块将不会暂停。
 */
void PressEnterToContinue(Boolean debug);

#endif //STATUS_H
