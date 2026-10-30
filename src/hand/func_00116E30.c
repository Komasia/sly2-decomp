typedef struct DYNA { char *ab; int c; int cMax; int cb; } DYNA;

void Reserve__9CDynArrayi(DYNA *pdyna, int c);
void *func_0023320C(void *pvDst, const void *pvSrc, unsigned int cb);

void func_00116E30(DYNA *pdyna, void *pv, int c)
{
    Reserve__9CDynArrayi(pdyna, pdyna->c + c);
    func_0023320C(pdyna->ab + pdyna->cb * pdyna->c, pv, pdyna->cb * c);
    pdyna->c += c;
}
