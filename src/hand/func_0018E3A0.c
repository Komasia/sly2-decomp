struct K { int a; int b; };
extern struct K D_002A5F98;
extern char D_003DD490[];
void func_00144480(void *p);
void func_00149AB8(void *, void *, struct K, int);
void func_0018E3A0(void *p)
{
    func_00144480(p);
    func_00149AB8(D_003DD490, p, D_002A5F98, 0);
}
