struct DL { void *pvFirst; void *pvLast; int ibDle; };
extern struct DL D_003E1A4C;
void RemoveDlEntry__FP2DLPv(struct DL *pdl, void *pv);
void func_001BD040(void *pv);
int func_0011A3B0(struct DL *pdl);
void func_001BE1E8(void)
{
    while (!func_0011A3B0(&D_003E1A4C)) {
        void *pv = D_003E1A4C.pvFirst;
        RemoveDlEntry__FP2DLPv(&D_003E1A4C, pv);
        func_001BD040(pv);
    }
}
