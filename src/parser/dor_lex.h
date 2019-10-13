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
    DOR_LEX_STAT_ZERO,                      /* 0状态 */
    DOR_LEX_STAT_NUM,                       /* 数字状态 */
    DOR_LEX_STAT_HEX_X,                     /* 十六进制分割x状态 */
    DOR_LEX_STAT_HEX,                       /* 十六进制状态 */
    DOR_LEX_STAT_BIN_B,                     /* 二进制分割b状态 */
    DOR_LEX_STAT_BIN,                       /* 二进制状态 */
    DOR_LEX_STAT_FLOAT_DOT,                 /* 浮点数分割.状态 */
    DOR_LEX_STAT_FLOAT,                     /* 浮点数状态 */
    DOR_LEX_STAT_DOT,                       /* 点状态 */
    DOR_LEX_STAT_STR_QUOT,                  /* 字符串引号状态 */
    DOR_LEX_STAT_STR,                       /* 字符串状态 */
    DOR_LEX_STAT_SPACE,                     /* 空白状态 */
    DOR_LEX_STAT_SYMBOL,                    /* 符号状态 */
    DOR_LEX_STAT_ESCAPE,                    /* 转义状态 */
    DOR_LEX_STAT_UNKNOWN,                   /* 未知状态 */
    DOR_LEX_STAT_ERROR,                     /* 错误状态 */

    DOR_LEX_STAT_COUNT
} DOR_LEX_STAT;


/* 词法状态对应的名称 */
#define DOR_LEX_STAT_NAME_LIST \
    {DOR_LEX_STAT_INIT,        "init"}, \
    {DOR_LEX_STAT_FINISH,      "finish"}, \
    {DOR_LEX_STAT_LEX,         "lex"}, \
    {DOR_LEX_STAT_ZERO,        "zero"}, \
    {DOR_LEX_STAT_NUM,         "num"}, \
    {DOR_LEX_STAT_HEX_X,       "hex_x"}, \
    {DOR_LEX_STAT_HEX,         "hex"}, \
    {DOR_LEX_STAT_BIN_B,       "bin_b"}, \
    {DOR_LEX_STAT_BIN,         "bin"}, \
    {DOR_LEX_STAT_FLOAT_DOT,   "f_dot"}, \
    {DOR_LEX_STAT_FLOAT,       "float"}, \
    {DOR_LEX_STAT_DOT,         "dot"}, \
    {DOR_LEX_STAT_STR_QUOT,    "s_quot"}, \
    {DOR_LEX_STAT_STR,         "str"}, \
    {DOR_LEX_STAT_SPACE,       "space"}, \
    {DOR_LEX_STAT_SYMBOL,      "symbol"}, \
    {DOR_LEX_STAT_ESCAPE,      "escape"}, \
    {DOR_LEX_STAT_UNKNOWN,     "unknown"}, \
    {DOR_LEX_STAT_ERROR,       "error"}


/* 词法类型 */
typedef enum DOR_LEX_TYPE_E {
    DOR_LEX_TYPE_NULL = 0,

    DOR_LEX_TYPE_CTRL,                      /* 控制 */
    DOR_LEX_TYPE_LEX,                       /* 词 */
    DOR_LEX_TYPE_INT,                       /* 整数 */
    DOR_LEX_TYPE_FLOAT,                     /* 浮点数 */
    DOR_LEX_TYPE_STR,                       /* 字符串 */

    DOR_LEX_TYPE_COUNT
} DOR_LEX_TYPE;


/* 词法类型对应的名称 */
#define DOR_LEX_TYPE_NAME_LIST \
    {DOR_LEX_TYPE_CTRL,  "ctrl"}, \
    {DOR_LEX_TYPE_LEX,   "lex"}, \
    {DOR_LEX_TYPE_INT,   "int"}, \
    {DOR_LEX_TYPE_FLOAT, "float"}, \
    {DOR_LEX_TYPE_STR,   "str"}


