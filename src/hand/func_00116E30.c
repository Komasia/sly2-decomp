/* CDynArray append: reserves room for c more items and copies them from pv to the end of the array (Sly 3:
 * CDynArray::Append). */
typedef struct DYNA { char *ab; int c; int cMax; int cb; } DYNA;

void Reserve__9CDynArrayi(DYNA *pdyna, int c);
void *s1_memcpy(void *pvDst, const void *pvSrc, unsigned int cb) asm("memcpy");

void func_00116E30(DYNA *pdyna, void *pv, int c)
{
    Reserve__9CDynArrayi(pdyna, pdyna->c + c);
    s1_memcpy(pdyna->ab + pdyna->cb * pdyna->c, pv, pdyna->cb * c);
    pdyna->c += c;
}
