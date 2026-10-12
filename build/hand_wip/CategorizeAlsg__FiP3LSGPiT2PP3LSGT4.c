/* WIP: structure right; the LSG reversal swap (qword pairs via stack temp at sp+0, reloading f0/f1 after the stores) not reproduced - gcc keeps the temps in regs and CSEs f1==0. Also needs plsgNone in fp (stack pressure). */
typedef int qword __attribute__((mode(TI)));
typedef struct EDGE { unsigned short ipos[2]; } EDGE;
typedef struct VEC { float x, y, z, w; } __attribute__((aligned(16))) VEC;
typedef struct LSG {
    VEC a, b, c, d;
    float g0, g1;
    int pad48;
    int f0, f1;
    EDGE *pedge;
    int iend;
    struct LSG *next;
} LSG;
void *func_002332B8(void *dst, void *src, int cb);
static __inline__ void SwapV(VEC *a, VEC *b) { VEC t = *a; *a = *b; *b = t; }
static __inline__ void SwapF(float *a, float *b) { float t = *a; *a = *b; *b = t; }
static __inline__ void SwapI(int *a, int *b) { int t = *a; *a = *b; *b = t; }
static __inline__ void Reverse(LSG *plsg)
{
    SwapV(&plsg->a, &plsg->b);
    SwapV(&plsg->c, &plsg->d);
    SwapF(&plsg->g0, &plsg->g1);
    SwapI(&plsg->f0, &plsg->f1);
    plsg->iend = 1;
}
void CategorizeAlsg(int clsg, LSG *alsg, int *pcpos, int *aipos, LSG **aplsg, LSG **pplsgBoth)
    __asm__("CategorizeAlsg__FiP3LSGPiT2PP3LSGT4");
void CategorizeAlsg(int clsg, LSG *alsg, int *pcpos, int *aipos, LSG **aplsg, LSG **pplsgBoth)
{
    int ilsg;
    LSG *plsgNone = 0;
    int cpos = 0;
    int ipos;
    *pplsgBoth = 0;
    for (ilsg = 0; ilsg < clsg; ilsg++) {
        LSG *plsg = &alsg[ilsg];
        if (plsg->f0) {
            if (plsg->f1) {
                plsg->next = *pplsgBoth;
                *pplsgBoth = plsg;
                continue;
            }
            Reverse(plsg);
        } else if (!plsg->f1) {
            plsg->next = plsgNone;
            plsgNone = plsg;
            continue;
        }
        for (ipos = 0; ipos < cpos; ipos++)
            if (plsg->pedge->ipos[plsg->iend] == aipos[ipos])
                break;
        if (ipos < cpos)
            plsg->next = aplsg[ipos];
        else
            aipos[cpos++] = plsg->pedge->ipos[plsg->iend];
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
        func_002332B8(&aplsg[ipos], &aplsg[ipos + 1], (cpos - ipos - 1) * 4);
        func_002332B8(&aipos[ipos], &aipos[ipos + 1], (cpos - ipos - 1) * 4);
        ipos--;
        cpos--;
    next:;
    }
    *pcpos = cpos;
}
