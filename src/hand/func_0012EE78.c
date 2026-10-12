typedef struct E { int a[5]; } E;
typedef struct T { char pad[0xE0]; E *pcur; int c; E *a; } T;
void func_0012EEE0(T *t, int n, int x, int y, float g, float h);
E *func_0012EE78(T *t)
{
    if (!t->pcur) {
        t->pcur = &t->a[t->c];
        func_0012EEE0(t, -1, 300, 3000, 1.0f, 0.0f);
    }
    return t->pcur;
}
