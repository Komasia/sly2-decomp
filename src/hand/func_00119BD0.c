/* class: unknown (a virtual function: vtable entry at 0x2CA5EC, next to the library classes of 0x2564E0..0x256AF0):
 * the base set-up 0x2564E0, then the +0x34 member's 0x256528 keyed by 0x119BC8 (the first word of an item). */
void func_002564E0(void *p, void *pOwner);
void func_00256528(void *p, void *pOwner, int (*pfnKey)(int *));
int func_00119BC8(int *p);

void func_00119BD0(char *p, void *pOwner)
{
    func_002564E0(p, pOwner);
    func_00256528(p + 0x34, p, func_00119BC8);
}
