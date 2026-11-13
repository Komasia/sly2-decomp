int PrefFindBinding(void *a, void *b, void *c, void *d) asm("PrefFindBinding__6CFrameUii");
void __as__4CRefRC4CRef(void *a, int b);
int FFindBinding__6CFrameUiiP4CRef(void *a, void *b, void *c, void *d)
{
    int v = PrefFindBinding(a, b, c, d);
    if (v) {
        if (d)
            __as__4CRefRC4CRef(d, v);
        return 1;
    }
    return 0;
}
