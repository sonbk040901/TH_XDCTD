/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __READER_H__
#define __READER_H__

#define IO_ERROR 0
#define IO_SUCCESS 1
//Đọc một ký tự trong file và lưu vào currentChar
// Khi hoàn thành xong một công việc, phải gọi hàm này để tạo mới cho currentChar để sử dụng cho công việc tiếp theo
int readChar(void);

// Mở file và đọc một ký tự đầu tiên
int openInputStream(char *fileName);

//Đóng file
void closeInputStream(void);

#endif
