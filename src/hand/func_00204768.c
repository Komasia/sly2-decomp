typedef int qword __attribute__((mode(TI)));
struct STEP;
struct XPD { char pad[8]; struct STEP *owner,*other; char pad10[0x30]; };
struct XP { struct XPD axpd[2]; qword normal; float gDist; char pad94[8]; int xpk; char padA0[0xC]; struct XP *next; };
/* a group of contacts of the attachment (OXA) */
struct XPGROUP { struct XP *pxpFirst; struct XPGROUP *next; struct XP **ppxpBack; };
struct OXA { char pad[0x64]; struct XPGROUP *pgroupFirst; struct XP *pxpFirst; };
struct STEP { char pad[0xEC]; struct OXA *poxa; char padF0[0x118]; struct XP *pxpFloor; float tFloor; char pad210[0x20]; qword posFloor; };
extern float D_002A85F4,g_clock;   /* FLT_MAX; g_clock.t */
#define XPK_Floor 14   /* a floor contact (AddStepFloorXps) */
struct SW;
extern struct SW g_sw;
void NotifyAloContacts(struct STEP *) asm("NotifyAloContacts__FP3ALO");
void FreeSwXpList__FP2SWP2XP(struct SW *,struct XP *);
/* the object at the contact's other end from pstep */
static inline struct STEP *Other(struct XP*pxp,struct STEP*pstep){unsigned fDiffer=(unsigned)pstep^(unsigned)pxp->axpd[0].owner;int i=fDiffer>0;return ((struct XPD *)((char *)pxp+(i<<6)))->other;}
/* FindStepFloor (0x204768): STEP vt slot 58: after the contacts are posted, the floor is the kind-14 contact with the
 * smallest separation among the attachment's groups and its own list (pxpFloor, tFloor, posFloor = its end 1's
 * point); the object's other kind-14 contacts are unlinked and freed. */
// name: SafeHouse port (FindStepFloor)
void FindStepFloor__FP3ALO(struct STEP *pstep)
{
    struct XP *pxpFloor;
    struct XPGROUP *pgroup;
    NotifyAloContacts(pstep);
    {
        float gDist=D_002A85F4;
        pgroup=pstep->poxa->pgroupFirst;
        pxpFloor=0;
        for(;;){
            struct XP *pxp=pgroup?pgroup->pxpFirst:pstep->poxa->pxpFirst;
            for(;pxp;pxp=pxp->next){
                if(pxp->xpk==XPK_Floor && pxp->gDist<gDist){gDist=pxp->gDist;pxpFloor=pxp;}
            }
            if(!pgroup)break;
            pgroup=pgroup->next;
        }
    }
    pstep->pxpFloor=pxpFloor;
    if(pxpFloor){pstep->tFloor=g_clock;pstep->posFloor=*(qword *)((char *)pxpFloor+0x50);}
    {
        struct XP *pxpRemoved=0;
        pgroup=pstep->poxa->pgroupFirst;
        for(;;){
            struct XP **ppxpLink=pgroup?&pgroup->pxpFirst:&pstep->poxa->pxpFirst;
            struct XP *pxp;
            while((pxp=*ppxpLink)!=0){
                if(Other(pxp,pstep)==pstep && pxp->xpk==XPK_Floor && pxp!=pxpFloor){
                    *ppxpLink=pxp->next;
                    pxp->next=pxpRemoved;
                    pxpRemoved=pxp;
                }else ppxpLink=&pxp->next;
            }
            if(!pgroup)break;
            *pgroup->ppxpBack=pgroup->pxpFirst;
            pgroup=pgroup->next;
        }
        FreeSwXpList__FP2SWP2XP(&g_sw,pxpRemoved);
    }
}
