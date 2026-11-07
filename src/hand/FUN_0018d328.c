struct B { char pad[0x5408]; char x5408[0x44]; int x544C; int x5450; };
void ResetSlotKeepSettings__FPci(struct B *p, int n);
void func_001ABB10(void *s, void *b, char *name);
int func_001AC900(void *s, char *name, void *b, int n);
int FUN_0018d328(void *s, struct B *b)
{
    char name[0x50];
    ResetSlotKeepSettings__FPci(b, 0);
    func_001ABB10(s, b, name);
    return func_001AC900(s, name, b, 0x5408);
}
