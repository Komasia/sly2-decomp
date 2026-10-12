struct S { char pad[0x1034]; void *p1034; char pad1[0x1530 - 0x1038]; void *p1530; int n1534; };
void func_001B6078(struct S *p, int n);
void func_001F0948(void *p, int n);
void func_001F0660(void *p, int n);
void func_001B9C00(struct S *p, void *pv, int n, int m, int f)
{
    p->p1530 = pv;
    p->n1534 = m;
    func_001B6078(p, 6);
    if (n == -1)
        return;
    if (p->p1530) {
        if (f)
            func_001F0948(p->p1530, n);
        else
            func_001F0660(p->p1530, n);
    }
    if (f)
        func_001F0948(p->p1034, n);
    else
        func_001F0660(p->p1034, n);
}
