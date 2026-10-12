#ifndef VEC_H
#define VEC_H
#include "common.h"
/* 16-byte (quadword) aligned on the PS2, but only x/y/z are meaningful */
struct VECTOR { float x, y, z; } __attribute__((aligned(16)));
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
#endif