/* 词法状态对应的处理 */
#define DOR_LEX_STAT_PROC_LIST \
    {DOR_LEX_STAT_INIT,         dor_lex_stat_init}, \
    {DOR_LEX_STAT_FINISH,       dor_lex_stat_finish}, \
    {DOR_LEX_STAT_LEX,          dor_lex_stat_lex}, \
    {DOR_LEX_STAT_ZERO,         dor_lex_stat_zero}, \
    {DOR_LEX_STAT_NUM,          dor_lex_stat_num}, \
    {DOR_LEX_STAT_HEX_X,        dor_lex_stat_hex_x}, \
    {DOR_LEX_STAT_HEX,          dor_lex_stat_hex}, \
    {DOR_LEX_STAT_BIN_B,        dor_lex_stat_bin_b}, \
    {DOR_LEX_STAT_BIN,          dor_lex_stat_bin}, \
    {DOR_LEX_STAT_FLOAT_DOT,    dor_lex_stat_float_dot}, \
    {DOR_LEX_STAT_FLOAT,        dor_lex_stat_float}, \
    {DOR_LEX_STAT_DOT,          dor_lex_stat_dot}, \
    {DOR_LEX_STAT_STR_QUOT,     dor_lex_stat_str_quot}, \
    {DOR_LEX_STAT_STR,          dor_lex_stat_str}, \
    {DOR_LEX_STAT_SPACE,        dor_lex_stat_space}, \
    {DOR_LEX_STAT_UNKNOWN,      dor_lex_stat_unkown}


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
    {'\'',  '\0',   DOR_LEX_STAT_STR_QUOT}, \
    {'\"',  '\0',   DOR_LEX_STAT_STR_QUOT}, \
    {'.',   '\0',   DOR_LEX_STAT_DOT}, \
    {'_',   '\0',   DOR_LEX_STAT_LEX}, \
    {'$',   '\0',   DOR_LEX_STAT_LEX}, \
    {'\\',  '\0',   DOR_LEX_STAT_ESCAPE}


/* 词法分析上下文 */
typedef struct DOR_LEX_CONTEXT_S {
    DOR_U32 state;                          /* 状态 */
    DOR_U32 index;                          /* 索引 */
    DOR_U32 line;                           /* 行号 */
    DOR_U32 col;                            /* 列号 */
    DOR_U32 line_index;                     /* 行对应的索引 */
} DOR_LEX_CONTEXT;


/* 初始化 */
extern DOR_ERR dor_lex_init(DOR_LEX_CONTEXT *t);

/* 解析 */
extern DOR_ERR dor_lex_parse(DOR_LEX_CONTEXT *t, const char *s);


/* 词法状态对应的名称 */
typedef struct DOR_LEX_STAT_NAME_S {
    DOR_LEX_STAT stat;
    const char * name;
} DOR_LEX_STAT_NAME;
extern DOR_ERR      dor_lex_set_stat_name(DOR_LEX_STAT_NAME *list, DOR_U32 count);
extern const char * dor_lex_get_stat_name(DOR_LEX_STAT stat);
extern DOR_LEX_STAT dor_lex_get_stat_value(const char *name);


/* 词法类型对应的名称 */
typedef struct DOR_LEX_TYPE_NAME_S {
    DOR_LEX_TYPE type;
    const char * name;
} DOR_LEX_TYPE_NAME;
extern DOR_ERR      dor_lex_set_type_name(DOR_LEX_TYPE_NAME *list, DOR_U32 count);
extern const char * dor_lex_get_type_name(DOR_LEX_TYPE type);
extern DOR_LEX_TYPE dor_lex_get_type_value(const char *name);


/* 词法状态对应的处理 */
typedef DOR_ERR (*DOR_LEX_STAT_FUNC) (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
typedef struct DOR_LEX_STAT_PROC_S {
    DOR_LEX_STAT        stat;
    DOR_LEX_STAT_FUNC   func;
} DOR_LEX_STAT_PROC;
extern DOR_ERR           dor_lex_set_stat_proc(DOR_LEX_STAT_PROC *list, DOR_U32 count);
extern DOR_LEX_STAT_FUNC dor_lex_get_stat_proc(DOR_LEX_STAT stat);


/* 字符集对应的词法状态 */
typedef struct DOR_LEX_CHR_STAT_S {
    char         begin;                     /* 开始字符 */
    char         end;                       /* 结束字符 */
    DOR_LEX_STAT state;                     /* 对应状态 */
} DOR_LEX_CHR_STAT;
extern DOR_ERR      dor_lex_set_stat_chr(DOR_LEX_CHR_STAT *list, DOR_U32 count);
extern DOR_LEX_STAT dor_lex_get_stat_chr(char c);


/* 词法状态入口 */
extern DOR_ERR dor_lex_stat_init       (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_finish     (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_lex        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_zero       (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_num        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_hex_x      (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_hex        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_bin_b      (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_bin        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_float_dot  (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_float      (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_dot        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_str_quot   (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_str        (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_space      (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);
extern DOR_ERR dor_lex_stat_unkown     (DOR_LEX_CONTEXT *t, const char *s, DOR_U32 i);


/* 状态变化 */
extern DOR_ERR dor_lex_stat_change(DOR_LEX_CONTEXT *t, 
    DOR_LEX_TYPE y, DOR_LEX_STAT a, 
    const char *s, DOR_U32 i);


/* 分词后的处理函数 */
typedef DOR_ERR (*DOR_LEX_PROC_FUNC)(DOR_LEX_CONTEXT *t, 
    DOR_LEX_TYPE y, DOR_LEX_STAT a, 
    const char *s, DOR_U32 i, 
    void *para);
extern void dor_lex_set_proc(DOR_LEX_PROC_FUNC func, void *para);



#ifdef __cplusplus
}
#endif


#endif /* #ifndef _DOR_LEX_H_ */
