#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// đọc từ stopw.txt vào mảng stopw_ar
void read_stopw(char stopw_ar[][5]) {
	FILE *fptr;
	char str[5];
	int cnt = 0;	// chỉ số của mảng

	fptr = fopen("stopw.txt", "r");
	while (!feof(fptr)) {
		fscanf(fptr, "%s", str);
		if (strlen(str) == 0) continue;		// xâu đọc được là rỗng thì bỏ qua
		strcpy(stopw_ar[cnt], str);		// copy chuỗi str vào mảng
		cnt++;
		fgets(str, 2, fptr);	// đọc kí tự xuống dòng
	}
	fclose(fptr);
}

// xem ký tự tiếp theo, rồi đưa con trỏ trở lại vị trí cũ
char next_char_peek(FILE *fptr) {
	char ch = fgetc(fptr);	// lấy ký tự tiếp theo
	ungetc(ch, fptr);	// trả lại ký tự đã lấy và lùi con trỏ
	return ch;
}

// kiểm tra ký tự có phải là 1 chữ cái
int letter_check(char ch, FILE *fptr) {
	int result = 0;
	result = result || ('a' <= ch && ch <= 'z');	// kiểm tra thuộc a-z
	result = result || ('A' <= ch && ch <= 'Z');	// kiểm tra thuộc A-Z
	result = result || (ch == '-');		// kiểm tra dấu -
	result = result || (ch == '.' && next_char_peek(fptr) != ' ' && next_char_peek(fptr) != '\r'); // kiểm tra dầu chấm trong từ viết tắt, vd: U.S.
	return result;
}

// kiểm tra từ có phải là 1 tên riêng
int ten_rieng_check(int dot, char *str) {
	if ('A' <= str[0] && str[0] <= 'Z' && dot == 0) return 1;	// chữ cái đầu viết hoa và phía trước KHÔNG phải là dấu chấm
	else return 0;
}

// kiểm tra từ có thuộc stopw
int stopw_check(char stopw_ar[][5], char *str) {
	for (int i = 0; i < 17; i++) {
		if (strcmp(stopw_ar[i], str) == 0) return 1;
	}
	return 0;
}

/**
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.

	 */
char* itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

