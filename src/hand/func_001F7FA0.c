struct P { char pad[0xA4]; int c; void **ap; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
void SetScrollerMasterSpeeds(void *, float, float) asm("SetScrollerMasterSpeeds__FP8SCROLLERff");
void func_001F7FA0(struct P *p, float f, float g)
{
    int i;
    for (i = 0; i < p->c; i++) {
        void *q = p->ap[i];
        if (FIsBasicDerivedFrom__FP5BASIC3CID(q, 0x8F)) SetScrollerMasterSpeeds(q, f, g);
    }
}
