typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct S { char pad[0x54]; int n; char pad2[0xD8 - 0x58]; int fd8; };
extern char D_003D4A60[];
void NProgress(CRef *pref, void *a, void *b);
void Decref(CRef *pref) asm("Decref__4CRef");
// name: SafeHouse port (FTaskDone)
int FTaskDone__FP4TASK(struct S *p)
{
    if (p->n == -1 && p->fd8) {
        CRef ref;
        int n;
        NProgress(&ref, &p->fd8, D_003D4A60);
        n = ref.m_tag;
        Decref(&ref);
        return n;
    }
    return p->n >= 2;
}
