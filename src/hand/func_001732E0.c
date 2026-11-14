/* class: SPAWNER (cid 0x77, SafeHouse spawner.cpp; its loader method 1324, its descriptor 0x2B9760): a source of
 * kind 0 (a proxy) with the given oid appended to the spawner's sources (+0x54, 0x80 at most). */
typedef struct SOURCE {          /* field: SafeHouse port (0x1C bytes) */
    /* 0x00 */ int kind;
    /* 0x04 */ int oid;
    /* 0x08 */ void *plo;
    /* 0x0c */ void *plist;
    /* 0x10 */ int pad10;
    /* 0x14 */ int fBusy;
    /* 0x18 */ float tUntil;
} SOURCE;

typedef struct SPAWNER {
    /* 0x00 */ char pad0[0x50];
    /* 0x50 */ int csrc;
    /* 0x54 */ SOURCE *asrc;     /* field: SafeHouse port */
} SPAWNER;

void func_001732E0(SPAWNER *pspawner, int oid)
{
    int isrc = pspawner->csrc;

    if (isrc < 0x80) {
        SOURCE *psrc;
        pspawner->csrc = isrc + 1;
        psrc = &pspawner->asrc[isrc];
        psrc->oid = oid;
        psrc->kind = 0;
    }
}
