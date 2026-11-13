typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x14]; short s14; short pad2; int n18; };
struct H { struct O *po; int pad; void *p8; void *pC; qword q10; qword q20; qword q30; };
struct N { struct H h[2]; char pad[0xAC - 0x80]; struct N *next; };
struct E { char pad[0x6C]; struct N *pn; };
struct P { char pad[0xEC]; struct E *pe; };
struct M { void *p0; void *p4; void *p8; int nC; int n10; int pad[3]; qword q20; qword q30; char pad2[0x60 - 0x40]; };
struct G;
extern struct G g_sw;
void *PaloXpFilter__FP3ALOUi(void *, int);
void s1_memset(void *, int, int);
int PaloAcceptContact__FP5CTMSG(struct M *);
void FreeSwXpList(struct G *, void *) asm("FreeSwXpList__FP2SWP2XP");
// name: SafeHouse port (DispatchAloSensorContacts)
void DispatchAloSensorContacts__FP3ALO(struct P *p)
{
    struct N *pn;
    for (pn = p->pe->pn; pn; pn = pn->next) {
        int i = pn->h[0].p8 != p;
        struct H *ph = (struct H *)((char *)pn + (i << 6));
        if (ph->po->n18) {
            struct H *pot = (struct H *)((char *)pn + ((1 - i) << 6));
            void *r = PaloXpFilter__FP3ALOUi(pot->pC, ph->po->n18);
            if (r) {
                struct M m;
                s1_memset(&m, 0, 0x60);
                m.p0 = p;
                m.p4 = ph->po;
                m.p8 = r;
                m.nC = ph->po->n18;
                m.n10 = ph->po->s14;
                m.q20 = pot->q10;
                m.q30 = ph->q30;
                PaloAcceptContact__FP5CTMSG(&m);
                if (!p->pe) break;
            }
        }
    }
    if (p->pe) {
        FreeSwXpList(&g_sw, p->pe->pn);
        p->pe->pn = 0;
    }
}
