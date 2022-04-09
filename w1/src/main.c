#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <jval.h>
#include <jrb.h>
#include <dllist.h>
#include <fields.h>
#include <ctype.h>
typedef struct _position
{
    int num;
    int ln[1000];
    int col[1000];
} * position;
// Duyệt từ file stopw để lấy ra những từ không hợp lệ để check file văn bản
int get_stopw(JRB, char[]);

// Duyệt từ file văn bản và đưa vào jrb những từ đúng định dạng yêu cầu, và vị trí của nó trong file
int get_text(JRB, char[], JRB);

//Đưa từ này vào trong jrb với vị trí ln, col
void insert_tree(JRB, char[], int, int);

// Tạo một position mới lưu trữ vị trí của từ
// Từ đó chưa có trong jrb
position new_pos(int, int);

// Thêm 1 vị trí của từ vào trong position
// Từ đó đã tồn tại trong jrb
void add_pos(position, int, int);

// Kiểm tra xem từ đó có trong những từ không hợp lệ hay không
// Nếu có trả về 1, ngược lại trả về 0
int check_stopw(JRB, char[]);

//Đưa từ về dạng đúng, có nghĩa
// ex: "(abc"->"abc"; "abc."->"abc"; "abc)"->"abc"
// trả về số ký tự bên trái bị xóa đi, bằng -1 nếu từ đó bị xóa hết
int format(char[]);

// In ra từ và vị trí của nó tương ứng với node
void print_word(JRB, FILE *);

/*= === === === === MAIN === === === === ==*/
void main(int argc, char *argv[])
{
    JRB stopw, text, node;
    stopw = make_jrb();
    text = make_jrb();
    FILE *fout;
    fout = fopen("output.txt", "w+");
    //Đọc stopw
    get_stopw(stopw, "stopw.txt");
    //Đọc vanban
    get_text(text, "vanban.txt", stopw);
    // In ra màn hình các từ và vị trí của nó
    jrb_traverse(node, text)
    {
        print_word(node, fout);
    }
    jrb_free_tree(stopw);
    jrb_free_tree(text);
    fclose(fout);
}
/*==========================================*/

int get_stopw(JRB stopw, char filename[])
{
    FILE *file;
    char line[32];
    file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }
    while (fscanf(file, "%s", line) != 0 && !feof(file))
    {
        jrb_insert_str(stopw, strdup(line), new_jval_i(1));
    }
    fclose(file);
    return 1;
}
int get_text(JRB tree, char filename[], JRB stopw)
{
    IS is = new_inputstruct(filename);
    // Vị trí của từ trong dòng đang xét
    int pos;
    // giá trị trả về của hàm format
    int move;
    // Từ đang xét
    char word[1000];
    if (is == NULL)
    {
        return 0;
    }
    while (get_line(is) >= 0) // Lấy ra từng dòng trong file
    {
        pos = 1;
        for (int i = 0; i < is->NF; i++) // Duyệt từng từ trong dòng đang xét
        {
            strcpy(word, is->fields[i]);
            move = format(word);
            if (move != -1)
            {
                if (!check_stopw(stopw, word))
                    insert_tree(tree, word, is->line, pos + move);
            }
            pos += strlen(is->fields[i]) + 1; // Tự động tăng để lấy vị trí của từ tiếp theo
        }
    }
    jettison_inputstruct(is);
    return 1;
}
void insert_tree(JRB tree, char word[], int ln, int col)
{
    JRB find;
    position p;
    find = jrb_find_str(tree, word);
    if (!find)
    {
        p = new_pos(ln, col);
        jrb_insert_str(tree, strdup(word), new_jval_v(p));
    }
    else
    {
        p = (position)jval_v(find->val);
        add_pos(p, ln, col);
    }
}
position new_pos(int ln, int col)
{
    position pos;
    pos = (position)malloc(sizeof(struct _position));
    pos->num = 1;
    pos->ln[0] = ln;
    pos->col[0] = col;
    return pos;
}
void add_pos(position pos, int ln, int col)
{
    pos->ln[pos->num] = ln;
    pos->col[pos->num] = col;
    pos->num++;
}
int check_stopw(JRB stopw, char word[])
{
    return (int)jrb_find_str(stopw, word);
}
int format(char word[])
{
    int length = strlen(word);
    // Giá trị trả về
    int move = 0;
    if (!isalpha(word[length - 1])) // Nếu ký tự cuối không phải chữ cái
    {
        word[length - 1] = 0;
    }
    if (strstr(word, ".")) // Nếu bên trong từ này có dấu chấm
    {
        strcat(word, "."); // =>đây là từ viết tắt, nên phải chèn thêm dấu chấm ở cuối
    }
    length = strlen(word);
    while (!isalpha(word[0]) && word[0] != 0) // Nếu ký tự đầu không phải chữ cái, và ko phải là ký tự kết thúc
    {
        strcpy(word, word + 1); // Lùi sang trái để xóa đi ký tự đầu
        move++;
    }
    for (int i = 0; i < length - move; i++)
    {
        word[i] = tolower(word[i]); // Chuyển về chữ thường
    }
    if (move == length) // Nếu move == length chứng tỏ từ này đã bị xóa hết
    {
        return -1;
    }
    else
        return move;
}
void print_word(JRB node, FILE *fout)
{
    position pos = (position)jval_v(node->val);
    printf("%-10s\t", jval_s(node->key));
    fprintf(fout, "%-10s\t", jval_s(node->key));
    char s[10];
    for (int i = 0; i < pos->num; i++)
    {
        sprintf(s, "(%d,%d)", pos->ln[i], pos->col[i]);
        printf("%-7s", s);
        fprintf(fout, "%-7s", s);
        if (i < pos->num - 1)
        {
            printf("; ");
            fprintf(fout, "; ");
        }
    }
    puts("");
    fputs("\n", fout);
    free(pos);
}