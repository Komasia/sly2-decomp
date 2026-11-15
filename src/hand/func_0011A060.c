/* Singly-linked list (SL): clears the list (Sly 3 map: ClearSl). */
typedef struct SL { void *pvFirst; void *pvLast; int ibNext; } SL;
void func_0011A060(SL *psl) { psl->pvLast = 0; psl->pvFirst = 0; }
