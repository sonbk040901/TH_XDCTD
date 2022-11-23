#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    char str[100][20];
    char arr[] = "Molly     Skyward     John \
    60 ";
    int index = 0, i = 0;
    while (sscanf(arr + index, "%s", str[i]) > 0)
    {
        index = ((int)(strstr(arr + index, str[i]) - arr) + strlen(str[i++]));
    }
    printf("%d\n", i);
    strcpy(str[i], str[0]);
    for (int j = 1; j < i; j++)
    {
        strcat(str[i], " ");
        strcat(str[i], str[j]);
    }
    printf("%s\n", str[i]);
    return 0;
}