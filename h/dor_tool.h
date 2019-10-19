/* dor_tool.h : door工具头文件 */

#ifndef _DOR_TOOL_H_
#define _DOR_TOOL_H_


#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************************
 * 拷贝字符串
 ********************************************************************************/
#ifndef DOR_STR_N_CPY                                           /* 安全拷贝字符串 */
#define DOR_STR_N_CPY(dst, src, max)                            \
    do {                                                        \
        char *__d = (dst); const char *__s = (src);             \
        while (__d && __s && *__s && (!(max) ||                 \
               __d < ((dst) + (max) - 1))) {                    \
            *__d++ = *__s++;                                    \
        }                                                       \
        if (__d) *__d = '\0';                                   \
    } while (0)
#endif


/********************************************************************************
 * 比较字符串
 ********************************************************************************/
#ifndef DOR_STR_N_CMP                                           /* 安全拷贝字符串 */
#define DOR_STR_N_CMP(r, dst, src, max)                         \
    do {                                                        \
        char *__d = (dst); const char *__s = (src);             \
        while (__d && *__d && __s && *__s && (!(max) ||         \
               __d < ((dst) + (max) - 1)) &&                    \
             (*__d == *__s)) {                                  \
             ++__d; ++__s;                                      \
        }                                                       \
        if (!__d)  { r = (!__s)? 0 : -1; break; }               \
        if (!__s)  { r = 1; break; }                            \
        if (*__d > *__s) { r = 1;  break; }                     \
        if (*__d < *__s) { r = -1; break; }                     \
        r = 0;                                                  \
    } while (0)
#endif


/********************************************************************************
 * 双向链表操作
 ********************************************************************************/
#ifndef DOR_DLL_HEAD                                            /* 表头 */
#define DOR_DLL_HEAD(type)                                      \
    type * __first;                                             \
    type * __final;                                             \
    int    __count
#endif
#ifndef DOR_DLL_NODE                                            /* 表节点 */
#define DOR_DLL_NODE(type)                                      \
    type *__next;                                               \
    type *__prev
#endif
#ifndef DOR_DLL_FIRST                                           /* 开头 */
#define DOR_DLL_FIRST(head)      ((head)->__first)
#endif
#ifndef DOR_DLL_FINAL                                           /* 最后 */
#define DOR_DLL_FINAL(head)      ((head)->__final)
#endif
#ifndef DOR_DLL_COUNT                                           /* 数量 */
#define DOR_DLL_COUNT(head)      ((head)->__count)
#endif
#ifndef DOR_DLL_PREV                                            /* 前一个节点 */
#define DOR_DLL_PREV(node)       ((node)->__prev)
#endif
#ifndef DOR_DLL_NEXT                                            /* 下一个节点 */
#define DOR_DLL_NEXT(node)       ((node)->__next)
#endif
#ifndef DOR_DLL_EMPTY                                           /* 是否为空 */
#define DOR_DLL_EMPTY(head)      (!DOR_DLL_FIRST(head) || !DOR_DLL_FINAL(head) || !DOR_DLL_COUNT(head))
#endif
#ifndef DOR_DLL_INIT                                            /* 初始化头 */
#define DOR_DLL_INIT(head)                                      \
    do {                                                        \
        DOR_DLL_FIRST(head) = 0;                                \
        DOR_DLL_FINAL(head)  = 0;                               \
        DOR_DLL_COUNT(head) = 0;                                \
    } while (0)
#endif
#ifndef DOR_DLL_NODE_INIT                                       /* 初始化节点 */
#define DOR_DLL_NODE_INIT(node)                                 \
    do {                                                        \
        DOR_DLL_NEXT(node) = 0;                                 \
        DOR_DLL_PREV(node) = 0;                                 \
    } while (0)
#endif
#ifndef DOR_DLL_INSERT                                          /* 插入 */
#define DOR_DLL_INSERT(head, node, where)                       \
    do {                                                        \
        if (DOR_DLL_EMPTY(head)) {                              \
            DOR_DLL_NEXT(node) = 0;                             \
            DOR_DLL_PREV(node) = 0;                             \
            DOR_DLL_FIRST(head) = (node);                       \
            DOR_DLL_FINAL(head) = (node);                       \
        } else if (!(where)) {                                  \
            DOR_DLL_NEXT(node) = DOR_DLL_FIRST(head);           \
            DOR_DLL_PREV(node) = 0;                             \
            DOR_DLL_PREV(DOR_DLL_FIRST(head)) = (node);         \
            DOR_DLL_FIRST(head) = (node);                       \
        } else {                                                \
            DOR_DLL_NEXT(node) = DOR_DLL_NEXT(where);           \
            DOR_DLL_PREV(node) = (where);                       \
            if (DOR_DLL_NEXT(where))                            \
                DOR_DLL_PREV(DOR_DLL_NEXT(where)) = (node);     \
            DOR_DLL_NEXT(where) = (node);                       \
            if ((where) == DOR_DLL_FINAL(head))                 \
                DOR_DLL_FINAL(head) = (node);                   \
        }                                                       \
        DOR_DLL_COUNT(head)++;                                  \
    } while (0)
#endif
#ifndef DOR_DLL_REMOVE                                          /* 移除 */
#define DOR_DLL_REMOVE(head, node)                              \
    do {                                                        \
        if (DOR_DLL_EMPTY(head)) break;                         \
        if (DOR_DLL_NEXT(node))                                 \
            DOR_DLL_PREV(DOR_DLL_NEXT(node)) = DOR_DLL_PREV(node); \
        if (DOR_DLL_PREV(node))                                 \
            DOR_DLL_NEXT(DOR_DLL_PREV(node)) = DOR_DLL_NEXT(node); \
        if (DOR_DLL_FIRST(head) == (node))                      \
            DOR_DLL_FIRST(head) = DOR_DLL_NEXT(node);           \
        if (DOR_DLL_FINAL(head) == (node))                      \
            DOR_DLL_FINAL(head) = DOR_DLL_PREV(node);           \
        DOR_DLL_NEXT(node) = 0;                                 \
        DOR_DLL_PREV(node) = 0;                                 \
        DOR_DLL_COUNT(head)--;                                  \
    } while (0)
#endif
#ifndef DOR_DLL_CLEAR                                           /* 清除 */
#define DOR_DLL_CLEAR(head, type, free)                         \
    do {                                                        \
        type *__node_loop = DOR_DLL_FIRST(head);                \
        while (__node_loop) {                                   \
            type *__node_free = __node_loop;                    \
            __node_loop = DOR_DLL_NEXT(__node_loop);            \
            free(__node_free);                                  \
        }                                                       \
        DOR_DLL_INIT(head);                                     \
    } while (0)
#endif


#ifdef __cplusplus
}
#endif


#endif /* #ifndef _DOR_TOOL_H_ */
