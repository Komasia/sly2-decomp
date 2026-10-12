struct E { short s0; short k; union { int n; float g; } u; };
struct P { char pad[0x22C]; void *ap[3]; void *p238; };
void func_001F80D0(void *, float);
void func_001F0660(void *, int);
void func_001FE0E8(struct P *p, struct E *pe)
{
    int k = pe->k;
    if (k != -1 && p->ap[k]) {
        if (k == 3) func_001F80D0(p->p238, pe->u.g);
        else if (pe->u.n != -1) func_001F0660(p->ap[k], pe->u.n);
    }
}
