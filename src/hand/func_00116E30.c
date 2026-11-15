/* CDynArray append: reserves room for c more items and copies them from pv to the end of the array (Sly 3:
 * CDynArray::Append). */
typedef struct DYNA { char *ab; int c; int cMax; int cb; } DYNA;

void Reserve__9CDynArrayi(DYNA *pdyna, int c);
void *s1_memcpy(void *pvDst, const void *pvSrc, unsigned int cb) asm("memcpy");

// name: Sly 3 name Append__9CDynArrayPvi (SafeHouse fnmap 0x116E30 -> Sly 3 0x118260, score 98): Reserve then copy c elements
void Append__9CDynArrayPvi(DYNA *pdyna, void *pv, int c)
{
    Reserve__9CDynArrayi(pdyna, pdyna->c + c);
    s1_memcpy(pdyna->ab + pdyna->cb * pdyna->c, pv, pdyna->cb * c);
    pdyna->c += c;
}
