#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORDLEN 100

/* 定义符号类型 */
typedef enum {
    nul, plus, minus, times, slash, lparen, rparen, eql, comma, period, neq, semicolon, ident, number, beginsym, callsym, constsym, dosym, endsym, ifsym, oddsym, procsym, readsym, thensym, varsym, whilesym, writesym
} Symbol;

/* 定义符号表 */
Symbol ssym[256];
char word[13][MAXWORDLEN];

/* 初始化符号表 */
void init() {
    int i;

    /* 设置单字符符号 */
    for (i = 0; i <= 255; i++) {
        ssym[i] = nul;
    }
    ssym['+'] = plus;
    ssym['-'] = minus;
    ssym['*'] = times;
    ssym['/'] = slash;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['='] = eql;
    ssym[','] = comma;
    ssym['.'] = period;
    ssym['#'] = neq;
    ssym[';'] = semicolon;

    /* 设置保留字名字 */
    strcpy(&(word[0][0]), "begin");
    strcpy(&(word[1][0]), "call");
    strcpy(&(word[2][0]), "const");
    strcpy(&(word[3][0]), "do");
    strcpy(&(word[4][0]), "end");
    strcpy(&(word[5][0]), "if");
    strcpy(&(word[6][0]), "odd");
    strcpy(&(word[7][0]), "procedure");
    strcpy(&(word[8][0]), "read");
    strcpy(&(word[9][0]), "then");
    strcpy(&(word[10][0]), "var");
    strcpy(&(word[11][0]), "while");
    strcpy(&(word[12][0]), "write");

}

/* 判断字符是否为字母 */
int is_letter(char c) {
    return isalpha(c) || c == '_';
}

/* 判断字符是否为数字 */
int is_digit(char c) {
    return isdigit(c);
}

/* 词法分析器 */
void lexer(const char *input) {
    int i = 0;
    char buffer[MAXWORDLEN];
    int buffer_pos = 0;

    while (input[i] != '\0') {
        if (isspace(input[i])) {
            i++;
            continue;
        }
        if (is_letter(input[i])) {
            buffer_pos = 0;
            while (is_letter(input[i]) || is_digit(input[i])) {
                buffer[buffer_pos++] = input[i++];
            }
            buffer[buffer_pos] = '\0';
            int j;
            for (j = 0; j < 13; j++) {
                if (strcmp(buffer, word[j]) == 0) {
                    printf("(%ssym,%s)\n", word[j], buffer);
                    break;
                }
            }
            if (j == 13) {
                printf("(ident,%s)\n", buffer);
            }
        } else if (is_digit(input[i])) {
            buffer_pos = 0;
            while (is_digit(input[i])) {
                buffer[buffer_pos++] = input[i++];
            }
            buffer[buffer_pos] = '\0';
            printf("(number,%s)\n", buffer);
        } else if (ssym[(unsigned char)input[i]] != nul) {
            Symbol sym = ssym[(unsigned char)input[i]];
            switch (sym) {
                case plus: printf("(plus,+)\n"); break;
                case minus: printf("(minus,-)\n"); break;
                case times: printf("(times,*)\n"); break;
                case slash: printf("(slash,/)\n"); break;
                case lparen: printf("(lparen,()\n"); break;
                case rparen: printf("(rparen,))\n"); break;
                case eql: printf("(eql,=)\n"); break;
                case comma: printf("(comma,,)\n"); break;
                case period: printf("(period,.)\n"); break;
                case neq: printf("(neq,#)\n"); break;
                case semicolon: printf("(semicolon,;)\n"); break;
                default: printf("(unknown,%c)\n", input[i]); break;
            }
            i++;
        } else {
            printf("(unknown,%c)\n", input[i]);
            i++;
        }
    }
}

int main() {
    char input[MAXWORDLEN * 10];  // 增加缓冲区大小以处理较长的输入

    init();

    printf("请输入要分析的字符串：\n");
    fgets(input, sizeof(input), stdin);

    // 删除末尾的换行符
    input[strcspn(input, "\n")] = '\0';

    lexer(input);
    return 0;
}
