/* Sly 2 decomp: basic types (shared with the Sly 1 decomp conventions). */
#ifndef COMMON_H
#define COMMON_H
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;     /* 64-bit on the EE */
typedef int sint;
#ifndef NULL
#define NULL 0
#endif
#define STRUCT_OFFSET(p, off, type) (*(type *)((byte *)(p) + (off)))
#endif
