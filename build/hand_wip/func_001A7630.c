/* WIP: five differences in the DMA chunk minimum and destination address allocation. */
struct E { int cb; int src; int x8; const char *xC; int x10; };
struct DMA { int src; int dst; int size; int x; };
extern struct E *D_004E5D80;
extern struct E *D_004E5E38;
extern int D_002E2058;
extern char D_002A6A48[];
void func_00236A60(int n);
int func_00238F00(void);
int func_002420F0(int n);
int func_0014B9C0(void);
void func_0014BA00(void);
int func_00237E70(void);
void func_0014BBB0(void *p, char *s, int n);
int func_00239340(void *p);
int func_002392F0(void);
int func_002425F0(int n);
void func_0014BD30(int n);
int func_00238BD0(void);
void *func_00238C58(int cb);
void func_00234CA0(int n);
int func_00234DE0(struct DMA *p, int n);
int func_00239140(void *h, int argc, const char *args);
int func_00238D40(void *h);
void func_001A7630(void)
{
    union { char buf[0x100]; struct DMA dma; } u;
    struct E *pe;
    int cbMax;
    void *h;
    func_00236A60(0);
    func_00238F00();
    func_002420F0(0);
    if (!func_0014B9C0())
        while (1)
            ;
    func_0014BA00();
    func_00237E70();
    if (!D_002E2058) {
        func_0014BBB0(u.buf, D_002A6A48, 1);
        while (!func_00239340(u.buf))
            ;
        while (!func_002392F0())
            ;
        func_00236A60(0);
        func_00238F00();
        func_002420F0(0);
        if (!func_0014B9C0())
            while (1)
                ;
        func_0014BA00();
        func_00237E70();
    }
    func_002425F0(0);
    func_0014BD30(1);
    func_00238BD0();
    cbMax = 0;
    {
        struct E *p;
        for (p = D_004E5D80; p < D_004E5E38; p++)
            if (p->cb >= cbMax)
                cbMax = p->cb;
    }
    h = func_00238C58(cbMax);
    for (pe = D_004E5D80; pe < D_004E5E38; pe++) {
        int cb = pe->cb;
        int off = 0;
        while (cb) {
            register int limit __asm__("$2")=0xFFFC0;
            int c=limit; if(cb<limit)c=cb;
            u.dma.src = pe->src + off;
            u.dma.dst = (int)((char*)h + off);
            u.dma.size = c;
            u.dma.x = 0;
            func_00234CA0(0);
            while (!func_00234DE0(&u.dma, 1))
                ;
            cb -= c;
            off += c;
        }
        while (func_00239140(h, pe->x8, pe->xC) < 0)
            ;
    }
    func_00238D40(h);
}
