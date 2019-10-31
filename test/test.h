/* test.h : 测试头文件 */

#ifndef _TEST_H_
#define _TEST_H_

#include "../h/door.h"

#ifdef __cplusplus
extern "C" {
#endif


/* 测试入口函数原型 */
typedef int (*DOR_TEST_FUNC)(
    int argc, const char **argv,
    LOG_PRINT print, LOG_PARA para);


/* 测试节点类型 */
typedef struct DOR_TEST_S {
    const char *    name;
    DOR_TEST_FUNC   func;
    DOR_DLL_NODE(struct DOR_TEST_S);
} DOR_TEST;


/* 测试头部类型 */
typedef struct DOR_TEST_HEAD_S {
    DOR_DLL_HEAD(DOR_TEST);
} DOR_TEST_HEAD;
extern  DOR_TEST_HEAD dor_test_head;


/* 测试结果 */
typedef struct DOR_TEST_RESULT_S {
    int count;
    int failed;
    const char *name;
} DOR_TEST_RESULT;


/* 测试用例 */
#define DOR_TEST_CASE(func)                                     \
    static int __dor_test_func_##func();                        \
    void __dor_test_reg_##func() {                              \
        static int reg = FALSE;                                 \
        static DOR_TEST __node = {#func,                        \
            __dor_test_func_##func};                            \
        if (!reg) {                                             \
            DOR_DLL_INSERT(&dor_test_head, &__node,             \
                DOR_DLL_FINAL(&dor_test_head));                 \
            reg = TRUE;                                         \
        }                                                       \
    }                                                           \
    static int __dor_test_func_##func(                          \
        int argc, const char **argv,                            \
        LOG_PRINT print, LOG_PARA para)
#define DOR_TEST_REG(func)                                      \
    extern void __dor_test_reg_##func();                        \
    __dor_test_reg_##func();


/* 测试入口 */
extern DOR_TEST_RESULT *dor_test_main(
    int argc, const char **argv,
    LOG_PRINT print, LOG_PARA para);


#ifdef __cplusplus
}
#endif

#endif // #ifndef _TEST_H_
