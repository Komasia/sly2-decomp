/* class: the file / CD CBinaryInputStream (vtable 0x2D2918): Sly 1's CBinaryInputStream::FOpenFile with a kind test -
 * a file location on the disc (kind 2) opens its sectors (FOpenSector__18CBinaryInputStreamUiUi 0x184D98), any other
 * fails. */
typedef struct CFileLocation {   /* Sly 1 cat.h (FCL), Sly 2 adds the kind (clear: 0x258248) */
    /* 0x0 */ unsigned int isector;
    /* 0x4 */ unsigned int cb;
    /* 0x8 */ int kind;            /* 2: on the disc; -1 none */
} CFileLocation;

int FOpenSector__18CBinaryInputStreamUiUi(void *pbis, unsigned int isector, unsigned int cb);

int func_00184D60(void *pbis, CFileLocation *pfl)
{
    int fOpen = 0;

    if (pfl->kind == 2) {
        fOpen = FOpenSector__18CBinaryInputStreamUiUi(pbis, pfl->isector, pfl->cb);
    }
    return fOpen;
}
