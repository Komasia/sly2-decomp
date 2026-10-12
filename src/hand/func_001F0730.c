struct P { char pad[0x24]; void *p24; char pad2[0x30 - 0x28]; int n30; int n34; int n38; char pad3[0x48 - 0x3C]; int n48; };
int func_001F0638(struct P *);
int func_001F0400(void *, int);
int func_001F0B80(void *, int, int, int, int);
void func_001F0660(struct P *, int);
void func_001F0730(struct P *p, int n)
{
    if (!func_001F0638(p) && n != -1) {
        int r = func_001F0400(p->p24, n);
        if (r != -1 && func_001F0B80(p->p24, p->n48, !p->n30 ? p->n34 : p->n38, r, 0))
            func_001F0660(p, n);
    }
}
