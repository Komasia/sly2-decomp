/* A fixed stack of up to 256 words: pop the top word (0 when empty). Push is func_001D57B8. */
struct STACK {
    /* 0x000 */ int c;
    /* 0x004 */ int a[0x100];
};
int func_001D57E0(struct STACK *pstack)
{
    if (pstack->c == 0)
        return 0;
    return pstack->a[--pstack->c];
}
