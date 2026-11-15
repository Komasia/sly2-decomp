/* SetLoRadius (0x1A6C48): sets the LO's activation radius (+0x38); a root in the world is requeued for its
 * activation check. SafeHouse activate.h. */
typedef unsigned long ulong;
struct SW;
extern struct SW g_sw;
void QueueLoRoot__FP2SWP2LO(struct SW *psw, void *ploroot);
struct S { char pad[0x10]; int psoParent; void *ploroot; char pad2[0x10]; ulong fl; int pad3[2]; float sRadius; };
// name: SafeHouse port (activate.h SetLoRadius, orig 0x1A6C48)
void SetLoRadius__FP2LOf(struct S *plo, float sRadius)
{
    plo->sRadius = sRadius;
    if (!plo->psoParent && ((int)(plo->fl >> 60) & 1)) QueueLoRoot__FP2SWP2LO(&g_sw, plo->ploroot);
}
