typedef struct S {
    char pad0[0x10];
    char *pb;      /* 0x10 */
    int cb;        /* 0x14 */
    char pad18[0x34 - 0x18];
    int cbSpool;   /* 0x34 */
    char *abSpool; /* 0x38 */
    int pad3c;
    int x40;
    int x44;
    int x48;
    int x4c;
    int x50;
    int x54;
    int x58;
    int x5c;
    int x60;
} S;

extern int func_00242810(void);
extern int func_00241E88(int);
extern int func_00242AE0(void);
extern void func_0014BC78(int isector, int csector, void *pv, int mode);

static __inline__ int Min(int a, int b) { return a < b ? a : b; }
void func_001849A0(S *p)
{
    int cbuf;
    int n;

    p->pb += p->cb;
    p->cb = 0;
    cbuf = p->cbSpool / p->x54;



    if (cbuf > 0x8000) cbuf &= -0x8000; else cbuf &= -0x800;



    if (p->x58 > 0) {
        n = p->x5c + 1;
        if (p->pb == p->abSpool + n * cbuf) {

            p->x5c = n % p->x54;
            p->x58--;

            p->pb = p->abSpool + p->x5c * cbuf;
        }
    }

    do {
        if (p->x44 > 0) {

            int t = Min(func_00242810() + p->x4c, p->x44);

            if (p->x40 < t) {
                p->x40 = t;
            } else if (func_00241E88(1) == 0) {
                if (func_00242AE0() == 0) {
                    int c = p->x44;
                    p->x40 = c;
                    p->x50 += c / 0x800;
                    p->x48 -= c;
                    p->x44 = 0;
                    p->x4c = 0;
                } else {
                    int c = p->x40;
                    p->x4c = c;
                    func_0014BC78(p->x50 + c / 0x800, ((p->x44 - c + 0x7FF) & -0x800) >> 11,
                                  p->abSpool + p->x60 * cbuf + c, 0);
                }
            }
        }

        if (p->x58 < p->x54 && p->x44 == 0 && p->x48 > 0) {

            int c = Min(p->x48, cbuf);

            p->x40 = 0;
            p->x44 = c;
            p->x60 = (p->x60 + 1) % p->x54;
            p->x58++;

            func_0014BC78(p->x50, ((c + 0x7FF) & -0x800) >> 11, p->abSpool + p->x60 * cbuf, 0);
        }

        if (p->x58 == 0) {
            p->cb = 0;
        } else {
            int c = (p->x58 == 1) ? p->x40 : cbuf;
            int v = c - (p->pb - (p->abSpool + p->x5c * cbuf));


            p->cb = Min(v, 0x1000);


        }
    } while (p->cb == 0 && p->x48 > 0);
}
