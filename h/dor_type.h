/* dor_type.h : door类型定义头文件 */

#ifndef _DOR_TYPE_H_
#define _DOR_TYPE_H_

#include "dor_config.h"


/********************************************************************************
 * 基本类型定义
 ********************************************************************************/
typedef unsigned char       DOR_BOOL;

typedef signed   char       DOR_S8;
typedef unsigned char       DOR_U8;

typedef signed   short      DOR_S16;
typedef unsigned short      DOR_U16;

typedef signed   int        DOR_S32;
typedef unsigned int        DOR_U32;

typedef signed   long long  DOR_S64;
typedef unsigned long long  DOR_U64;

typedef float               DOR_F32;
typedef double              DOR_F64;


#if     DOR_CPU_BITS == 8
#define DOR_SIZE            DOR_U8
#define DOR_INTPTR          DOR_U8
#define DOR_ARG             DOR_U8
#define DOR_ALIGN           0
#elif   DOR_CPU_BITS == 16
#define DOR_SIZE            DOR_U16
#define DOR_INTPTR          DOR_U16
#define DOR_ARG             DOR_U16
#define DOR_ALIGN           0x1
#elif   DOR_CPU_BITS == 32
#define DOR_SIZE            DOR_U32
#define DOR_INTPTR          DOR_U32
#define DOR_ARG             DOR_U32
#define DOR_ALIGN           0x3
#elif   DOR_CPU_BITS == 64
#define DOR_SIZE            DOR_U64
#define DOR_INTPTR          DOR_U64
#define DOR_ARG             DOR_U64
#define DOR_ALIGN           0x7
#else
#error 'DOR_CPU_BITS' defined error!
#endif


#ifndef NULL
#define NULL                (void *)0
#endif
#ifndef TRUE
#define TRUE                1
#endif
#ifndef FALSE
#define FALSE               0
#endif

typedef void                (*VOIDFUNC)(void);
/********************************************************************************/


/********************************************************************************
 * 获取数组长度
 ********************************************************************************/
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)       (sizeof(a)/sizeof((a)[0]))
#endif

/* 获取最大值 */
#ifndef MAX
#define MAX(a, b)           (((a) > (b))? (a) : (b))
#endif

/* 获取最小值 */
#ifndef MIN
#define MIN(a, b)           (((a) < (b))? (a) : (b))
#endif

/* 交换两个变量 */
#ifndef SWAP
#define SWAP(a, b)          ((a) ^= (b) ^= (a) ^= (b))
#endif

/* 结构中成员偏移 */
#ifndef OFFSET_OF
#define OFFSET_OF(t, m)     ((int)&(((t *)0)->m))
#endif

/* 结构中成员大小 */
#ifndef SIZE_OF
#define SIZE_OF(t, m)       (sizeof(((t *)0)->m))
#endif

/* 通过成员获取结构体指针 */
#ifndef CONTAINER_OF
#define CONTAINER_OF(p, t, m) ((p)?((t *)((char *)p - OFFSET_OF(t, m))):0)
#endif

/* 按CPU位宽对齐 */
#if DX_CPU_BITS == 8
#define ALIGN_OF(v)         (v)
#else
#define ALIGN_OF(v)         (((v)&DX_ALIGN)?(((v)&(~DX_ALIGN))+(DX_ALIGN+1)):(v))
#endif


/********************************************************************************
 * 日志打印接口
 ********************************************************************************/
typedef void  (*LOG_PRINT)(const char *info, void *para);
typedef void *  LOG_PARA;


#endif /* #ifndef _DOR_TYPE_H_ */
