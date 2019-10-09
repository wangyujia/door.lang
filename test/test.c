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

    static DOR_TEST_RESULT result;
    result.count  = 0;
    result.failed = 0;
    result.name   = 0;

    DOR_TEST *p = DOR_DLL_FIRST(&dor_test_head);
    while (p) {
        result.count++;
        DOR_TEST_FUNC f = p->func;
        const char *nm = p->name;
        p = DOR_DLL_NEXT(p);
        if (!f) continue;

        if (print) print("------------------------------------ \n", para);
        int r = f(argc, argv, print, para);
        if (!r) continue;

        result.failed++;
        if (!result.name) result.name = nm;
    }

    return &result;
}
