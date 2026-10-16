/* (Claude agent) v2: 16/89, only s0/s1 swap (target p=s0, k=s1). Logic fixed from jump tables 2A7500/2A7560: out-of-range state/k return 0 (old WIP returned 1 / fell through), states 0,1,9,10 continue, k 1,2,15,16,20,21 -> 1; case 5 tail written 'if (k == 19) { if (f()) return 1; } return 0;'. */
struct O { char pad[0x180]; void *x180; };
struct P { char pad[0x2C4]; int x2C4; char pad1[0x12F0 - 0x2C8]; int x12F0; char pad2[0x13D0 - 0x12F4]; int x13D0; char pad3[0x13F0 - 0x13D4]; struct O *x13F0; };
extern int D_002DFBC0;
extern char D_002DE2E0[];
int func_001443D8(struct P *p, int k);
int func_0019C8D0(void *p, int k);
int func_00194558(void *p, int k);
int func_0019EEF0(void *p, int k);
int func_00132B10(void *p, int n);
int func_0014FD50(void *p);
int func_001B98A0(struct P *p, int k)
{
    if (func_001443D8(p, k)) return 0;
    switch (p->x13D0) {
    case 0: case 1: case 9: case 10:
        break;
    case 2:
        if (!func_0019C8D0((char *)p + 0x2C0, k)) return 0;
        break;
    case 13:
        if (!func_00194558((char *)p + 0x4C0, k)) return 0;
        break;
    case 20:
        if (!func_0019EEF0((char *)p + 0xF50, k)) return 0;
        break;
    case 5:
        if (k == 3) return 1;
        if (k == 19) { if (func_00132B10(p->x13F0->x180, 0x38)) return 1; }
        return 0;
    default:
        return 0;
    }
    switch (k) {
    case 3:
    {
        int r = 0;
        if (p->x12F0 && (D_002DFBC0 & 2)) r = !func_0014FD50(D_002DE2E0);
        return r;
    }
    case 22:
    {
        int r = 0;
        if (p->x2C4 != 0 && p->x2C4 != 11) r = p->x2C4 != -1;
        return r;
    }
    case 1: case 2: case 15: case 16: case 20: case 21:
        break;
    default:
        return 0;
    }
    return 1;
}
