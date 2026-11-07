struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
void Enter__5AIJOB(void *p);
void SetState__15JOBMURRAYATTACKi(void *p, int n);
// name: SafeHouse port (JOBCOMPANIONATTACK::Enter)
void Enter__18JOBCOMPANIONATTACK(char *p)
{
    struct O *o;
    struct VTE *e;
    Enter__5AIJOB(p);
    SetState__15JOBMURRAYATTACKi(p, 0);
    o = *(struct O **)(p + 0x10);
    e = &o->vt[95];
    ((void (*)(void *, int, int, int, int))e->pfn)((char *)o + e->d, 4, *(int *)(p + 0x38), 4, *(int *)(p + 0x38));
    *(int *)(*(char **)(p + 0x10) + 0x10E0) |= 1;
}
