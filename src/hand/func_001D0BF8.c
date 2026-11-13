typedef int qword __attribute__((mode(TI)));
typedef struct { qword a[3]; } M3;
typedef struct { void *x0; void *x4; } S;
typedef struct { char pad[0x40]; M3 m; } R;
typedef struct { char pad[0x1C]; void *x1C; } OBJ;
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
R *PripDecal__FP4RIPNP4RIPGP2LOG9VU_VECTORT3(OBJ *, void *, void *, qword, qword);
void func_001A7050(M3 *, int, void *, M3 *);
void RemoveRip(OBJ *) asm("RemoveRip__FP3RIP");
int func_001D0BF8(OBJ *p, S *s, qword a, qword b)
{
    R *r;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(s->x4, 0x33))
        return 0;
    r = PripDecal__FP4RIPNP4RIPGP2LOG9VU_VECTORT3(p, p->x1C, s->x0, a, b);
    if (r) {
        M3 m;
        func_001A7050(&m, 0, s->x4, &r->m);
        r->m = m;
    }
    RemoveRip(p);
    return 1;
}
