typedef struct SL { void *pvFirst; void *pvLast; int ibNext; } SL;

void func_0011A200(SL *psl)
{
    psl->pvLast = 0;
    psl->pvFirst = 0;
}
