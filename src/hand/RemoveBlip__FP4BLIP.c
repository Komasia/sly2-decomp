/* RemoveBlip (0x139098): the same body as Sly 1's blip.c RemoveBlip: the blip leaves its group's list (BLIPG +0x448;
 * 0x139250 walks the same list) and goes to the pending list. */
// name: Sly 1 (RemoveBlip__FP4BLIP, blip.c; same body)
typedef struct DL { void *head; void *tail; int ibDle; } DL;

typedef struct BLIPG {
    /* 0x000 */ char pad0[0x448];
    /* 0x448 */ DL dlBlip;          /* the group's blips */
} BLIPG;

typedef struct BLIP {
    /* 0x0000 */ char pad0[0x108c];
    /* 0x108c */ BLIPG *pblipg;
} BLIP;

void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_002DEB00;   /* Sly 1 g_dlBlipPending */

void RemoveBlip__FP4BLIP(BLIP *pblip)
{
    RemoveDlEntry__FP2DLPv(&pblip->pblipg->dlBlip, pblip);
    AppendDlEntry__FP2DLPv(&D_002DEB00, pblip);
}
