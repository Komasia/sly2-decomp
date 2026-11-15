/* func_001A6CA8 (0x1A6CA8): sets the LO's activation kind (bits 52..55 of +0x28; SafeHouse activate.cpp: InitLo
 * sets 2); a root in the world is requeued for its activation check when it changes. */
struct O {
    char pad[0x10];
    struct O *psoParent;
    void *ploroot;
    char pad2[0x10];
    unsigned long b0 : 52;
    long actk : 4;           /* the activation kind */
    unsigned int b56 : 4;
    unsigned int fInWorld : 1;
};
extern char g_sw[];
void QueueLoRoot__FP2SWP2LO(void *, void *);
void func_001A6CA8(struct O *plo, int actk)
{
    if (actk != plo->actk) {
        plo->actk = actk;
        if (!plo->psoParent && plo->fInWorld != 0)
            QueueLoRoot__FP2SWP2LO(g_sw, plo->ploroot);
    }
}
