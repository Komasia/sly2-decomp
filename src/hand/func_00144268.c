void func_001C4228(void *p, int a, int b);
void func_00144188(void *p, int a);
int func_001441A0(void *p);
void func_001441C0(void *p, int a);
// name: SafeHouse port (HealActor)
void HealActor__FP5ACTORii(char *p, int a, int b)
{
    func_001C4228(p, a, b);
    func_00144188(p, **(int **)(p + 0xE00) + a);
    func_001441C0(p, func_001441A0(p) + b);
}
