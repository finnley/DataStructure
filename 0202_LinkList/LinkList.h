//
// 线性表的链式存储结构（链表）
// Created by mingm on 2022/2/28.
//

#ifndef LINKLIST_H
#define LINKLIST_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../Status/Status.h"

// 单链表数据元素类型定义
typedef int ElemType;

// 单链表数据结构
// 这里的单链表存在头结点
// 可以将 struct LNode 看作一个整体，这个整体是一个类型，类型 typedef Bool true;
typedef struct LNode {
    ElemType data;          // 数据结点
    struct LNode *next;     // 指向下一个节点的指针
} LNode, *LinkList; // LNode等价于struct LNode, LinkList等价于struct LNode *

// 指向单链表结点的指针
// 指向LNode这个结构体类型的的指针
// 可以看作某个结点的地址
// 用来表示头节点的地址，知道了地址也就知道了头节点
//typedef LNode *LinkList; // 我放到上面的结构体里面了

/**
 * 初始化
 *
 * 初始化成功则返回OK，否则返回ERROR。
 *
 * 假设L是LinkList类型的变量，则L为链表的头指针，它指向表中的第一个结点；
 * 如果有头节点，则头指针指向头结点
 *
 * @param L
 * @return
 */
Status InitList(LinkList *L);

/**
 * 销毁（结构）
 *
 * 释放连表所占内存
 *
 * @param L
 * @return
 */
Status DestroyList(LinkList *L);

/**
 * 置空（内容）
 *
 * 这里需要释放连表中头节点的处的空间
 *
 * @param L
 * @return
 */
Status ClearList(LinkList L);

/**
 * 判空
 *
 * 判断连表中是否包含有效数据
 *
 * 返回值：
 * TRUE: 连表为空
 * FALSE: 连表不为空
 *
 * @param L
 * @return
 */
Status ListEmpty(LinkList L);

/**
 * 计数
 *
 * 返回连表包含的有效元素的数量
 *
 * @param L
 * @return
 */
int ListLength(LinkList L);

/**
 * 取值
 *
 * 获取连表中第i个元素，将其存储到e中
 * 如果可以找到，返回OK，否则，返回FALSE
 *
 * 教材中i的含义是元素位置，从1开始计数，但这不符合编码的通用约定。
 * 通常，i的含义应该指索引，即从0开始计数。
 *
 * @param L
 * @param i
 * @param e
 * @return
 */
Status GetElem(LinkList L, int i, ElemType *e);

/*
 * 查找
 *
 * 返回链表中首个与e满足Compare关系的元素位序。
 * 如果不存在这样的元素，则返回0。
 *
 *【备注】
 * 元素e是Compare函数第二个形参
 */
int LocateElem(LinkList L, ElemType e, Status(Compare)(ElemType, ElemType));

/*
 * 前驱
 *
 * 获取元素cur_e的前驱，
 * 如果存在，将其存储到pre_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e);

/*
 * 后继
 *
 * 获取元素cur_e的后继，
 * 如果存在，将其存储到next_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status NextElem(LinkList L, ElemType cur_e, ElemType* next_e);

/*
 * ████████ 算法2.9 ████████
 *
 * 插入
 *
 * 向链表第i个位置上插入e，插入成功则返回OK，否则返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数
 */
Status ListInsert(LinkList L, int i, ElemType e);

/*
 * ████████ 算法2.10 ████████
 *
 * 删除
 *
 * 删除链表第i个位置上的元素，并将被删除元素存储到e中。
 * 删除成功则返回OK，否则返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数
 */
Status ListDelete(LinkList L, int i, ElemType* e);

/*
 * 遍历
 *
 * 用visit函数访问链表L
 */
void ListTraverse(LinkList L, void(Visit)(ElemType));

/*
 * ████████ 算法2.11 ████████
 *
 * 头插法创建链表
 *
 *
 *【备注】
 *
 * 教材中默认从控制台读取数据。
 * 这里为了方便测试，避免每次运行都手动输入数据，
 * 因而允许选择从预设的文件path中读取测试数据。
 *
 * 如果需要从控制台读取数据，则path为NULL或者为空串，
 * 如果需要从文件中读取数据，则需要在path中填写文件名信息。
 */
Status CreateList_Head(LinkList* L, int n, char* path);

/*
 * 尾插法创建链表
 *
 *
 *【备注】
 *
 * 教材中默认从控制台读取数据。
 * 这里为了方便测试，避免每次运行都手动输入数据，
 * 因而允许选择从预设的文件path中读取测试数据。
 *
 * 如果需要从控制台读取数据，则path为NULL或者为空串，
 * 如果需要从文件中读取数据，则需要在path中填写文件名信息。
 */
Status CreateList_Tail(LinkList* L, int n, char* path);

#endif //LINKLIST_H
