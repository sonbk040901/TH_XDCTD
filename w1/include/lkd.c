#include "lkd.h"
#include <stdio.h>
#include <stdlib.h>

PointerType *InsertMiddle(PointerType *Prev, ElementType X)
{
    PointerType *TempNode;
    TempNode = (PointerType *)malloc(sizeof(PointerType));
    TempNode->data = X;
    TempNode->Next = Prev->Next;
    Prev->Next = TempNode;
    return TempNode;
}
ElementType Delete(PointerType *Prev)
{
    ElementType X;
    PointerType *TempNode;
    TempNode = Prev->Next;
    Prev->Next = Prev->Next->Next;
    X = TempNode->data;
    free(TempNode);
    return X;
}
PointerType *InsertToHead(PointerType *First, ElementType X)
{
    PointerType *TempNode;
    TempNode = (PointerType *)malloc(sizeof(PointerType));
    TempNode->data = X;
    TempNode->Next = First;
    return TempNode;
}
PointerType *InsertToLast(PointerType *First, ElementType X)
{
    PointerType *NewNode;
    PointerType *TempNode;
    NewNode = (PointerType *)malloc(sizeof(PointerType));
    NewNode->data = X;
    NewNode->Next = NULL;
    TempNode = First;
    while (TempNode->Next != NULL)
        TempNode = TempNode->Next;
    TempNode->Next = NewNode;
    return First;
}
PointerType *DeleteHead(PointerType *First)
{
    PointerType *TempNode;
    TempNode = First->Next;
    free(First);
    return TempNode;
}
PointerType *DeleteLast(PointerType *First)
{
    PointerType *root;
    root = First;
    while (root->Next->Next != NULL)
        root = root->Next;
    free(root->Next);
    root->Next = NULL;
    return First;
}
int IsEmpty(PointerType *First)
{
    return !First;
}
PointerType *MakeNull(PointerType *First)
{
    while (!IsEmpty(First))
        First = DeleteHead(First);
    return First;
}
void Print(PointerType *First)
{
    /*Code tuy vao yeu cau cua tung bai*/
}