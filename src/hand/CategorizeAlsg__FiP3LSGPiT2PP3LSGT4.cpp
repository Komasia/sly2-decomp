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

// CategorizeAlsg (0x1A8410).  Keys: one function-scope plsg shared by both loops (its base becomes unknown to
// alias analysis, so the VECTOR swap temp at 0(sp) is not forwarded and fA/fB are reloaded); plain block temps
// for the float/int swaps; pipos formed just before the second memmove.
void CategorizeAlsg(int clsg, LSG *alsg, int *pcpos, int *aipos, LSG **aplsg, LSG **pplsgBoth)
{
    LSG *plsgNone = 0;
    int cpos = 0;
    int ilsg;
    int ipos;
    LSG *plsg;

    *pplsgBoth = 0;
    for (ilsg = 0; ilsg < clsg; ilsg++) {
        plsg = &alsg[ilsg];
        if (plsg->fA && plsg->fB) {
            plsg->plsgNext = *pplsgBoth;
            *pplsgBoth = plsg;
        } else if (!plsg->fA && !plsg->fB) {
            plsg->plsgNext = plsgNone;
            plsgNone = plsg;
        } else {
            if (plsg->fA) {
                VECTOR vecT;
                vecT = plsg->posA; plsg->posA = plsg->posB; plsg->posB = vecT;
                vecT = plsg->normalA; plsg->normalA = plsg->normalB; plsg->normalB = vecT;
                {
                    float gT = plsg->gA; plsg->gA = plsg->gB; plsg->gB = gT;
                }
                {
                    int fT = plsg->fA; plsg->fA = plsg->fB; plsg->fB = fT;
                }
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
        LSG **pplsg = &aplsg[ipos];
        int *pipos;
        if ((*pplsg)->plsgNext)
            continue;
        for (plsg = plsgNone; plsg; plsg = plsg->plsgNext) {
            if (plsg->pedge->aipos[0] == aipos[ipos] || plsg->pedge->aipos[1] == aipos[ipos])
                goto next;
        }
        (*pplsg)->plsgNext = *pplsgBoth;
        *pplsgBoth = *pplsg;
        func_002332B8(pplsg, pplsg + 1, (cpos - ipos) * 4 - 4);
        pipos = &aipos[ipos];
        func_002332B8(pipos, pipos + 1, (cpos - ipos) * 4 - 4);
        ipos--;
        cpos--;
    next:;
    }
    *pcpos = cpos;
}
