/* WIP: only diff = gcc hoists &r/&one (sp+0xC10/0xC20) into s4/s5 before the loop (PRE/gcse); target recomputes each iteration. Dist asm form from func_001A3B80 (matched). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct S0 { char pad[0x70]; qword x70; };
struct S { struct S0 *x0; int x4; float x8; };
struct E { qword x0; qword x10; int x20; int x24; };
int func_001A93C8(qword pos, int b, int c, int d, int e, int n, struct E *buf, float f);
void func_002564B8(void *p);
void func_001A7C18(void *a, struct S *s, int b, qword p, qword q, int x20, int z, int x24, int g, float f);
void func_001A9B28(void *a, struct S *s, int b, int d, int e, int g)
{
    struct E buf[64];
    U r, one;
    int i;
    struct E *pe;
    i = func_001A93C8(s->x0->x70, b, 0x7FFFFFFF, d, e, 0x40, buf, s->x8) - 1;
    if (i >= 0) {
        pe = &buf[i];
        do {
            float dist;
            qword A, B;
            i--;
            A = pe->x0;
            B = pe->x10;
            func_002564B8(&r);
            func_002564B8(&one);
            __asm__("vmul.xyz %1, %3, %4\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %3w\n\tqmfc2.ni %2, %1"
                    : "=&j"(one.q), "=&j"(r.q), "=r"(dist) : "j"(B), "j"(A));
            func_001A7C18(a, s, b, A, B, pe->x20, 0, pe->x24, g, dist);
            pe--;
        } while (i >= 0);
    }
}
