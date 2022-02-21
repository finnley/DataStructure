//
// Created by finnley on 2022/1/25.
//
#include "stdio.h"
#include "SqList.h"

// 打印元素
void PrintElem(ElemType e) {
    printf("%d ", e);
}

int main(int argc, char** argv) {
    SqList L; // 声明一个顺序表，此时并没有初始化

    int i;

    ElemType e;

    printf("InitList \n");
    {
        printf("初始化顺序表 L...\n");
        InitList(&L);
    }
    PressEnterToContinue(debug);

    printf("ListEmpty \n");
    {
        if (ListEmpty(L) == TRUE) {
            printf("L 为空\n");
        } else {
            printf("L 不为空\n");
        }
    }
    PressEnterToContinue(debug);

    printf("ListLength \n");
    {
        printf("L 长度 = %d\n", ListLength(L));
    }
    PressEnterToContinue(debug);

    printf("ListTraverse \n");
    {
        printf("L 中的元素为：L = ");
        ListTraverse(L, PrintElem);
    }
    PressEnterToContinue(debug);



    return 0;
}
