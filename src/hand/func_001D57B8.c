/* A fixed stack of up to 256 words: push n (dropped when full). Pop is func_001D57E0. */
struct STACK {
    /* 0x000 */ unsigned int c;
    /* 0x004 */ int a[0x100];
};
void func_001D57B8(struct STACK *pstack, int n)
{
    if (pstack->c < 0x100)
        pstack->a[pstack->c++] = n;
}
