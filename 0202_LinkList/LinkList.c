//
// 线性表的链式存储结构（链表）
// Created by mingm on 2022/2/28.
//

#include "LinkList.h"

/**
 * 头节点：
 * 有时，在链表的第一个节点之前会额外增设一个节点，该节点的数据域一般不存放数据（有些情况下也可以存放链表的长度等信息），
 * 此节点被称为头节点。
 *
 * 若链表中存在头节点，且头节点的指针域为空（NULL），表明链表是空表。
 *
 * 头节点对于链表来说，不是必须的，换句话说，一个完整的链表中可以不设有头节点。
 * 那么，可能有人会问：既然头节点无关紧要，那它有什么作用？在处理某些问题时，给链表添加头节点会使问题变得简单。
 *
 * 头指针：
 * 链表的头指针永远指向链表中第一个节点的位置，换句话说，如果链表有头节点，头指针指向头节点；否则，头指针指向首元节点。
 * 即指向头结点的指针变量
 *
 * 一个链表可以头节点，但不能没有头指针。
 *
 * 头节点和头指针的区别在程序中的直接体现是：头指针只声明而没有分配存储空间，头节点需要声明并分配一个节点的实际物理内存。
 *
 * 确定一个链表需要几个参数：
 * 只需要一个参数，头指针
 * 因为通过头指针可以推算出链表的其他所有信息
 */

/**
 * 初始化
 *
 * 只是初始化一个头节点
 * 初始化成功则返回OK，否则返回ERROR。
 *
 * L为带头结点的单链表的头指针
 * 假设L是LinkList类型的变量，则L为链表的头指针，它指向表中的第一个结点；
 * 如果有头节点，则头指针指向头结点
 *
 * @param L
 * @return
 */
Status InitList(LinkList *L) {
    // int i = 10;          ==> i, addr: 1000H, val: 10,    i是int类型, 只能存放整形变量
    // int *p = &i;         ==> p, addr: 2000H, val: 1000H, p是int *类型变量, p只能存放i的地址
    // int **q = &p;        ==> q, addr: 3000H, val: 2000H, q是(int *) *类型变量，q只能存放p的地址
    // int ***r = &q;       ==> r, addr: 4000H, val: 3000H, r是((int *) *) *类型变量, r只能存q的地址
    // 反过来推如何用r来表示i
    // r是q的地址，则*r 就是 q, *r表示以r的内容为地址的变量，r的内容是3000H，以3000H为地址的变量就是q
    // **r 等价于 *q, *q就是p
    // ***r 等价于*p, *p就是i
    // 所以***r等价于i

    // LinkList 本身就是一个 TYPE * 类型的变量，类似 int * p;
    // LinkList *L可以看作是定义了L，L是个(TYPE *) * 类型的变量，也就是L以 TYPE *的变量地址为地址的变量
    // 类似于int * *q = &p; 则 *q 就是 p, 即*L 等价于 TYPE * 类型的变量，也就是 LinkList

    // 头节点是什么类型的呀？LNode类型的，所以获取字节就是 sizeof(LNode)
    // malloc返回的指针类型未知，所以需要强制类型转换，指向头节点的指针，类型是LinkList,指针类型
    // 用什么来接收返回值？L还是 (*L)?

    LinkList lList = (LinkList) malloc(sizeof(LNode));

    // 产生头结点，并使L指向此头结点
    // 或者说是 分配了一个不存放有效数据的头结点
//    (*L) = (LinkList) malloc(sizeof(LNode));
//     上面的语句可以写成下面写法吗？
//    L = (LinkList *) malloc(sizeof(LNode));
    if (*L == NULL) {
        exit(OVERFLOW);
    }
    // 为什么不需要指定data为NULL
    //(*L)->data = NULL;
    (*L)->next = NULL;

    return OK;
}

/**
 * 销毁(结构)
 *
 * 释放链表所占内存，头结点也会被清理。
 *
 * @param L
 * @return
 */
Status DestroyList(LinkList *L) {
    LinkList p;

    // 确保链表结构存在
    if (L == NULL || *L == NULL) {
        return ERROR;
    }

    p = *L;
    while (p != NULL) {
        p = (*L)->next;
        free(*L);
        (*L) = p;
    }

    *L = NULL;

    return OK;
}

#include "LinkList.h"
