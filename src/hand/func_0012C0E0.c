typedef struct T { int pad; int c; float *a; } T;
// name: SafeHouse port (TRKPA::IkeyFind)
int IkeyFind__5TRKPAf(T *t, float g)
{
    int i;
    for (i = 1; i < t->c - 1; i++) {
        if (g < t->a[i])
            break;
    }
    return i;
}
