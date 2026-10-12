#include "gifs.h"
extern "C" void func_0015F000(void *p, int f, GIFS *pgifs)
{
    if (f) {
        pgifs->AddPrimPack(0, 1, 0xe);
        pgifs->PackAD(0x40, 0xdf000001ff0000L);
    }
}
