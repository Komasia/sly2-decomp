int PrefFindBinding(void *a, void *b, void *c, void *d) asm("PrefFindBinding__6CFrameUii");
void func_00129658(void *a, int b);
int FFindBinding__6CFrameUiiP4CRef(void *a, void *b, void *c, void *d)
{
    int v = PrefFindBinding(a, b, c, d);
    if (v) {
        if (d)
            func_00129658(d, v);
        return 1;
    }
    return 0;
}
