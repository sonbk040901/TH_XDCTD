#include "jrb.h"
#include "dllist.h"
#include "jval.h"
#include <stdio.h>
#include <string.h>
#include "fields.h"
#include <stdlib.h>

char *trim(char *word)
{
    if (word[strlen(word) - 1] == '.' || word[strlen(word) - 1] == ',' || word[strlen(word) - 1] == ')')
    {
        word[strlen(word) - 1] = '\0';
    }
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        if (word[i] >= 65 && word[i] <= 90)
        {
            word[i] += 32;
        }
    }
    if (word[0] == '(')
    {
        strcpy(word, word + 1);
    }
    return word;
}
Dllist StopWords(char *filename)
{
    Dllist stopWord = new_dllist();
    IS is = new_inputstruct(filename);
    if (is == NULL)
    {
        printf("khong mo duoc file \n");
        exit(0);
    }
    while (get_line(is) >= 0)
    {
        int i;
        for (i = 0; i < is->NF; i++)
        {
            dll_append(stopWord, new_jval_s(strdup(is->fields[i])));
        }
    }
    jettison_inputstruct(is);
    return stopWord;
}

// JRB tree

typedef struct
{
    JRB coord;
    int count;
} position;

void createPos(position *pos)
{
    pos = (position *)malloc(sizeof(position));
    pos->coord = make_jrb();
    pos->count = 0;
}

void addWord(JRB scanner, char *word1, int row, int col)
{
    char *word = trim(word1);
    JRB tmp = jrb_find_str(scanner, word);
    if (tmp == NULL)
    {
        // init p
        position *p = (position *)malloc(sizeof(position));
        p->coord = make_jrb();
        p->count = 0;

        jrb_insert_int(p->coord, row, new_jval_i(col));
        p->count++;
        jrb_insert_str(scanner, strdup(word), new_jval_v(p));
    }
    else
    {
        position *p = (position *)jval_v(tmp->val);
        JRB tree = p->coord;
        jrb_insert_int(tree, row, new_jval_i(col));
        p->count++;
    }
}

int checkStopW(char *word, Dllist stopw)
{
    Dllist tmp;
    dll_traverse(tmp, stopw)
    {
        if (strcmp(word, jval_s(tmp->val)) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int checkTenRieng(char *prev, char *cur)
{
    if (prev[strlen(prev) - 1] != '.')
    {
        if (cur[0] >= 65 && cur[0] <= 90)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int checkNum(char *word)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        if (word[i] >= 48 && word[i] <= 57)
        {
            return 1;
        }
    }
    return 0;
}
JRB handleScanner(char *vanban, char *stopw)
{
    // khởi tạo
    JRB scanner = make_jrb();
    Dllist stopWord = new_dllist();
    stopWord = StopWords(stopw);

    // ======== //

    IS is = new_inputstruct(vanban);
    if (is == NULL)
    {
        printf("khong mo duoc file \n");
        exit(0);
    }
    while (get_line(is) >= 0)
    {
        int i;
        int count = 0;
        for (i = 0; i < is->NF; i++)
        {
            int len = strlen(is->fields[i]);
            char w[1000];
            strcpy(w, is->fields[i]);
            char *word = trim(w);
            if (checkNum(is->fields[i]) || checkStopW(word, stopWord))
            {
                count = count + len + 1;
                continue;
            }
            addWord(scanner, is->fields[i], is->line, count);
            count = count + len + 1;
        }
    }
    jettison_inputstruct(is);
    return scanner;
}
void print(JRB scanner)
{
    JRB tmp;
    jrb_traverse(tmp, scanner)
    {
        printf("%s: ", jval_s((tmp->key)));
        position *p = (position *)jval_v(tmp->val);
        JRB tree = p->coord;
        printf("%d ", p->count);
        JRB node;
        jrb_traverse(node, tree)
        {
            printf("(%d,%d), ", jval_i(node->key), jval_i(node->val));
        }
        printf("\n");
    }
}
void main()
{

    JRB scanner = handleScanner("vanban.txt", "stopw.txt");
    print(scanner);
}