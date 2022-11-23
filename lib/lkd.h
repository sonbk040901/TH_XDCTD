#define LKD_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMBER_OF_TIMES 10  // So lan xuat hien cua tu trong file
#ifndef STRUCT_DT
#define STRUCT_DT
typedef struct DT
{
    char word[256];
    unsigned char count; // Dem so lan xuat hien
    char position[MAX_NUMBER_OF_TIMES][256];
} DataType;
typedef DataType ElementType;
// const ElementType NotFound = {"Not Found", "Not Found", "Not Found"};
#endif
struct _PointerType
{
    ElementType data;
    struct _PointerType *Next;
};
typedef struct _PointerType PointerType;
PointerType *InsertMiddle(PointerType *Prev, ElementType X);  /*Xoa phan tu o sau vi tri prev(Phai tim phan tu prev de thao tac)*/
ElementType Delete(PointerType *Prev);                        /*Xoa phan tu dung sau phan tu prev va tra ve data cua phan tu do*/
PointerType *InsertToHead(PointerType *First, ElementType X); /*Them 1 phan tu moi vao dau cua list*/
PointerType *InsertToLast(PointerType *First, ElementType X); /*Them 1 phan tu moi vao cuoi cua list*/
PointerType *DeleteHead(PointerType *First);                  /*Xoa phan tu dau cua list*/
PointerType *DeleteLast(PointerType *First);                  /*Xoa phan tu cuoi cua list*/
int IsEmpty(PointerType *First);                              /*Kiem tra xem list co rong khong*/
PointerType *MakeNull(PointerType *First);                    /*Khoi tao list ve list rong*/
void Print(PointerType *First);                               /*In ra data cua list*/