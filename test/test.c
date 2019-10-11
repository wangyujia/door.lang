/* test.c : 测试实现文件 */

#include "test.h"


/* 测试头 */
DOR_TEST_HEAD dor_test_head;


/* 测试入口 */
DOR_TEST_RESULT *dor_test_main(
    int argc, const char **argv,
    LOG_PRINT print, LOG_PARA para)
{
    DOR_TEST_REG(lex);

    char info[256];
    sprintf(info, "dor_test_main argc:%d\n", argc);
    if (print) print(info, para);
    for (int i = 0; i < argc; ++i) {
        if (print) print(argv[i], para);
    }

    static DOR_TEST_RESULT result;
    result.count  = 0;
    result.failed = 0;
    result.name   = 0;

    DOR_TEST *p = DOR_DLL_FIRST(&dor_test_head);
    while (p) {
        DOR_TEST_FUNC f = p->func;
        const char *nme = p->name;
        sprintf(info, "--------- TEST CASE '%s'|%d ---------\n", nme, result.count);
        if (print) print(info, para);
        result.count++;

        p = DOR_DLL_NEXT(p);
        if (!f) continue;
        int r = f(argc, argv, print, para);
        if (!r) continue;

        result.failed++;
        if (!result.name) result.name = nme;
    }

    return &result;
}
