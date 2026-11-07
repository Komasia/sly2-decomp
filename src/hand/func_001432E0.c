extern void *D_003E1AC8;
int IdBooty__FP2LO(void *p);
void DropActorBooty__FP5ACTORii(void *p);
void *func_001CB250(void *p, int n);
void SelectBootyRecord__FP2LOi(void *p, int n);
void SetBootyState__FP2LOi(void *p, int n);
// name: SafeHouse port (GiveActorBooty)
void GiveActorBooty__FP5ACTORi(char *p, int n)
{
    void *q = *(void **)(p + 0x11A8);
    char *o;
    if (q && IdBooty__FP2LO(q) == n) return;
    DropActorBooty__FP5ACTORii(p);
    if (n == -1) return;
    if (!D_003E1AC8) return;
    o = func_001CB250(D_003E1AC8, 1);
    SelectBootyRecord__FP2LOi(o, n);
    *(void **)(o + 0x160) = p;
    SetBootyState__FP2LOi(o, 6);
    SetBootyState__FP2LOi(o, 4);
}
