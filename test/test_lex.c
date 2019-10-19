/* test_lex.c : 测试词法分析实现文件 */

#include "test.h"
#include "../src/parser/dor_lex.h"


static LOG_PRINT dor_log_print = NULL;
static LOG_PARA  dor_log_para  = NULL;
static DOR_LEX_CONTEXT dor_lex_context;


static DOR_ERR dor_lex_cb(DOR_LEX_CONTEXT *t, 
        DOR_LEX_STAT a, const char *s, DOR_U32 i, 
        void *para) {
    char info[256];
    DOR_U32 b = t->index;
    if (i <= b) {
        snprintf(info, sizeof(info), "lex pos err! (%d->%d)\n", b, i);
        if (dor_log_print) dor_log_print(info, dor_log_para);
        return DOR_FAIL;
    }

    DOR_U32 l = i - b + 1;
    char *p = (char *)malloc(l);
    DOR_STR_N_CPY(p, s + b, l);
    snprintf(info, sizeof(info), "lex state:%02d|%-6s value:%s \n", 
        t->state, dor_lex_get_stat_name(t->state), p);
    if (dor_log_print) dor_log_print(info, dor_log_para);
    free(p);
    return DOR_OK;
}


/*
dump-door:test,"var a=100;if(a==100)console.log('a',a);"
dump-door:test,"var a=102.3;if(a==102.3)console.log('a',a);"
dump-door:test,"var a=00x100f;console.log('a',(a)?a:'null');"
dump-door:test,"var a=0x100f;console.log('a',(a)?a:'null');"
dump-door:test,"var a=0X100f;console.log('a',(a)?a:'null');"
dump-door:test,"var a=00700;console.log('a',(a)?a:'null');"
dump-door:test,"var a=0700;console.log('a',(a)?a:'null');"
dump-door:test,"var a=00b0110;console.log('a',(a)?a:'null');"
dump-door:test,"var a=0b0110;console.log('a',(a)?a:'null');"

*/
DOR_TEST_CASE(lex) {
    char info[256];

    dor_log_print = print;
    dor_log_para  = para;

    DOR_ERR r = dor_lex_init(&dor_lex_context);
    if (r != DOR_OK) {
        snprintf(info, sizeof(info), "lex init err! (errno:0x%x)\n", r);
        if (print) print(info, para);
        return DOR_FAIL;
    }

    dor_lex_set_proc(dor_lex_cb, NULL);

#define __CHECK(s, t) \
    do { \
        snprintf(info, sizeof(info), "-----> '%s' <-----\n", s); \
        if (print) print(info, para); \
        r = dor_lex_parse(&dor_lex_context, s); \
        if (r != DOR_OK) { \
            snprintf(info, sizeof(info), "lex parse err! (errno:0x%x,state:%d|%s',line:%d,col:%d)\n", \
                r, dor_lex_context.state, dor_lex_get_stat_name(dor_lex_context.state), \
                dor_lex_context.line, dor_lex_context.col); \
            if (print) print(info, para); \
            DOR_STR_N_CPY(info, s+dor_lex_context.line_index, MIN(dor_lex_context.col+1, sizeof(info))); \
            if (print) print(info, para); \
            if (t) return DOR_FAIL; \
        } else { \
            if (!t) return DOR_FAIL; \
        } \
    } while (0)


    if (!argc || !argv) {

        __CHECK("var a=100;if(a==100)console.log('a:',a);", TRUE);
        __CHECK("102.3", TRUE);
        __CHECK("00x100f", FALSE);
        __CHECK("0x100f", TRUE);
        __CHECK("0X100f", TRUE);
        __CHECK("0x100g", FALSE);
        __CHECK("0x", FALSE);
        __CHECK("00700", TRUE);
        __CHECK("0700", TRUE);
        __CHECK("00b0110", FALSE);
        __CHECK("0b0110", TRUE);
        __CHECK("0b0121", FALSE);
        __CHECK("0B0110", TRUE);
        __CHECK("0b", FALSE);
        __CHECK(".150", TRUE);
        __CHECK(".a150", TRUE);
        __CHECK(".a150b223", TRUE);
        __CHECK(".150a", FALSE);
        __CHECK(".150(a", TRUE);
        __CHECK(".150 a", TRUE);
        __CHECK("0.150", TRUE);
        __CHECK("00.151", FALSE);
        __CHECK("0.15//abc", TRUE);
        __CHECK("0.15//abc\n*", TRUE);
        __CHECK("0.15/*abc*/", TRUE);
        __CHECK("0.15/*abc*123*def*/", TRUE);
        __CHECK("0.15/*abc*123*def*/*", TRUE);
        __CHECK("0.15/*abc*123*def*", FALSE);

    } else {
            for (int i = 0;i < argc; ++i) {
            __CHECK(argv[i], TRUE);
        }
    }


#undef __CHECK

    return DOR_OK;
}
