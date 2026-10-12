struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
void func_001A5848(void *p);
void func_00149718(void *p, int n);
void func_00149880(char *p)
{
    func_001A5848(p);
    if ((unsigned int)(*(int *)(p + 0x1C0) - 1) < 2) {
        func_00149718(p, 0);
        if (*(int *)(p + 0x2C8)) {
            struct VTE *e;
            *(int *)(p + 0x2C0) = 0;
            e = &((struct O *)p)->vt[3];
            ((void (*)(void *, int, int, int, int, int))e->pfn)(p + e->d, 9, 0, 0, 0, 0);
        }
    }
}
