// (Claude agent) v2: aligned 86 (same as .c) but block layout now matches the target: both/none tests as separate ifs then if(pv0) reverse (jump threading), aipos[ipos] store in the ipos>=cpos branch, size (cpos-ipos)*4-4. Left: target swaps vectors through a stack temp and reloads pv0/pv1 (no CSE); plsgNone spilled (target: fp), aipos kept in s7.
typedef struct EDGE { unsigned short ipos[2]; } EDGE;
struct VECTOR { float af[4]; } __attribute__((aligned(16)));
struct LSG {
    VECTOR a, b, c, d;
    float g0, g1;
    int pad48;
    void *pv0, *pv1;
    EDGE *pedge;
    int iend;
    LSG *next;
};
extern "C" void *func_002332B8(void *dst, void *src, int cb);
template <class T> inline void Swap(T &a, T &b) { T t = a; a = b; b = t; }
inline void SwapV(VECTOR &a, VECTOR &b) { VECTOR t; __builtin_memcpy(&t, &a, sizeof(VECTOR)); __builtin_memcpy(&a, &b, sizeof(VECTOR)); __builtin_memcpy(&b, &t, sizeof(VECTOR)); }
void CategorizeAlsg(int clsg, LSG *alsg, int *pcpos, int *aipos, LSG **aplsg, LSG **pplsgBoth)
{
    int ilsg;
    LSG *plsgNone = 0;
    int cpos = 0;
    int ipos;
    *pplsgBoth = 0;
    for (ilsg = 0; ilsg < clsg; ilsg++) {
        LSG *plsg = &alsg[ilsg];
        if (plsg->pv0 && plsg->pv1) {
            plsg->next = *pplsgBoth;
            *pplsgBoth = plsg;
            continue;
        }
        if (!plsg->pv0 && !plsg->pv1) {
            plsg->next = plsgNone;
            plsgNone = plsg;
            continue;
        }
        if (plsg->pv0) {
            Swap(plsg->a, plsg->b);
            Swap(plsg->c, plsg->d);
            Swap(plsg->g0, plsg->g1);
            Swap(plsg->pv0, plsg->pv1);
            plsg->iend = 1;
        }
        for (ipos = 0; ipos < cpos; ipos++)
            if (plsg->pedge->ipos[plsg->iend] == aipos[ipos])
                break;
        if (ipos >= cpos) {
            aipos[ipos] = plsg->pedge->ipos[plsg->iend];
            cpos++;
        } else
            plsg->next = aplsg[ipos];
        aplsg[ipos] = plsg;
    }
    for (ipos = 0; ipos < cpos; ipos++) {
        LSG *p;
        if (aplsg[ipos]->next)
            continue;
        for (p = plsgNone; p; p = p->next)
            if (p->pedge->ipos[0] == aipos[ipos] || p->pedge->ipos[1] == aipos[ipos])
                goto next;
        aplsg[ipos]->next = *pplsgBoth;
        *pplsgBoth = aplsg[ipos];
        func_002332B8(&aplsg[ipos], &aplsg[ipos + 1], (cpos - ipos) * 4 - 4);
        func_002332B8(&aipos[ipos], &aipos[ipos + 1], (cpos - ipos) * 4 - 4);
        ipos--;
        cpos--;
    next:;
    }
    *pcpos = cpos;
}
