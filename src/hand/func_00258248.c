/* class: CFileLocation (Sly 1 cat.h FCL {isector, cb}; Sly 2 adds the kind at +0x8, which 0x184D60 / 0x14B670
 * test for 2): cleared - no sector, no size, kind -1, the byte at +0xC 0. */
typedef struct CFileLocation {
    /* 0x0 */ unsigned int isector;
    /* 0x4 */ unsigned int cb;
    /* 0x8 */ int kind;
    /* 0xc */ char b;
} CFileLocation;

void *memset(void *pv, int b, unsigned int cb);

void func_00258248(CFileLocation *pfl)
{
    memset(pfl, 0, 8);
    pfl->b = 0;
    pfl->kind = -1;
}
