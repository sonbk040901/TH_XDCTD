/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __TOKEN_H__
#define __TOKEN_H__

#define MAX_IDENT_LEN 15
#define KEYWORDS_COUNT 20

typedef enum
{
  TK_NONE,   // Token không xác định
  TK_IDENT,  // Token định danh  vd: tên biến, tên hàm,...
  TK_NUMBER, // Token chữ số  vd: 123
  TK_CHAR,   // Token ký tự hằng vd: 'a', 'b', 'c',...
  TK_EOF,    // Token kết thúc file

  KW_PROGRAM,   // Từ khóa
  KW_CONST,     // Từ khóa
  KW_TYPE,      // Từ khóa
  KW_VAR,       // Từ khóa
  KW_INTEGER,   // Từ khóa
  KW_CHAR,      // Từ khóa
  KW_ARRAY,     // Từ khóa
  KW_OF,        // Từ khóa
  KW_FUNCTION,  // Từ khóa
  KW_PROCEDURE, // Từ khóa
  KW_BEGIN,     // Từ khóa
  KW_END,       // Từ khóa
  KW_CALL,      // Từ khóa
  KW_IF,        // Từ khóa
  KW_THEN,      // Từ khóa
  KW_ELSE,      // Từ khóa
  KW_WHILE,     // Từ khóa
  KW_DO,        // Từ khóa
  KW_FOR,       // Từ khóa
  KW_TO,        // Từ khóa

  SB_SEMICOLON, // Dấu chấm phẩy ';'
  SB_COLON,     // Dấu hai chấm ':'
  SB_PERIOD,    // Dấu chấm '.'
  SB_COMMA,     // Dấu phẩy ','
  SB_ASSIGN,    // Dấu bằng(dùng để gán) ':='
  SB_EQ,        // Dấu bằng(dùng để so sánh bằng) '='
  SB_NEQ,       // Dấu khác(Dùng để so sánh khác) '!='
  SB_LT,        // Dấu bé hơn(dùng trong so sánh) '<'
  SB_LE,        // Dấu bé hơn hoặc bằng(dùng trong so sánh) '<='
  SB_GT,        // Dấu lớn hơn(dùng trong so sánh) '>'
  SB_GE,        // Dấu lớn hơn hoặc bằng(dùng trong so sánh) '>='
  SB_PLUS,      // Toán tử cộng(dùng trong tính toán) '+'
  SB_MINUS,     // Toán tử trừ(dùng trong tính toán) '-'
  SB_TIMES,     // Toán tử nhân(dùng trong tính toán) '*'
  SB_SLASH,     // Toán tử chia(dùng trong tính toán) '/'
  SB_LPAR,      // Dấu mở ngoặc '('
  SB_RPAR,      // Dấu đóng ngoặc ')'
  SB_LSEL,      // '<.'
  SB_RSEL       // '.>'
} TokenType;

typedef struct
{
  char string[MAX_IDENT_LEN + 1]; // Mảng chứa giá trị của token(Định danh, số)
  int lineNo, colNo;              // Vị trí của token
  TokenType tokenType;
  int value; // Giá trị của token(Nếu là token number)
} Token;

// Kiểm tra xem string có phải là tên của một từ khóa hay không
// Nếu đúng trả về TokenType của từ khóa
// Nếu không trả về TK_NONE
TokenType checkKeyword(char *string);

// Trả về con trỏ chứa token được tạo mới
// Với kiểu token, vị trí được truyền vào
Token *makeToken(TokenType tokenType, int lineNo, int colNo);

#endif
