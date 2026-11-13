typedef struct P { float x; float y; int n; } P;
void ApplyAseg__FP4ASEGiiffPP5ASEGA(void *a, float x, float y, int b, int n, int c);
// name: SafeHouse port (asega.cpp: "0x149A50 queues ApplyAsegParams 0x12F8C0")
void ApplyAsegParams(void *a, P *p) asm("ApplyAsegParams__FP4ASEGPv");
void ApplyAsegParams(void *a, P *p)
{
    ApplyAseg__FP4ASEGiiffPP5ASEGA(a, p->x, p->y, 0, p->n, 0);
}
