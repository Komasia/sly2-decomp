/* class: CFileLocation (see 0x258248; the function after StartupCatalog, as Sly 1's FUN_001407A0 "returns the
 * second integer"): the size of a location on the disc (kind 2), else 0. */
typedef struct CFileLocation {
    /* 0x0 */ unsigned int isector;
    /* 0x4 */ unsigned int cb;
    /* 0x8 */ int kind;
} CFileLocation;

unsigned int func_0014B670(CFileLocation *pfl)
{
    unsigned int cb = 0;

    if (pfl->kind == 2) {
        cb = pfl->cb;
    }
    return cb;
}
