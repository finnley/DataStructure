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
    (*L).elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
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
    // 销毁顺序表需要哪些前提？1. 如果顺序表存在，才能销毁，如果顺序表不存在，可以销毁吗？一个不存在的顺序表怎么销毁？销个毛线啊，肯定要返回错误了
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
int ListLength(SqList L) {
    // 思考：
    // 前提是否需要考虑顺序表是否存在，如果顺序表不存在呢？可以返回 length?
    return L.length;
}

/**
 * 取值
 * 获取顺序表中第i个元素，将其存储到e中。
 * 如果可以找到，返回OK，否则，返回ERROR。
 *
 * 教材中i的含义是元素位置，从1开始计数，但这不符合编码的通用约定。通常，i的含义应该指索引，即从0开始计数。
 *
 * @param L
 * @param i
 * @param e
 * @return
 */
Status GetElem(SqList L, int i, ElemType *e) {
    // 思考：有什么前提条件？
    // 1. i 位置的取值范围是 1<=i<=Length(L)，如果不在此范围内，返回错误
    // 2. 如果i满足条件怎么取值？L.elem[i-1] 1->0, 2->1, 3->2  => [i-1]
    if (i < 1 || i > ListLength(L)) {
        return ERROR;
    }
    *e = L.elem[i - 1];

    return OK;
}

/**
 * 查找
 *
 * 返回顺序表中首个与e满足Compare关系的元素位序。
 * 如果不存在这样的元素，则返回0。
 *
 * @param L
 * @param e
 * @param Compare
 * @return
 */
int LocateElem(SqList L, ElemType e, Status(Compare)(ElemType, ElemType)) {
    // 思考：
    // 1. 顺序表不存在如何处理？返回错误
    // 2. 如何查找顺序表 L 中第一个满足 Compare 关系的元素 e 的 位置，如果不存在返回0？
    // 遍历，在可遍历范围内（i < len(L)）并且当前元素不满足Compare关系时就继续下一个元素的判断
    // 3. 因为要返回满足条件的位序，所以需要一个变量i来保存位序

    // 确保顺序表结构存在
    if (L.elem == NULL) {
        return ERROR;
    }

    int i = 1;
    // 4. 为什么要定义这个指针?
    ElemType *p;
    // p 指向 L 的第一个元素，
    p = L.elem;

    // *p++ 等价于 *(p++)

    // p++整体表示L中的第一个元素地址，因为后自增整体表达式的值是p加1前的值，那么*(p++)表示第一个值，第一个值语e进行判断，最后指针p往后移动一位
    while (i <= L.length && !Compare(*p++, e)) {
        // 前自增整体表达式的值是i+1后的值，第一次循环后，i的值变成了2
        // 这里需要避开前自增和后自增的差异，这里 ++i 和 i++ 是一样的，都是让i的值+1
        // 最后直到 i 的值超出L的长度则退出循环
        ++i;
    }

    if (i <= L.length) {
        return i;
    } else {
        return 0;
    }
}

/**
 * 前驱
 *
 * 获取元素 cur_e 的前驱
 * 如果存在，将其存储到 pre_e 中，返回 OK
 * 如果不存在，返回 ERROR
 *
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e) {
    // 思考：
    // 1.顺序表是空的
    // 2.有哪些前提条件？
    // 除了第一个元素外，每个元素都有一个直接前驱，所以可能会出现顺序表元素个数小于2个？比如只有一个，那就不存在前驱

    // 确保顺序表结构存在，且最少包含两个元素(L.length < 2 或者 L.length <= 1都可以)
    if (L.elem == NULL || L.length < 2) {
        return ERROR;
    }

    // 这里的i初始化为第1个元素的【索引】
    int i = 0;

    // 从第1个元素开始，查找cur_e的位置
    while (i < L.length && L.elem[i] != cur_e) {
        ++i;
    }

    // 如果cur_e是首个元素(没有前驱)，或者没找到元素cur_e，返回ERROR
    if (i == 0 || i > L.length) {
        return ERROR;
    }

    // 存储 cur_e 的前驱
    *pre_e = L.elem[i - 1];

    return OK;
}

/**
 * 后继
 *
 * 获取元素cur_e的后继，
 * 如果存在，将其存储到next_e中，返回OK，
 * 如果不存在，则返回ERROR。
 *
 * @param L
 * @param cur_e
 * @param next_e
 * @return
 */
Status NextElem(SqList L, ElemType cur_e, ElemType *next_e) {
    // 确保顺序表结构存在，且最少包含两个元素
    if (L.elem == NULL || L.length < 2) {
        return ERROR;
    }

    // 这里的i初始化为第1个元素的【索引】
    int i = 0;

    while (i < L.length - 1 && L.elem[i] != cur_e) {
        ++i;
    }
    if (i >= L.length - 1) {
        return ERROR;
    }

    // 存储cur_e的后继
    *next_e = L.elem[i + 1];

    return OK;
}

/**
 * 插入
 *
 * 向顺序表第i个位置上插入e，插入成功则返回OK，否则返回ERROR。
 *
 * 【备注】
 * 教材中i的含义是元素位置，从1开始计数
 *
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListInsert(SqList *L, int i, ElemType *e) {
    // 思考：
    // 1. 顺序表L不存在
    // 2. 插入的位置越界
    // 3. 顺序表L空间不够，已满，需要扩容

    // 确保顺序表结构存在
    if (L == NULL || (*L).elem == NULL) {
        return ERROR;
    }
    // i值越界
    if (i < 1 || i > (*L).length + 1) {
        return ERROR;
    }

    // 若存储空间已满，则增加新空间
    if ((*L).length >= (*L).listsize) {
        // 基于现有空间扩容
    }
}

/**
 * 遍历
 *
 * 用visit函数访问顺序表L
 *
 * @param L
 * @param Visit
 */
void ListTraverse(SqList L, void(Visit)(ElemType)) {
    int i;

    for (i = 0; i < L.length; i++) {
        Visit(L.elem[i]);
    }

    printf("\n");
}