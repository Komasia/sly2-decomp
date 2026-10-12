typedef struct KEY { int pad[3]; float t; int pad2[4]; } KEY;
typedef struct T { int pad; int c; KEY *a; } T;
int func_0012BB70(T *t, float g)
{
    int i;
    for (i = 1; i < t->c - 1; i++) {
        if (g < t->a[i].t)
            break;
    }
    return i;
}
