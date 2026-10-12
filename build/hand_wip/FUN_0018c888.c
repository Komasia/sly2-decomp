/* WIP: one extra callee-saved reg: gcc CSEs the hi part of D_002E6500 across strcpy and join; target re-lui. */
struct D { char data[0x40]; };
struct O { char data[0x5C]; };
struct S { int x0; int x4; char pad[0xFD5C - 8]; char xFD5C[1]; };
extern char D_002E6500[];
extern struct D D_002E6080[];
unsigned int strlen(const char *s);
char *strcpy(char *d, const char *s);
void *func_002333B4(void *p, int c, unsigned int n);
int func_002446F0(int a, int b, char *c, int d, int e, struct D *f);
int func_001AB098(void *p, int a, int b, int *c);
void func_001AA9B8(struct D *d, struct O *o);
int FUN_0018c888(struct S *s, char *name, int cnt, struct O *out, int *pn)
{
    int fAll;
    struct D *pd;
    int r;
    int i;
    if (cnt >= 0x13)
        return 0x25;
    if (name) {
        if (strlen(name) > 0x40)
            return 0xD;
        strcpy(D_002E6500, name);
        fAll = 0;
    } else {
        fAll = 1;
    }
    name = D_002E6500;
    pd = D_002E6080;
    func_002333B4(pd, 0, 0x480);
    r = func_001AB098(s->xFD5C, func_002446F0(s->x0, s->x4, name, fAll, cnt, pd), 0xD, pn);
    if (r)
        return r;
    for (i = 0; i < *pn; i++)
        func_001AA9B8(&pd[i], &out[i]);
    return 0;
}
