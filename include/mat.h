#ifndef MAT_H
#define MAT_H
#include "vec.h"
/* 3x3 rotation stored as three quadword rows (48 bytes) */
struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16)));
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
#endif
