/* test_lex.c : 测试词法分析实现文件 */

#include "test.h"
#include "../src/parser/dor_lex.h"


static LOG_PRINT dor_log_print = NULL;
static LOG_PARA  dor_log_para  = NULL;
static DOR_LEX_CONTEXT dor_lex_context;


static DOR_ERR dor_lex_cb(DOR_LEX_CONTEXT *t, 
        DOR_LEX_TYPE y, DOR_LEX_STAT a, 
        const char *s, DOR_U32 b, DOR_U32 e, 
        void *para) {
    char info[256];
    if (e <= b) {
        sprintf(info, "lex pos err! (%d->%d)\n", b, e);
        if (dor_log_print) dor_log_print(info, dor_log_para);
        return DOR_FAIL;
    }

    DOR_U32 l = e - b;
    char *p = (char *)malloc(l + 1);
    DOR_STR_N_CPY(p, s + b, l);
    p[l] = '\0';
    sprintf(info, "lex type:%d | stat:%d | %s \n", y, a, p);
    if (dor_log_print) dor_log_print(info, dor_log_para);
    return DOR_OK;
}


DOR_TEST_CASE(lex) {
    char info[256];

    dor_log_print = print;
    dor_log_para  = para;

    DOR_ERR r = dor_lex_init(&dor_lex_context);
    if (r != DOR_OK) {
        sprintf(info, "lex init err! (0x%x)\n", r);
        return DOR_FAIL;
    }

    dor_lex_set_proc(dor_lex_cb, NULL);

#define __CHECK(s) \
    do { \
        r = dor_lex_parse(&dor_lex_context, s); \
        if (r != DOR_OK) { \
            sprintf(info, "lex parse err! (0x%x)\n", r); \
            return DOR_FAIL; \
        } \
    } while (0)


    __CHECK("var a = 'test'");


#undef __CHECK

    return DOR_OK;
}
