typedef int qword __attribute__((mode(TI)));
struct LSG { qword a[4]; float t; char pad[0x1C]; };
int func_0014C6A0(void *pso, qword a, qword b, int c, struct LSG *plsg);
void *PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(int grf, qword a, qword b, int cso, void **apso, struct LSG *plsg)
{
    void *psoBest = 0;
    float tBest = 3.40282346638528859812e+38f;
    int i;
    for (i = 0; i < cso; i++) {
        struct LSG alsg[2];
        void *pso = apso[i];
        int c = func_0014C6A0(pso, a, b, 2, alsg);
        int j = 0;
        if (c > 0 && alsg[0].t == 0.0f && (grf & 1))
            j = 1;
        if (j < c && alsg[j].t < tBest) {
            tBest = alsg[j].t;
            psoBest = pso;
            if (plsg)
                *plsg = alsg[j];
        }
    }
    return psoBest;
}
