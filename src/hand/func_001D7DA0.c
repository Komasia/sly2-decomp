typedef struct {
    short ch;
    signed char x2;
    unsigned char x3;
    unsigned short x4;
    unsigned short iChild;
    unsigned short iSibling;
} ENT;
typedef struct { int pad; ENT *ae; } TRIE;
typedef struct { int c; unsigned short *a; } KEY;
typedef struct { ENT *pe; int n; } OUT;
int func_001D7DA0(TRIE *p, KEY *key, OUT *out)
{
    ENT *ae = p->ae;
    ENT *e;
    int i;
    if (ae->iChild == 0)
        return 0;
    e = &ae[ae->iChild];
    out->n = 0;
    i = 0;
    for (;;) {
        if (e->ch == key->a[i]) {
            i++;
            if (i == key->c) {
                out->pe = e;
                return 1;
            }
            if (e->x3) {
                out->pe = e;
                out->n = key->a[i++];
                return i == key->c;
            }
            if (e->x2 != -1)
                return 0;
            if (!e->iChild)
                return 0;
            e = &p->ae[e->iChild];
        } else {
            if (!e->iSibling)
                return 0;
            e = &p->ae[e->iSibling];
        }
    }
}
