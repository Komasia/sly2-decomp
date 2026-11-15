// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { void (*func)(void *, void *); void *arg; void *gp; int pad; } NotifyHandler;
extern NotifyHandler D_0044E708[];  /* system notify handlers, 32 */
extern NotifyHandler *D_002C5A50;   /* user notify handlers */
extern int D_002C5A54;              /* count of user handlers */
static inline void *SetGP(void *gp)
{
    void *old;
    __asm__ volatile("move %0, $gp\n\tmove $gp, %1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}
static inline void *GetGP(void)
{
    void *gp;
    __asm__ volatile("move %0, $gp" : "=r"(gp));
    return gp;
}
/* sceSifExecNotifyHandler (libkernel): call every registered system (sys != 0) or user notify handler with
   `data`, each with its own $gp (sceSifResetIop calls both before an IOP reset). */
void *sceSifExecNotifyHandler(int sys, void *data)
{
    NotifyHandler *p;
    int n;
    void *gp;
    if (sys) {
        n = 0x20;
        p = D_0044E708;
    } else {
        p = D_002C5A50;
        n = D_002C5A54;
    }
    gp = GetGP();
    if (n > 0) {
        NotifyHandler *q = p;
        int i = n;
        do {
            if (q->func) {
                SetGP(q->gp);
                q->func(data, q->arg);
            }
            i--;
            q++;
        } while (i != 0);
    }
    return SetGP(gp);
}
