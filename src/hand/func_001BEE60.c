struct S { char pad[0xE0]; int c; char *a[1]; };
void RenderGlobCtx(void *p, struct S *ps) asm("RenderGlobCtx__FP4GLOBP3ALO");
void func_001BEE60(struct S *p)
{
    int i;
    if (*(int *)((char *)p + 0x128)) {
        for (i = 0; i < p->c; i++) RenderGlobCtx(p->a[i] + 0x80, p);
    }
}
