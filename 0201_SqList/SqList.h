//
// Created by finnley on 2022/1/25.
//

#ifndef SQLIST_H
#define SQLIST_H

#include "stdio.h"
// 提供malloc、realloc、free、exit原型
#include "stdlib.h"
#include "../Status/Status.h"

/**
 * page. 22
 */
// ------------- 线性表动态分配顺序存储结构
#define LIST_INIT_SIZE    100     // 线性表存储空间的初始化分配量
#define LISTINCREMENT     10      // 线性表存储空间的分配增量

// 定义顺序表元素类型
typedef int ElemType;

/**
 * 顺序表结构
 *
 * 注：elem在使用前需要先为其分配内存，且元素从elem[0]处开始存储
 */
typedef struct {
  ElemType *elem;    // 顺序表存储空间基址（指向顺序表所占内存的起始位置）
  int length;        // 当前顺序表长度（包含多少元素）
  int listsize;      // 当前分配的存储容量（以 sizeof(ElemType) 为单位，也就是可以存储多少个元素，类似 golang 中 slice capacity）
} SqList;

/**
 *
 */
/**
 * 初始化
 *
 * 操作结果：构造一个空的线性表 L
 *
 * @param L
 * @return
 */
Status InitList(SqList *L);

/**
 * 销毁（结构）
 *
 * 释放顺序表所占内存。
 *
 * 初始条件：线性表 L已存在
 * 操作结果：销毁线性表 L
 *
 * @param L
 * @return
 */
Status DestroyList(SqList *L);

/**
 * 置空（内容）
 *
 * 只是清理顺序表中存储的数据，不释放顺序表所占内存
 *
 * 初始条件：线性表已存在
 * 操作结果：将 L 重置为空表
 *
 * @param L
 * @return
 */
Status ClearLit(SqList *L);

/**
 * 判空
 *
 * 判断顺序表中是否包含有效数据
 *
 * @param L
 * @return
 */
Status ListEmpty(SqList L);

/**
 * 计数
 *
 * 返回顺序表包含的有效元素数量
 *
 * 初始条件：线性表 L 存在
 * 操作结果：返回 L 中数据元素个数
 *
 * @param L
 * @return
 */
int ListLength(SqList L);

/**
 * 取值
 *
 * 获取顺序表中第 i 个元素，将其存储到 e 中
 * 如果找到，返回 OK，否则返回 ERROR
 *
 * 初始条件：线性表 L 已存在，1 <= i <= ListLength(L)
 * 操作结果：用 e 返回 L 中第 i 个数据元素的值
 *
 * @param L
 * @param i
 * @param e
 * @return
 */
Status GetElem(SqList L, int i, ElemType *e);

/**
 * 查找
 *
 * 返回顺序表首个与 e 满足 Compare 关系的元素位序
 * 如果不存在这样的元素，则返回 0
 *
 *【备注】
 * 元素e是Compare函数第二个形参
 *
 * 初始条件：线性表 L 已存在，compare() 是数据元素判定函数
 * 操作结果：返回 L 中第 1 个与 e 满足关系 compare() 的数据元素的位序。若这样的数据元素不存在，则返回 0
 *
 * @param L
 * @param e
 * @param Compare
 * @return
 */
int LocateElem(SqList L, ElemType e, Status(Compare)(ElemType, ElemType));

/**
 * 前驱
 *
 * 获取元素 cur_e 的前驱
 * 如果存在，将其存储到 pre_e 中，返回 OK
 * 如果不存在，则返回 ERROR
 *
 * 初始条件：线性表 L 已存在
 * 操作结果：若 cur_e 是 L 的数据元素，且不是第一个，则用 pre_e 返回它的前驱，否则操作失败，pre_e 无定义
 *
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e);

/**
 * 后继
 *
 * 获取元素cur_e的后继
 * 如果存在，将其存储到next_e中，返回OK，
 * 如果不存在，则返回ERROR
 *
 * 初始条件：线性表 L 已存在
 * 操作结果：若 cur_e 是 L 的数据元素，且不是最后一个，则用 next_e 返回它的后继，否则操作失败，next_e 无定义
 *
 * @param L
 * @param cur_e
 * @param next_e
 * @return
 */
Status NextElem(SqList L, ElemType cur_e, ElemType *next_e);

/**
 * 插入
 *
 * 向顺序表第i个位置上插入e，插入成功则返回OK，否则返回ERROR
 *
 * 初始条件：线性表 L 已存在，1 <= i <= ListLength(L) + 1
 * 操作结果: 在 L 中第 i 个位置之前插入新的数据元素 e，L 的长度加1
 *
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListInsert(SqList L, int i, ElemType *e);

/**
 * 删除
 *
 * 删除顺序表第i个位置上的元素，并将被删除元素存储到e中
 * 删除成功则返回OK，否则返回ERROR
 *
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListDelete(SqList L, int i, ElemType *e);

/**
 * 遍历
 *
 * 用visit函数访问顺序表L
 *
 * @param L
 * @param Visit
 */
void ListTraverse(SqList L, void(Visit)(ElemType));

#endif //SQLIST_H
