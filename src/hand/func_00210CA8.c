/* func_00210CA8 (called by the movie code 0x1B3700): a key's value in a {key, value} table, or the default
 * D_002A8A98 when the key is missing or its value is null. */
typedef struct KV {
    /* 0x0 */ int key;
    /* 0x4 */ void *pv;
} KV;
typedef struct KVTABLE {
    /* 0x0 */ int c;
    /* 0x4 */ KV *akv;
} KVTABLE;
extern char D_002A8A98[];

void *func_00210CA8(KVTABLE *ptable, int key)
{
    void *pv;
    int c;
    int i;
    KV *pkv;

    c = ptable->c;
    i = 0;
    if (c > 0) {
        pkv = ptable->akv;
    loop:
        i++;
        if (key != pkv->key || (pv = pkv->pv) == 0) {
            pkv++;
            if (i >= c) {
                goto none;
            }
            goto loop;
        }
    } else {
    none:
        pv = D_002A8A98;
    }
    return pv;
}
