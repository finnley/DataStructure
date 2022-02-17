//
// Created by finnley on 2022/1/25.
//

#include "SqList.h"

/**
 * 初始化
 *
 * 分配预定义长度的内存空间
 * 并将长度设置 0
 *
 * @param L
 * @return
 */
Status InitList(SqList *L) {
    // 思考：
    // 1. 为什么需要初始化线性表？ 初始化就是首先要有一个盛放数据容器，没有容器怎么去存放数据呢？
    // 2. 初始化顺序表需要哪些准备？因为是随机存储的，所以需要知道第一个元素的地址（基址），容器的长度，容器容量不够扩容时的增量
    // 3. 需要注意哪些细节? 如果线性表不存在就正常初始化，如果线性表已存在，还能就行初始化化吗？
    // malloc 分配内存一定会成功吗？如果内存足够，肯定会分配成功，如果系统内存不够还能分配成功吗，malloc分配失败会返回NULL

    // malloc:
    // references: http://c.biancheng.net/cpp/html/137.html
    // 分配预定义长度的内存空间，长度以 Byte 为单位，函数执行完后只做了分配内存空间，不会初始化，所以它们的值是未知的
    // 分配成功返回指向该内存的地址，首地址，失败则返回 NULL。
    // 一定会申请成功吗？如果内存空间不够肯定申请不成功，所以需要自行判单是否申请成功，再进行后续操作
    // 注意：函数的返回值类型是 void *，void 并不是说没有返回值或者返回空指针，而是返回的指针类型未知。
    // 所以在使用 malloc() 时通常需要进行强制类型转换，将 void 指针转换成我们希望的类型
    // (*L).elem 这是什么用法，需要去看郝斌的C语言指针
    (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if ((*L).elem == NULL) {
        exit(OVERFLOW);
    }

    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;

    return OK;
}

/**
 * 销毁结构
 *
 * 释放顺序表所占结构
 *
 * @param L
 * @return
 */
Status Destroy(SqList *L) {
    // 思考：
    // 销毁顺序表需要哪些前提？1. 如果顺序表存在，才能销毁，如果顺序表不存在，可以销毁吗？
    // 具体怎么销毁？销毁需要完成哪些操作?
    if (L == NULL || (*L).elem == NULL) {
        return ERROR;
    }
    // 释放顺序表内存
    free((*L).elem);

    // 释放内存后置空指针
    (*L).elem = NULL;
    // 顺序表长度跟容量都归零
    (*L).length = 0;
    (*L).listsize = 0;

    return OK;
}

/**
 * 置空（内容）
 *
 * 只是清理顺序表中存储的数据，不释放顺序表所占内存。
 *
 * @param L
 * @return
 */
Status ClearList(SqList *L) {
    // 思考：
    // 置空时需要哪些前提？前提是确保顺序表结构存在
    // 如果顺序表存在，才能置空，如果顺序表不存在呢？
    // 置空时需要哪些操作？比如elem, length, listsize如何处理？
    if (L == NULL || (*L).elem == NULL) {
        return ERROR;
    }

    (*L).length = 0;

    return OK;
}

/**
 * 判空
 *
 * 判断顺序表是否包含数据
 *
 * 返回值：
 * TRUE: 空表
 * FALSE: 非空表
 *
 * @param L
 * @return
 */
Status ListEmpty(SqList L) {
    return L.length == 0 ? TRUE : FALSE;
}

/**
 * 计数
 *
 * 返回顺序表包含的有效元素数量
 *
 * @param L
 * @return
 */
Status ListLength(SqList L) {
    // 思考：
    // 前提是否需要考虑顺序表是否存在，如果顺序表不存在呢？可以返回 length?
    return L.length;
}