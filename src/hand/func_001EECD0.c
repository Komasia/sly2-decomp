struct S { int n0; int n4; int n8; };
struct L { int a; int b; int c; int d; };
void EndChildJob__FPP5AIJOB(struct L *pl);
// name: SafeHouse port (ClearJobs)
void ClearJobs__FP5ACTOR(struct S *p)
{
    struct L l;
    if (p->n4 > 0) {
        l.a = p->n8;
        EndChildJob__FPP5AIJOB(&l);
    }
    p->n4 = 0;
}
