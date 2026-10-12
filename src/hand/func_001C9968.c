struct E { char pad[0x18]; int *ap; char pad2[0x50]; };
extern struct E *D_003E1398;
int func_001C9958(void *p);
int func_001C9950(void *p);
int func_001C9968(void *p)
{
    struct E *pe;
    if (func_001C9958(p) == -1) return -1;
    pe = &D_003E1398[func_001C9950(p)];
    return pe->ap[func_001C9958(p)];
}
