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

    DOR_U32 l = e - b + 1;
    char *p = (char *)malloc(l);
    DOR_STR_N_CPY(p, s + b, l);
    p[l - 1] = '\0';
    sprintf(info, "lex type:%d|%-6s state:%02d|%-8s value:%s \n", 
        y, dor_lex_get_type_name(y), 
        a, dor_lex_get_stat_name(a), p);
    if (dor_log_print) dor_log_print(info, dor_log_para);
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
        sprintf(info, "lex init err! (errno:0x%x)\n", r);
        if (print) print(info, para);
        return DOR_FAIL;
    }

    dor_lex_set_proc(dor_lex_cb, NULL);

#define __CHECK(s, t) \
    do { \
        r = dor_lex_parse(&dor_lex_context, s); \
        if (r != DOR_OK) { \
            sprintf(info, "lex parse err! (errno:0x%x,state:%d|%s',line:%d,col:%d)\n", \
                r, dor_lex_context.state, dor_lex_get_stat_name(dor_lex_context.state), \
                dor_lex_context.line, dor_lex_context.col); \
            if (print) print(info, para); \
            if (t) return DOR_FAIL; \
        } else { \
            if (!t) return DOR_FAIL; \
        } \
    } while (0)


    if (!argc || !argv) {

        __CHECK("var a=100;if(a==100)console.log('a',a);", TRUE);
        __CHECK("var a=102.3;if(a==102.3)console.log('a',a);", TRUE);
        __CHECK("var a=00x100f;console.log('a',(a)?a:'null');", FALSE);
        __CHECK("var a=0x100f;console.log('a',(a)?a:'null');", TRUE);
        __CHECK("var a=0X100f;console.log('a',(a)?a:'null');", TRUE);
        __CHECK("var a=00700;console.log('a',(a)?a:'null');", TRUE);
        __CHECK("var a=0700;console.log('a',(a)?a:'null');", TRUE);
        __CHECK("var a=00b0110;console.log('a',(a)?a:'null');", FALSE);
        __CHECK("var a=0b0110;console.log('a',(a)?a:'null');", TRUE);

    } else {
            for (int i = 0;i < argc; ++i) {
            __CHECK(argv[i], TRUE);
        }
    }


#undef __CHECK

    return DOR_OK;
}
