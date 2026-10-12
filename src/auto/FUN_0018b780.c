#include "m2c_prelude.h"
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
M2C_UNK strcpy(void *, s32);                        /* extern */

void FUN_0018b780(void *arg0, void *arg1) {
    memset(arg1, 0, 0x5C);
    strcpy(arg1, arg0 + 0x20);
    M2C_FIELD(arg1, s32 *, 0x44) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
    if (M2C_FIELD(arg0, u16 *, 0x14) & 1) {
        M2C_FIELD(arg1, s32 *, 0x48) = (s32) (M2C_FIELD(arg1, s32 *, 0x48) | 1);
    }
    if (M2C_FIELD(arg0, u16 *, 0x14) & 2) {
        M2C_FIELD(arg1, s32 *, 0x48) = (s32) (M2C_FIELD(arg1, s32 *, 0x48) | 2);
    }
    if (M2C_FIELD(arg0, u16 *, 0x14) & 4) {
        M2C_FIELD(arg1, s32 *, 0x48) = (s32) (M2C_FIELD(arg1, s32 *, 0x48) | 4);
    }
    if (M2C_FIELD(arg0, u16 *, 0x14) & 8) {
        M2C_FIELD(arg1, s32 *, 0x48) = (s32) (M2C_FIELD(arg1, s32 *, 0x48) | 8);
    }
    if (M2C_FIELD(arg0, u16 *, 0x14) & 0x20) {
        M2C_FIELD(arg1, s32 *, 0x48) = (s32) (M2C_FIELD(arg1, s32 *, 0x48) | 0x10);
    }
    if (M2C_FIELD(arg0, u16 *, 0x14) & 0x80) {
        M2C_FIELD(arg1, s32 *, 0x48) = (s32) (M2C_FIELD(arg1, s32 *, 0x48) | 0x20);
    }
    if (M2C_FIELD(arg0, u16 *, 0x14) & 0x800) {
        M2C_FIELD(arg1, s32 *, 0x48) = (s32) (M2C_FIELD(arg1, s32 *, 0x48) | 0x40);
    }
    if (M2C_FIELD(arg0, u16 *, 0x14) & 0x1000) {
        M2C_FIELD(arg1, s32 *, 0x48) = (s32) (M2C_FIELD(arg1, s32 *, 0x48) | 0x80);
    }
    M2C_FIELD(arg1, u8 *, 0x4A) = (u8) M2C_FIELD(arg0, u8 *, 5);
    M2C_FIELD(arg1, u8 *, 0x4B) = (u8) M2C_FIELD(arg0, u8 *, 4);
    M2C_FIELD(arg1, u16 *, 0x4C) = (u16) M2C_FIELD(arg0, u16 *, 6);
    M2C_FIELD(arg1, u8 *, 0x4E) = (u8) M2C_FIELD(arg0, u8 *, 3);
    M2C_FIELD(arg1, u8 *, 0x4F) = (u8) M2C_FIELD(arg0, u8 *, 2);
    M2C_FIELD(arg1, u8 *, 0x50) = (u8) M2C_FIELD(arg0, u8 *, 1);
    M2C_FIELD(arg1, u8 *, 0x52) = (u8) M2C_FIELD(arg0, u8 *, 0xD);
    M2C_FIELD(arg1, u8 *, 0x53) = (u8) M2C_FIELD(arg0, u8 *, 0xC);
    M2C_FIELD(arg1, u16 *, 0x54) = (u16) M2C_FIELD(arg0, u16 *, 0xE);
    M2C_FIELD(arg1, u8 *, 0x56) = (u8) M2C_FIELD(arg0, u8 *, 0xB);
    M2C_FIELD(arg1, u8 *, 0x57) = (u8) M2C_FIELD(arg0, u8 *, 0xA);
    M2C_FIELD(arg1, u8 *, 0x58) = (u8) M2C_FIELD(arg0, u8 *, 9);
}
