struct DL { void *pvFirst; void *pvLast; int ibDle; };
extern struct DL D_003E1A4C;
void func_0011A2E8(struct DL *pdl, void *pv);
void func_001BD040(void *pv);
int func_0011A3B0(struct DL *pdl);
void func_001BE1E8(void)
{
    while (!func_0011A3B0(&D_003E1A4C)) {
        void *pv = D_003E1A4C.pvFirst;
        func_0011A2E8(&D_003E1A4C, pv);
        func_001BD040(pv);
    }
}
