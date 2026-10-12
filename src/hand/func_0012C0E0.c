typedef struct T { int pad; int c; float *a; } T;
int func_0012C0E0(T *t, float g)
{
    int i;
    for (i = 1; i < t->c - 1; i++) {
        if (g < t->a[i])
            break;
    }
    return i;
}
