struct P { char pad[0xA4]; int c; void **ap; };
int func_00132B10(void *, int);
void func_001EDAD8(void *, float, float);
void func_001F8038(struct P *p, float f, float g)
{
    int i;
    for (i = 0; i < p->c; i++) {
        void *q = p->ap[i];
        if (func_00132B10(q, 0x8F)) func_001EDAD8(q, f, g);
    }
}
