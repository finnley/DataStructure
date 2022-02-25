//
// Created by finnley on 2022/1/25.
//
#include "stdio.h"
#include "SqList.h"

// 打印元素
void PrintElem(ElemType e) {
  printf("%d ", e);
}

/**
 * 判断data>e是否成立
 *
 * @param data
 * @param e
 * @return
 */
Status CmpGreater(ElemType data, ElemType e) {
  return data > e ? TRUE : FALSE;
}

int main(int argc, char **argv) {
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

  printf("████████ ListInsert \n");
  {
    for (i = 1; i <= 8; i++) {
      printf("█ 作为示范，在 L 第 %d 个位置插入 \"%d\"...\n", i, 2 * i);
      ListInsert(&L, i, 2 * i);
    }
  }
  PressEnterToContinue(debug);

  printf("████████ ListTraverse \n");
  {
    printf("█ L 中的元素为：L = ");
    ListTraverse(L, PrintElem);
  }
  PressEnterToContinue(debug);

  printf("████████ ListLength \n");
  {
    i = ListLength(L);
    printf("█ L 的长度为 %d \n", i);
  }
  PressEnterToContinue(debug);

  printf("████████ ListDelete \n");
  {
    printf("█ 删除前的元素：L = ");
    ListTraverse(L, PrintElem);

    printf("█ 尝试删除 L 中第 6 个元素...\n");

    if(ListDelete(&L, 6, &e) == OK) {
      printf("█ 删除成功，被删除元素是：\"%d\"\n", e);
    } else {
      printf("█ 删除失败，第 6 个元素不存在！\n");
    }

    printf("█ 删除后的元素：L = ");
    ListTraverse(L, PrintElem);
  }
  PressEnterToContinue(debug);

  printf("████████ ListTraverse \n");
  {
    printf("█ L 中的元素为：L = ");
    ListTraverse(L, PrintElem);
  }
  PressEnterToContinue(debug);

  return 0;
}
