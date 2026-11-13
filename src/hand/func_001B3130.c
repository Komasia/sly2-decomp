struct S { int f0; int f4; char pad[0x28]; char x30[0x20]; char x50[0x20]; char x70[0x10]; };
void func_00232F28(void);
void Reset__10CByteQueue(void *p);
void Reset__15CQueueOutputIop(void *p);
void func_001B3130(struct S *p)
{
    if (p->f0) {
        func_00232F28();
        p->f0 = 1;
        p->f4 = -1;
        Reset__10CByteQueue(p->x30);
        Reset__10CByteQueue(p->x50);
        Reset__15CQueueOutputIop(p->x70);
    }
}
