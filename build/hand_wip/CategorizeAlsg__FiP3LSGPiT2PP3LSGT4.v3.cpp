struct VECTOR { float x, y, z; } __attribute__((aligned(16)));
struct EDGE { unsigned short aipos[2]; };
struct LSG {
    VECTOR posA;
    VECTOR posB;
    VECTOR normalA;
    VECTOR normalB;
    float gA, gB;
    int pad48;
    int fA, fB;
    EDGE *pedge;
    int iend;
    LSG *plsgNext;
};
extern "C" void *func_002332B8(void *dst, const void *src, int cb);

#define Swap(a, b) do { typeof(a) t__ = (a); (a) = (b); (b) = t__; } while (0)

void CategorizeAlsg(int clsg, LSG *alsg, int *pcpos, int *aipos, LSG **aplsg, LSG **pplsgBoth)
{
    LSG *plsgNone = 0;
    int cpos = 0;
    int ilsg;
    int ipos;

    *pplsgBoth = 0;
    for (ilsg = 0; ilsg < clsg; ilsg++) {
        LSG *plsg = &alsg[ilsg];
        if (plsg->fA && plsg->fB) {
            plsg->plsgNext = *pplsgBoth;
            *pplsgBoth = plsg;
        } else if (!plsg->fA && !plsg->fB) {
            plsg->plsgNext = plsgNone;
            plsgNone = plsg;
        } else {
            if (plsg->fA) {
                Swap(plsg->posA, plsg->posB);
                Swap(plsg->normalA, plsg->normalB);
                Swap(plsg->gA, plsg->gB);
                Swap(plsg->fA, plsg->fB);
                plsg->iend = 1;
            }
        for (ipos = 0; ipos < cpos; ipos++) {
            if (plsg->pedge->aipos[plsg->iend] == aipos[ipos])
                break;
        }
            if (ipos >= cpos) {
                aipos[ipos] = plsg->pedge->aipos[plsg->iend];
                cpos++;
            } else {
                plsg->plsgNext = aplsg[ipos];
            }
            aplsg[ipos] = plsg;
        }
    }

    for (ipos = 0; ipos < cpos; ipos++) {
        LSG *plsg;
        int *pipos = &aipos[ipos];
        if (aplsg[ipos]->plsgNext)
            continue;
        for (plsg = plsgNone; plsg; plsg = plsg->plsgNext) {
            if (plsg->pedge->aipos[0] == *pipos || plsg->pedge->aipos[1] == *pipos)
                goto next;
        }
        aplsg[ipos]->plsgNext = *pplsgBoth;
        *pplsgBoth = aplsg[ipos];
        func_002332B8(&aplsg[ipos], &aplsg[ipos + 1], (cpos - ipos) * 4 - 4);
        func_002332B8(pipos, pipos + 1, (cpos - ipos) * 4 - 4);
        ipos--;
        cpos--;
    next:;
    }
    *pcpos = cpos;
}
