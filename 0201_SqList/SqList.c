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
    // 1. 为什么需要初始化线性表？
    // 2. 初始化顺序表需要哪些准备？
    // 3. 需要注意哪些细节?
    // 4. malloc 分配内存一定会成功吗？如果内存足够，肯定会分配成功，如果系统内存不够还能分配成功吗?

    // A:
    // 1. 初始化是为了有一个盛放数据容器，没有容器怎么去存放数据呢
    // 2. 因为顺序表是随机存取的，所以需要知道第一个元素的地址（基址），容器的长度，容器容量不够扩容时的增量
    // 3. 如果线性表不存在就正常初始化，如果线性表已存在，还能就行初始化化吗？
    // 4. malloc分配失败会返回NULL

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
Status ListInsert(SqList *L, int i, ElemType e) {
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

    ElemType *newbase;

    // 若存储空间已满，则增加新空间
    if ((*L).length >= (*L).listsize) {
        // 基于现有空间扩容
        // 新的基址
        newbase = (ElemType *) realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
        if (newbase == NULL || (*L).elem == NULL) {
            exit(OVERFLOW);
        }

        // 新基址
        (*L).elem = newbase;
        // 存储空间
        (*L).listsize += LISTINCREMENT;
    }

    // 插入数据需要知道哪些数据？
    // 1. 右移的第一个元素 (*L).elem[(*L).length-1];
    // 2. 右移的元素个数
    // 3. 插入的位置 (*L).elem[i-1]
    ElemType *p, *q;

    // p 为右移的第一个元素
    p = &(*L).elem[(*L).length - 1];
    // q 为插入元素的地址
    q = &(*L).elem[i - 1];
    // 右移元素，腾出位置
    for (p; p >= q; --p) {
        *(p + 1) = *p;
    }

    // 插入元素
    *q = e;

    (*L).length++;

    return OK;
}

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
Status ListDelete(SqList *L, int i, ElemType *e) {
    // 确保顺序表结构存在
    if (L == NULL || (*L).elem == NULL) {
        return ERROR;
    }
    // i值越界
    if (i < 1 || i > (*L).length) {
        return ERROR;
    }

    ElemType *p, *q;
    // p为被删除元素的位置
    p = &(*L).elem[i - 1];
    // 获取被删除的元素
    *e = *p;
    // q 为表尾元素的位置
//  q = (*L).elem + (*L).length - 1;
    q = &(*L).elem[(*L).length - 1];

    // 左移元素，被删除的位置上会有新元的进来
    for (++p; p <= q; ++p) {
        *(p - 1) = *p;
    }

    // 长度-1
    (*L).length--;

    return OK;
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

void Union(SqList *La, SqList Lb) {
    // 思路：
    // A=A∪B
    // 1. 扩大线性表 LA 长度
    // 2. 将存在于LB中，但不存在于LA中的数据元素插入到线性表LA中
    // 遍历线性表LB中的每个数据元素，并逐个到线性表LA中查找，如果不存在就插入到LA中

    int La_len, Lb_len;

    // 顺序表长度
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);

    int i;
    ElemType e;

    for (i = 1; i <= Lb_len; i++) {
        // 取从Lb中第i个元素赋值给e
        GetElem(Lb, i, &e);

        // 若e不在La中则插入
        if (!LocateElem(*La, e, equal)) {
            ListInsert(La, ++La_len, e);
        }
    }
}

/**
 * 判等
 *
 * 判断两元素是否相等
 * 如果相等，则返回TRUE，否则，返回FALSE。
 *
 * @param e1
 * @param e2
 * @return
 */
Status equal(ElemType e1, ElemType e2) {
    return e1 == e2 ? TRUE : FALSE;
}


// 归并非降序顺序表
/**
 * 非递减链表归并：C=A+B
 * 归并顺序表La和Lb，生成新的顺序表Lc。
 * 其中，La、Lb、Lc均为非递减序列。
 *
 * @param La
 * @param Lb
 * @param Lc
 */
