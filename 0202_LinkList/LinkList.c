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

    // 数据结点类型是 LNode，定以了一个 LinkList 变量用来保存LNode类型结点的地址，LinkList类型是 TYPE *类型，LinkList可以理解为头结点
    // LinkList 本身是一个 TYPE * 类型的变量，类似 int *p;
    // LinkList *L可以看作是定义了L，L是个(TYPE *) * 类型的变量，也就是L以 TYPE *的变量地址为地址的变量，L保存的是头结点的地址，*L就是头结点LinkList
    // 类似于int * *q = &p; 则 *q 就是 p, 即*L 等价于 TYPE * 类型的变量，是个地址，是个TYPE类型变量的地址，这个TYPE就是LNode，也就是LNode类型的地址

    // 头节点是什么类型的呀？LNode类型的，所以获取字节就是 sizeof(LNode)
    // malloc返回的指针类型未知，所以需要强制类型转换，指向头节点的指针，类型是LinkList,指针类型
    // 用什么来接收返回值？L还是 (*L)?

    // 1. 产生头结点，并使L指向此头结点，或者说是 分配了一个不存放有效数据的头结点
    // *L就是LinkList，LinkList是个指针，所以这个的*L不是内容，而是指针，是个地址，头结点的地址
    (*L) = (LinkList) malloc(sizeof(LNode));
    // 上面的语句可以写成下面写法吗？
    // L = (LinkList *) malloc(sizeof(LNode));

    // 2. 如果头结点分配失败，退出程序
    if (*L == NULL) {
        exit(OVERFLOW);
    }

    // 3. 设置头节点指向为空
    // 初始化链表长度为0，头节点指向必为空，我没有下一个结点，就单独一个头结点
    // 为什么不需要指定data为NULL，比如(*L)->data = NULL;
    // 因为头节点不存放有效数据，可以不用设置数据域
    (*L)->next = NULL;

    return OK;
}

/**
 * 销毁(结构)
 *
 * 释放链表所占内存，头结点也会被清理。
 * 是先销毁了链表的头，然后接着一个一个的把后面的销毁了，这样这个链表就不能再使用了，即把包括头的所有节点全部释放。
 * 销毁就是链表没了，整个链表(包括头)的空间都被释放了，不能进行任何操作了
 *
 * @param L
 * @return
 */
Status DestroyList(LinkList *L) {
    // 思考：
    // 怎么才能销毁一个链表? 需要传入哪些参数
    // 传入一个保存头结点的指针，也就是头指针
    // 如何通过头指针销毁链表？
    // 可以将头结点的指向设置为NULL吗？设置为NULL，会存在什么风险
    // 不能，那原本头结点之后的所有结点都没有释放，其实并没有将那块内存空间的操作权限还给操作系统，可能会导致内存溢出
    // 还需要遍历整个链表进行释放，定义个指向结点的指针，释放调哪个结点，这个指针就指向这个结点的下一个结点


    LinkList p;

    // 1.确保链表结构存在
    // 头指针都不存在，还是个链表吗？都不是个链表还释放放个屁
    // L 是头指针变量，是头结点的地址；*L是头结点
    // 所以这边判断L头结点指针是否为空，头结点是否为空
    if (L == NULL || *L == NULL) {
        return ERROR;
    }

    // 2. 遍历链表，释放结点
    // 需要定义一个指针，指向头结点
    // 是先释放，然后再将指针指向下一个；还是先指向下一个，然后再释放
    // p 就是 LinkList 头结点，保存了是首结点指针
    p = *L;
    while (p != NULL) {
        // 第一个循环开始p先后移一位，指向首结点
        p = (*L)->next;
        // 接着释放头结点
        free(*L);
        // L也后移一位，此时首结点可以理解成是存放了有效数据的头节点
        (*L) = p;
    }

    // 3.最后一个结点设置为NULL
    *L = NULL;

    return OK;
}

/**
 * 置空(内容)
 *
 * 这里需要释放链表中非头结点处的空间。
 *
 * 是先保留了链表的头，然后把头后面的所有的都销毁，最后把头里指向下一个的指针设为空，这样就相当与清空了，
 * 但这个链表还在，还可以继续使用；即保留了头，后面的全部释放。
 * 清空是链表的头还在，可以继续插入节点；
 *
 * @param L
 * @return
 */
Status ClearList(LinkList L) {
    LinkList pre, p;

    if (L == NULL) {
        return ERROR;
    }

    p = L->next;

    // 释放链表上所有结点所占内存
    while (p != NULL) {
        pre = p;
        p = p->next;
        free(pre);
    }

    L->next = NULL;

    return OK;
}

/**
 * 判空
 *
 * 判断链表中是否包含有效数据。
 *
 * @param L
 * @return
 */
Status ListEmpty(LinkList L) {
    if (L != NULL && L->next == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int ListLength(LinkList L) {
    // 确保链表存在且不为空
    if (L == NULL || L->next == NULL) {
        return 0;
    }

    int i = 0;
    LinkList p;

    p = L->next;
    // 遍历所有结点
    while (p != NULL) {
        i++;
        p = p->next;
    }

    return i;
}

Status GetElem(LinkList L, int i, ElemType *e) {
    // 确保链表存在且不为空
    if (L == NULL || L->next == NULL) {
        return ERROR;
    }

    LinkList p;
    int j = 1;

    p = L->next;
    while (p && j < i) {
        p = p->next;
        ++j;
    }

    // 第i个元素不存在
    if (!p || j > i) {
        return ERROR;
    }
    *e = p->data;

    return OK;
}

int LocateElem(LinkList L, ElemType e, Status(Compare)(ElemType, ElemType)) {

}

Status ListInsert(LinkList L, int i, ElemType e) {

}

#include "LinkList.h"
