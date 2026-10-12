/* Prelude for raw m2c --valid-syntax output (auto-matching pass). */
#ifndef M2C_PRELUDE_H
#define M2C_PRELUDE_H
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long s64;               /* EE gcc: long is 64-bit */
typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
typedef float f32;
typedef double f64;
#ifndef NULL
#define NULL 0
#endif
#include "m2c_macros.h"
#endif
