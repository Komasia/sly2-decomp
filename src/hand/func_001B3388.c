struct M { int a, b; int n8; unsigned int nC; };
struct S { char pad[0x160]; char x160[0x10]; unsigned int c170; };
void CbFill(void *p, unsigned int a, int b) asm("CbFill__10CByteQueueiPUc");
int func_001B3388(void *a, struct M *pm, struct S *p)
{
    if (p->c170 < pm->nC) return 0;
    CbFill(p->x160, pm->nC, pm->n8);
    return 1;
}
