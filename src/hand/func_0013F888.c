/* class: an LOSINK (the loaders' object sink: LoadProxyFromBrx takes one; LoadSwFromBrx / LoadExplgFromBrx /
 * LoadProxyFromBrx build this kind on the stack): the constructor of the pointer-array sink (vtable 0x2CBE50, its
 * slot 1 0x13F8A8 adds an object) - empty. */
typedef struct LO LO;
typedef struct LOSINKA {
    /* 0x0 */ void *pvt;
    /* 0x4 */ int cMax;
    /* 0x8 */ int c;
    /* 0xc */ LO **aplo;
} LOSINKA;

extern char D_002CBE50[];   /* its vtable */

LOSINKA *func_0013F888(LOSINKA *plosink)
{
    plosink->cMax = 0;
    plosink->pvt = D_002CBE50;
    plosink->c = 0;
    plosink->aplo = 0;
    return plosink;
}
