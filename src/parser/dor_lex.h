/* dor_lex.h : door词法分析头文件 */

#ifndef _DOR_LEX_H_
#define _DOR_LEX_H_

#include "../../h/door.h"


#ifdef __cplusplus
extern "C" {
#endif


/* 词法状态 */
typedef enum DOR_LEX_STAT_E {
    DOR_LEX_STAT_NULL = 0,

    DOR_LEX_STAT_INIT,                      /* 开始状态 */
    DOR_LEX_STAT_FINISH,                    /* 结束状态 */
    DOR_LEX_STAT_LEX,                       /* 词状态 */
    DOR_LEX_STAT_STR,                       /* 字符串状态 */
    DOR_LEX_STAT_DOT,                       /* 点状态 */
    DOR_LEX_STAT_ZERO,                      /* 0状态 */
    DOR_LEX_STAT_NUM,                       /* 数字状态 */
    DOR_LEX_STAT_HEX_X,                     /* 十六进制分割x状态 */
    DOR_LEX_STAT_HEX,                       /* 十六进制状态 */
    DOR_LEX_STAT_OCT,                       /* 八进制状态 */
    DOR_LEX_STAT_BIN_B,                     /* 二进制分割b状态 */
    DOR_LEX_STAT_BIN,                       /* 二进制状态 */
    DOR_LEX_STAT_FLOAT_DOT,                 /* 浮点数分割.状态 */
    DOR_LEX_STAT_FLOAT,                     /* 浮点数状态 */
    DOR_LEX_STAT_SINGLE_QUOT,               /* 单引号状态 */
    DOR_LEX_STAT_DOUBLE_QUOT,               /* 双引号状态 */
    DOR_LEX_STAT_SPACE,                     /* 空白状态 */
    DOR_LEX_STAT_SYMBOL,                    /* 符号状态 */
    DOR_LEX_STAT_ESCAPE,                    /* 转义状态 */
    DOR_LEX_STAT_UNKNOWN,                   /* 未知状态 */
    DOR_LEX_STAT_ERROR,                     /* 错误状态 */

    DOR_LEX_STAT_COUNT
} DOR_LEX_STAT;
#define DOR_LEX_STAT_NAME_NULL              ""
#define DOR_LEX_STAT_NAME_INIT              "init"
#define DOR_LEX_STAT_NAME_FINISH            "finish"
#define DOR_LEX_STAT_NAME_LEX               "lex"
#define DOR_LEX_STAT_NAME_STR               "str"
#define DOR_LEX_STAT_NAME_DOT               "dot"
#define DOR_LEX_STAT_NAME_ZERO              "zero"
#define DOR_LEX_STAT_NAME_NUM               "num"
#define DOR_LEX_STAT_NAME_HEX_X             "hex_x"
#define DOR_LEX_STAT_NAME_HEX               "hex"
#define DOR_LEX_STAT_NAME_OCT               "oct"
#define DOR_LEX_STAT_NAME_BIN_B             "bin_b"
#define DOR_LEX_STAT_NAME_BIN               "bin"
#define DOR_LEX_STAT_NAME_FLOAT_DOT         "f_dot"
#define DOR_LEX_STAT_NAME_FLOAT             "float"
#define DOR_LEX_STAT_NAME_SINGLE_QUOT       "s_quot"
#define DOR_LEX_STAT_NAME_DOUBLE_QUOT       "d_quot"
#define DOR_LEX_STAT_NAME_SPACE             "space"
#define DOR_LEX_STAT_NAME_SYMBOL            "symbol"
#define DOR_LEX_STAT_NAME_ESCAPE            "escape"
#define DOR_LEX_STAT_NAME_UNKNOWN           "unknown"
#define DOR_LEX_STAT_NAME_ERROR             "error"
extern const char * dor_lex_get_stat_name(DOR_LEX_STAT stat);
extern DOR_LEX_STAT dor_lex_get_stat_value(const char *name);



/* 词法类型 */
typedef enum DOR_LEX_TYPE_E {
    DOR_LEX_TYPE_NULL = 0,

    DOR_LEX_TYPE_CTRL,                      /* 控制 */
    DOR_LEX_TYPE_VAR,                       /* 变量 */
    DOR_LEX_TYPE_INT,                       /* 整数 */
    DOR_LEX_TYPE_FLOAT,                     /* 浮点数 */
    DOR_LEX_TYPE_BOOL,                      /* 布尔值 */
    DOR_LEX_TYPE_STR,                       /* 字符串 */

    DOR_LEX_TYPE_COUNT
} DOR_LEX_TYPE;
#define DOR_LEX_TYPE_NAME_NULL              ""
#define DOR_LEX_TYPE_NAME_CTRL              "ctrl"
#define DOR_LEX_TYPE_NAME_VAR               "var"
#define DOR_LEX_TYPE_NAME_INT               "int"
#define DOR_LEX_TYPE_NAME_FLOAT             "float"
#define DOR_LEX_TYPE_NAME_BOOL              "bool"
#define DOR_LEX_TYPE_NAME_STR               "str"
extern const char * dor_lex_get_type_name(DOR_LEX_TYPE type);
extern DOR_LEX_TYPE dor_lex_get_type_value(const char *name);


/* 词法状态对应的处理 */
#define DOR_LEX_STAT_PROC_LIST \
    {DOR_LEX_STAT_INIT, dor_lex_stat_init}, \
    {DOR_LEX_STAT_FINISH, dor_lex_stat_finish}, \
    {DOR_LEX_STAT_LEX, dor_lex_stat_lex}, \
    {DOR_LEX_STAT_STR, dor_lex_stat_str}, \
    {DOR_LEX_STAT_ZERO, dor_lex_stat_zero}, \
    {DOR_LEX_STAT_NUM, dor_lex_stat_num}, \
    {DOR_LEX_STAT_HEX_X, dor_lex_stat_hex_x}, \
    {DOR_LEX_STAT_HEX, dor_lex_stat_hex}, \
    {DOR_LEX_STAT_BIN_B, dor_lex_stat_bin_b}, \
    {DOR_LEX_STAT_BIN, dor_lex_stat_bin}, \
    {DOR_LEX_STAT_FLOAT_DOT, dor_lex_stat_float_dot}, \
    {DOR_LEX_STAT_FLOAT, dor_lex_stat_float}, \
    {DOR_LEX_STAT_SINGLE_QUOT, dor_lex_stat_single_quot}, \
    {DOR_LEX_STAT_DOUBLE_QUOT, dor_lex_stat_double_quot}, \
    {DOR_LEX_STAT_SPACE, dor_lex_stat_space}, \
    {DOR_LEX_STAT_UNKNOWN, dor_lex_stat_unkown}


/* 字符集对应的词法状态 */
#define DOR_LEX_CHR_STAT_LIST \
    {'\r',  '\0',   DOR_LEX_STAT_SPACE}, \
    {'\n',  '\0',   DOR_LEX_STAT_SPACE}, \
    {'\t',  '\0',   DOR_LEX_STAT_SPACE}, \
    {' ',   '\0',   DOR_LEX_STAT_SPACE}, \
    {'!',   '/',    DOR_LEX_STAT_SYMBOL}, \
    {'0',   '\0',   DOR_LEX_STAT_ZERO}, \
    {'1',   '9',    DOR_LEX_STAT_NUM}, \
    {':',   '@',    DOR_LEX_STAT_SYMBOL}, \
    {'A',   'Z',    DOR_LEX_STAT_LEX}, \
    {'[',   '`',    DOR_LEX_STAT_SYMBOL}, \
    {'a',   'z',    DOR_LEX_STAT_LEX}, \
    {'{',   '~',    DOR_LEX_STAT_SYMBOL}, \
    {'\'',  '\0',   DOR_LEX_STAT_SINGLE_QUOT}, \
    {'\"',  '\0',   DOR_LEX_STAT_DOUBLE_QUOT}, \
    {'.',   '\0',   DOR_LEX_STAT_DOT}, \
    {'_',   '\0',   DOR_LEX_STAT_LEX}, \
    {'$',   '\0',   DOR_LEX_STAT_LEX}, \
    {'\\',  '\0',   DOR_LEX_STAT_ESCAPE}


/* 16进制字符集对应的词法状态 */
#define DOR_LEX_HEX_STAT_LIST \
    {'0',   '9',    DOR_LEX_STAT_HEX}, \
    {'a',   'f',    DOR_LEX_STAT_HEX}, \
    {'A',   'F',    DOR_LEX_STAT_HEX}, \


/* 词法分析上下文 */
typedef struct DOR_LEX_CONTEXT_S {
    DOR_U32 state;                          /* 状态 */
    DOR_U32 index;                          /* 索引 */
    DOR_U32 line;                           /* 行号 */
    DOR_U32 col;                            /* 列号 */
} DOR_LEX_CONTEXT;


/* 初始化 */
extern DOR_ERR dor_lex_init(DOR_LEX_CONTEXT *t);


/* 解析 */
extern DOR_ERR dor_lex_parse(DOR_LEX_CONTEXT *t, const char *s);


/* 词法状态对应的处理 */
typedef DOR_ERR (*DOR_LEX_STAT_FUNC) (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
typedef struct DOR_LEX_STAT_PROC_S {
    DOR_LEX_STAT        stat;
    DOR_LEX_STAT_FUNC   func;
} DOR_LEX_STAT_PROC;
extern DOR_ERR           dor_lex_set_proc_state(DOR_LEX_STAT_PROC *list, DOR_U32 count);
extern DOR_LEX_STAT_FUNC dor_lex_get_proc_state(DOR_LEX_STAT stat);


/* 字符集对应的词法状态 */
typedef struct DOR_LEX_CHR_STAT_S {
    char         begin;                     /* 开始字符 */
    char         end;                       /* 结束字符 */
    DOR_LEX_STAT state;                     /* 对应状态 */
} DOR_LEX_CHR_STAT;
extern DOR_ERR      dor_lex_set_chr_state(DOR_LEX_CHR_STAT *list, DOR_U32 count);
extern DOR_LEX_STAT dor_lex_get_chr_state(char c);
extern DOR_ERR      dor_lex_set_hex_state(DOR_LEX_CHR_STAT *list, DOR_U32 count);
extern DOR_LEX_STAT dor_lex_get_hex_state(char c);


/* 词法状态入口 */
extern DOR_ERR dor_lex_stat_init       (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_finish     (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_lex        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_str        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_zero       (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_num        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_hex_x      (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_hex        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_bin_b      (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_bin        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_float_dot  (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_float      (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_single_quot(DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_double_quot(DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_space      (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_unkown     (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);


/* 状态变化 */
extern DOR_ERR dor_lex_stat_change(DOR_LEX_CONTEXT *t, 
    DOR_LEX_TYPE y, DOR_LEX_STAT a, 
    const char *s, DOR_U32 i);


/* 分词后的处理函数 */
typedef DOR_ERR (*DOR_LEX_PROC_FUNC)(DOR_LEX_CONTEXT *t, 
    DOR_LEX_TYPE y, DOR_LEX_STAT a, 
    const char *s, DOR_U32 b, DOR_U32 e, 
    void *para);
extern void dor_lex_set_proc(DOR_LEX_PROC_FUNC func, void *para);



#ifdef __cplusplus
}
#endif


#endif /* #ifndef _DOR_LEX_H_ */
