typedef int qword __attribute__((mode(TI)));
struct LSG { char pad[0x60]; };
int ClipSegmentSoe__FP3SOEG9VU_VECTORT1iP3LSG(void *pso, qword a, qword b, int c, struct LSG *plsg);
int CMergeAlsg__FiP3LSGiT1iT1i(int c, struct LSG *alsg, int n, struct LSG *plsg, int cMax, struct LSG *alsg2, int f);
int func_0014CDB0(qword a, qword b, int cso, void **apso, int cMax, struct LSG *alsg)
{
    int c = 0;
    int i;
    for (i = 0; i < cso; i++) {
        struct LSG *plsg = &alsg[c];
        int n = ClipSegmentSoe__FP3SOEG9VU_VECTORT1iP3LSG(apso[i], a, b, cMax - c, plsg);
        if (n)
            c = CMergeAlsg__FiP3LSGiT1iT1i(c, alsg, n, plsg, cMax, alsg, 0);
    }
    return c;
}