void MergeSqList_1(SqList La, SqList Lb, SqList *Lc) {
    /**
     * 思路
     * 已知线性表LA和LB中的数据元素按值非递减有序排列，先要求将 LA和LB对并为一个心的线性表LC
     * LA = (3, 5, 8, 11)
     * LB = (2, 6, 8, 9, 11, 15, 20)
     * 则LC = (2, 3, 5, 6, 8, 9, 11, 11, 15, 20)
     *
     * 先设LC是个空表，所以需要先初始化
     * 然后将 LA 或 LB 中的数据逐个插入到LC中即可
     */
    // 初始化Lc
    InitList(Lc);

    int La_len, Lb_len;
    // 获取La、Lb的长度
    La_len = ListLength(La);
    Lb_len = ListLength(Lb);

    int i, j, k;
    i = j = 1;
    k = 0;

    // 比较的元素
    ElemType ai, bj;

    // 如果La及Lb均未遍历完
    // 同时使用 i 遍历La，j 遍历 Lb
    while (i <= La_len && j <= Lb_len) {
        // 分别获取La和Lb当前遍历的元素，分别放到 ai，bj 中
        GetElem(La, i, &ai);
        GetElem(Lb, j, &bj);

        // 比较遍历到的元素，先将比较小的元素加入顺序表Lc
        // 为什么是 ++k 前自增，整体表达式是k+1后的值，最开始也就是插入1的位置
        if (ai <= bj) {
            ListInsert(Lc, ++k, ai);
            i++;
        } else {
            ListInsert(Lc, ++k, bj);
            j++;
        }
    }

    // 如果Lb已遍历完，但La还未遍历完，将La中剩余元素加入Lc
    // i++ 后自增整体表达式是i+1前的值
    // ++k 前自增整体表达式是j+1后的值
    while (i <= La_len) {
        GetElem(La, i++, &ai);
        ListInsert(Lc, ++k, ai);
    }

    // 如果La已遍历完，但Lb还未遍历完，将Lb中剩余元素加入Lc
    while (j <= Lb_len) {
        GetElem(Lb, j++, &bj);
        ListInsert(Lc, ++k, bj);
    }
}

/**
 * 非递减链表归并：C=A+B
 * 归并顺序表La和Lb，生成新的顺序表Lc。
 * 其中，La、Lb、Lc均为非递减序列。
 * 使用指针的方式归并
 *
 * @param La
 * @param Lb
 * @param Lc
 */
void MergeSqList_2(SqList La, SqList Lb, SqList *Lc) {
    ElemType *pa, *pb, *pc;
    ElemType *pa_last, *pb_last;

    // pa 指向La第一个元素
    pa = La.elem;
    // pb 指向Lb第一个元素
    pb = Lb.elem;

    // 此时还没有Lc，这里不适用 InitList 初始化Lc
    (*Lc).listsize = (*Lc).length = La.length + Lb.length;
    pc = (*Lc).elem = (ElemType *) malloc((*Lc).listsize * sizeof(ElemType));
    if (pc == NULL) {
        exit(OVERFLOW);
    }

    // pa_last 指向La最后一个元素
    pa_last = La.elem + La.length - 1;
    // pb_last 指向Lb最后一个元素
    pb_last = Lb.elem + Lb.length - 1;

    // 如果La及Lb均未遍历完
    while (pa <= pa_last && pb <= pb_last) {
        if (*pa <= *pb) {
            *pc++ = *pa++;
        } else {
            *pc++ = *pb++;
        }
    }

    // 如果Lb已遍历完，但La还未遍历完，将La中剩余元素加入Lc
    while(pa <= pa_last) {
        *pc++ = *pa++;
    }

    // 如果La已遍历完，但Lb还未遍历完，将Lb中剩余元素加入Lc
    while(pb <= pb_last) {
        *pc++ = *pb++;
    }
}