// đọc từng từ vào chương trình để xử lý
int read_vanban(char stopw_ar[][5], char word[][20], int xuat_hien[], char dong_xuat_hien[][100]) {
	FILE *fptr;
	char str[20];	// xâu ký tự lưu từ lấy được
	char ch;
	int dot = 1, dot_tmp;	// kiểm tra ký tự đặc biệt trước từ hiện tại có phải dấu CHẤM không
	int invalid_word;	// kiểm tra từ có hợp lệ không
	int cur_line = 1;	// dòng hiện tại
	int char_counter = 0;	// chỉ số ký tự của dòng hiện tại
	int word_id = 0;	// chỉ số của từ trong mảng
	int appeared;	// đã xuất hiện trong mảng word chưa
	char tmp_str[3];
	int xuong_dong_check;	// kiểm tra xem có kí tự xuống dòng không

	fptr = fopen("vanban.txt", "r");
	while (!feof(fptr)) {
		ch = fgetc(fptr);	// lấy 1 ký tự
		char_counter++;		// tăng chỉ số ký tự lên 1

		xuong_dong_check = 0;
		while (ch == '\n' || ch == '\r') {	// bỏ qua ký tự xuống dòng
			ch = fgetc(fptr);
			xuong_dong_check = 1;	// tăng biến lên 1 để sau đó tăng chỉ số dòng lên
		}

		cur_line = cur_line + xuong_dong_check;		// tăng chỉ số dòng nếu cần

		if (letter_check(ch, fptr) && xuong_dong_check == 0) {	// kiểm tra ký tự đọc vào là chữ cái hay ký tự khác
			strncat(str, &ch, 1);	// nếu là chữ cái, thêm vào xâu
		} else {	// nếu là ký tự khác -> đã tìm được 1 từ, tiến hành xử lý

			invalid_word = 0;

			invalid_word = invalid_word || (strlen(str) == 0) || (strlen(str) == 1);	// nếu từ tìm được rỗng hoặc có 1 ký tự thì bỏ qua

			if (invalid_word == 0) {
				dot_tmp = (ch == '.') ? 1 : 0;		// nếu từ hiện tại khác rỗng, dấu gần nhất của từ tiếp theo là ký tự hiện tại
			} else {											// nếu từ hiện tại rỗng:
				if (ch != ' ') dot_tmp = (ch == '.') ? 1 : 0;	// nếu ký tự hiện tại khác KHOẢNG TRẮNG, thì dấu gần nhất của từ tiếp theo là ký tự hiện tại
				else dot_tmp = dot;								// nếu ký tự hiện tại là KHOẢNG TRẮNG, thì dấu gần nhất của từ tiếp theo vẫn là dấu cũ
			}

			invalid_word = invalid_word || ten_rieng_check(dot, str);	// kiểm tra xem có phải tên riêng

			for (int i = 0; i < strlen(str); i++)
				str[i] = tolower(str[i]);	// chuyển các ký tự thành ký tự thường

			invalid_word = invalid_word || stopw_check(stopw_ar, str);		// kiểm tra xem có thuộc stopw

			if (invalid_word == 0) {
				appeared = 0;

				for (int i = 0; i < word_id; i++)	// kiểm tra xem từ đã xuất hiện trong mảng word chưa
					if (strcmp(word[i], str) == 0) {
						xuat_hien[i]++;
						dong_xuat_hien[i][strlen(dong_xuat_hien[i])] = ' ';
						dong_xuat_hien[i][strlen(dong_xuat_hien[i])] = '(';
						itoa(cur_line, tmp_str, 10);
						strcat(dong_xuat_hien[i], tmp_str);		// in dòng
						dong_xuat_hien[i][strlen(dong_xuat_hien[i])] = ',';
						itoa(char_counter - strlen(str), tmp_str, 10);
						strcat(dong_xuat_hien[i], tmp_str);		// in cột
						dong_xuat_hien[i][strlen(dong_xuat_hien[i])] = ')';
						appeared = 1;
						break;
					}

				if (appeared == 0) {	// nếu chưa xuất hiện, thêm từ mới vào mảng word
					strcpy(word[word_id], str);
					xuat_hien[word_id] = 1;
					dong_xuat_hien[word_id][strlen(dong_xuat_hien[word_id])] = '(';
					itoa(cur_line, tmp_str, 10);
					strcat(dong_xuat_hien[word_id], tmp_str);	// in dòng
					dong_xuat_hien[word_id][strlen(dong_xuat_hien[word_id])] = ',';
					itoa(char_counter - strlen(str), tmp_str, 10);
					strcat(dong_xuat_hien[word_id], tmp_str);	// in cột
					dong_xuat_hien[word_id][strlen(dong_xuat_hien[word_id])] = ')';
					word_id++;
				}
			}

			str[0] = '\0';		// làm rỗng xâu để lấy từ mới vào
		}
		dot = dot_tmp;		// gán lại giá trị của dot để chuẩn bị cho từ tiếp theo

		if (xuong_dong_check == 1) {	// nếu xuống dòng:
			strncat(str, &ch, 1);	// ghép ký tự lấy từ đầu vòng lặp vào xâu
			char_counter = 1;	// reset chỉ số ký tự
		}
	}
	fclose(fptr);
	return word_id;
}

// sắp xếp các từ theo thứ tự bảng chữ cái
void sort(char word[][20], int xuat_hien[], char dong_xuat_hien[][100], int word_id) {
	char tmp_str[100];
	int tmp_int;

	for (int i = 0; i < word_id - 1; i++)
		for (int j = i + 1; j < word_id; j++)
			if (strcmp(word[i], word[j]) > 0) {
				strcpy(tmp_str, word[i]);
				strcpy(word[i], word[j]);
				strcpy(word[j], tmp_str);

				tmp_int = xuat_hien[i];
				xuat_hien[i] = xuat_hien[j];
				xuat_hien[j] = tmp_int;

				strcpy(tmp_str, dong_xuat_hien[i]);
				strcpy(dong_xuat_hien[i], dong_xuat_hien[j]);
				strcpy(dong_xuat_hien[j], tmp_str);
			}
}

int main() {
	char stopw_ar[17][5];	// mảng lưu từ không có nghĩa
	char word[1000][20];	// mảng lưu từ
	int xuat_hien[1000];	// số lần xuất hiện
	char dong_xuat_hien[1000][100];		// các dòng mà từ xuất hiện

	read_stopw(stopw_ar);	// đọc file stopw.txt
	/*for (int i = 0; i < 17; i++)
		printf("%s\n", stopw_ar[i]);*/

	int word_id = read_vanban(stopw_ar, word, xuat_hien, dong_xuat_hien);	// đọc file văn bản

	sort(word, xuat_hien, dong_xuat_hien, word_id);		// sắp xếp các từ theo thứ tự bảng chữ cái

	for (int i = 0; i < word_id; i++) {
		//dong_xuat_hien[i][strlen(dong_xuat_hien[i]) - 1] = '\0';	// bỏ dấu phẩy ở cuối xâu
		printf("%d. %s %d %s\n", i, word[i], xuat_hien[i], dong_xuat_hien[i]);		// in ra kết quả
	}
	return 0;
}