typedef struct {
    int key;
    int a;
    int b;
    int c;
    int cur;
    int pad[2];
    int flags;
} E;
typedef struct {
    char pad0[0x24];
    void *x24;
    char pad28[0x48 - 0x28];
    int key;
    int n;
    E *ae;
} OBJ;
void func_00213928(void *, int);
void func_00213B00(void *, int);
void func_001DB390(OBJ *p, int key)
{
    int i;
    p->key = key;
    for (i = 0; i < p->n; i++) {
        E *e = &p->ae[i];
        int v;
        if (e->key == key)
            v = e->c;
        else if (e->flags & 4)
            v = e->b;
        else if (e->flags & 2)
            v = e->a;
        else
            v = -1;
        if (v != e->cur) {
            if (p->x24 && e->cur != -1)
                func_00213928(p->x24, e->cur);
            e->cur = v;
            if (p->x24 && v != -1)
                func_00213B00(p->x24, v);
        }
    }
}
