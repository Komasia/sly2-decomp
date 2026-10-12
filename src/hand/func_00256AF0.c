typedef struct B { char pad[0x10]; int *base; } B;
typedef struct O { char pad[0xC]; B *pb; int (*pfn)(int *); char h[0x10]; } O;
int *func_002569F8(void *, int *, int *);

void func_00256AF0(O *p, int *px)
{
    int a[2];
    void *h = p->h;
    a[1] = px - p->pb->base;
    a[0] = p->pfn(px);
    func_002569F8(h, &a[0], &a[1]);
}
