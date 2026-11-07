typedef struct KEY { int pad[3]; float t; int pad2[8]; } KEY;
typedef struct T { int pad; int c; KEY *a; } T;
// name: SafeHouse port (TRKPK::IkeyFind)
int IkeyFind__5TRKPKf(T *t, float g)
{
    int i;
    for (i = 1; i < t->c - 1; i++) {
        if (g < t->a[i].t)
            break;
    }
    return i;
}
