struct A { char pad[0x15C]; int x15C; };
struct E { int x0; void *p4; void *p8; };
struct P { char pad[0x2C0]; char a2C0[0x200]; char a4C0[0xF50 - 0x4C0]; char aF50[0x11B4 - 0xF50]; int x11B4; int pad1[2];
    struct A *pa11C0; char pad2[0x12F0 - 0x11C4]; int x12F0; char pad3[0x13D0 - 0x12F4]; int x13D0; char pad4[0x1818 - 0x13D4];
    long x1818; };
extern int D_002DFBC0;
extern char D_002DE2E0[];
int func_001443D8();
int func_0019C8D0(void *pv, int k);
int func_00194558(void *pv, int k);
int func_0019EEF0(void *pv, int k);
struct E *func_00136A28(struct P *p, int k);
int func_00224590(void *pv);
int func_001CADE0(void *pv, int n);
int func_0014FD50(void *pv);
int func_00136870(struct P *p, int k)
{
    int f;
    if (p->x1818 != 0)
        goto fail;
    if (func_001443D8())
        return 0;
    switch (p->x13D0) {
    case 2:
        f = func_0019C8D0(p->a2C0, k);
        goto test;
    case 3:
        f = func_00194558(p->a4C0, k);
        goto test;
    case 13:
        f = func_0019EEF0(p->aF50, k);
    test:
        if (f)
            goto inner;
    default:
    fail:
        return 0;
    case 12:
        if ((unsigned int)(p->x11B4 - 4) < 3) {
            switch (k) {
            case 4: case 7: case 9: case 11: case 13:
                if (p->pa11C0->x15C == k)
                    goto one;
                goto fail;
            }
        }
        goto fail;
    case 0: case 1: case 5: case 7:
    inner:
        switch (k) {
        case 4: case 5: case 7: case 9: case 11: case 13: {
            struct E *pe = func_00136A28(p, k);
            if (pe->p8) {
                if (func_00224590(pe->p8))
                    return 1;
                goto fail;
            }
            if (pe->p4 && func_001CADE0(pe->p4, 2))
                goto one;
            goto fail;
        }
        case 3: {
            int r = 0;
            if (p->x12F0 && (D_002DFBC0 & 2))
                r = func_0014FD50(D_002DE2E0) == 0;
            return r;
        }
        case 1: case 2: case 8: case 10: case 12: case 14:
        one:
            return 1;
        }
        goto fail;
    }
}
