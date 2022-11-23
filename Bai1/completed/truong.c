#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#define tenfile1 "vanban.txt"

int main(int argc, char const *argv[])
{
    char tu[300];
    FILE *file1 = fopen(tenfile1, "r");
    fgets(tu, sizeof(tu), file1);
    tu[strlen(tu) - 2] = '\0';
    // for (int i = 0; i < strlen(tu) ; i++)
    // {
    //     printf("%c\t",tu[i]);
    // }
    printf("%s %x%d", tu, '\r', '\n');
    fclose(file1);
    return 0;
}