/* class: SPAWNER (cid 0x77, SafeHouse spawner.cpp; its loader method 1325, its descriptor 0x2B9788): a source of
 * kind 1 (a path) with the given oid appended to the spawner's sources (+0x54, 0x80 at most). */
#include "h2_spawner.h"

void func_00173318(SPAWNER *pspawner, int oid)
{
    int isrc = pspawner->csrc;

    if (isrc < 0x80) {
        SOURCE *psrc;
        pspawner->csrc = isrc + 1;
        psrc = &pspawner->asrc[isrc];
        psrc->kind = 1;
        psrc->oid = oid;
    }
}
