/* WIP 163/170 (logic complete): target keeps plsgFree in fp (ours spills to sp+0x14), first loop in t-regs, Swap() goes through a stack temp and reloads pv0/pv1 (ours propagates pv1==0). */
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct LSG {
    VECTOR pos0, pos1, n0, n1;
    float g0, g1;
    int x48;
    void *pv0, *pv1;
    unsigned short *aipos;
    int ipos;
    LSG *plsgNext;
};
extern "C" void *func_002332B8(void *pvDst, void *pvSrc, int cb);
template <class T> inline void Swap(T &a, T &b) { T t = a; a = b; b = t; }
void CategorizeAlsg(int clsg, LSG *alsg, int *pcpos, int *aipos, LSG **aplsg, LSG **pplsg)
{
    LSG *plsgFree = 0;
    int cpos = 0;
    int i, j;
    *pplsg = 0;
    for (i = 0; i < clsg; i++) {
        LSG *plsg = &alsg[i];
        if (plsg->pv0) {
            if (plsg->pv1) {
                plsg->plsgNext = *pplsg;
                *pplsg = plsg;
                continue;
            }
            Swap(plsg->pos0, plsg->pos1);
            Swap(plsg->n0, plsg->n1);
            Swap(plsg->g0, plsg->g1);
            Swap(plsg->pv0, plsg->pv1);
            plsg->ipos = 1;
        } else if (!plsg->pv1) {
            plsg->plsgNext = plsgFree;
            plsgFree = plsg;
            continue;
        }
        for (j = 0; j < cpos; j++) {
            if (plsg->aipos[plsg->ipos] == aipos[j])
                break;
        }
        if (j < cpos) {
            plsg->plsgNext = aplsg[j];
        } else {
            aipos[j] = plsg->aipos[plsg->ipos];
            cpos++;
        }
        aplsg[j] = plsg;
    }
    for (i = 0; i < cpos; i++) {
        LSG *p;
        if (aplsg[i]->plsgNext)
            continue;
        for (p = plsgFree; p; p = p->plsgNext) {
            if (p->aipos[0] == aipos[i] || p->aipos[1] == aipos[i])
                goto next;
        }
        aplsg[i]->plsgNext = *pplsg;
        *pplsg = aplsg[i];
        func_002332B8(&aplsg[i], &aplsg[i + 1], (cpos - i - 1) * 4);
        func_002332B8(&aipos[i], &aipos[i + 1], (cpos - i - 1) * 4);
        i--;
        cpos--;
    next:;
    }
    *pcpos = cpos;
}
