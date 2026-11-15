// LoadAsegEventsFromBrx (SafeHouse aseg.h, orig 0x12F590): one of an ASEG's event lists: U8 count, then per event
// its S8 kind, (timed lists) its S16 time in frames, and the kind's payload in the two words +0x8 / +0xC (kinds 0,
// 17, 20 and 24 point at a copy on the world heap).
extern "C" {
typedef struct BIS BIS;
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct EV0 { int n; int a, b, c; float x, y, z; } EV0;     // kind 0: S16, 3 S32, 3 F32 (read z, x, y)
typedef struct EV20 { int a, b; float g; } EV20;                     // kind 20: 2 S32, F32
typedef struct ASEGEV {
    float t;                                                         // field: SafeHouse port
    int kind;                                                        // field: SafeHouse port
    union { int n; float g; void *pv; int *pn; } u8;
    union { int n; float g; } uC;
} ASEGEV;
float F32Read(BIS *pbis) asm("F32Read__18CBinaryInputStream");
int S16Read(BIS *pbis) asm("S16Read__18CBinaryInputStream");
int S32Read(BIS *pbis) asm("S32Read__18CBinaryInputStream");
int S8Read(BIS *pbis) asm("S8Read__18CBinaryInputStream");
int U8Read(BIS *pbis) asm("U8Read__18CBinaryInputStream");
void *PvAllocSwImpl(AREQ *preq) asm("PvAllocSwImpl__Fi");
void *PvAllocSwClearImpl(AREQ *preq) asm("PvAllocSwClearImpl__Fi");
void *PvAllocSwCopyImpl(AREQ *preq, void *pv) asm("PvAllocSwCopyImpl__FiPv");
void ReadCb8(BIS *pbis, void *pv) asm("ReadCb8__18CBinaryInputStreamPv");
void func_0012F590(void *paseg, BIS *pbis, int fTime, int *pcev, struct ASEGEV **paev);
}
static __inline__ void *PvAlloc(int cb) { AREQ req; req.cb = cb; req.cbAlign = 0x10; return PvAllocSwClearImpl(&req); }
void func_0012F590(void *paseg, BIS *pbis, int fTime, int *pcev, ASEGEV **paev)
{
    int i;
    int cev;
    ASEGEV *aev;
    cev = U8Read(pbis);
    *pcev = cev;
    aev = (ASEGEV *)PvAlloc(cev * 16);
    *paev = aev;
    for (i = 0; i < cev; i++) {
        ASEGEV *pev = &aev[i];
        pev->kind = S8Read(pbis);
        if (fTime)
            pev->t = S16Read(pbis) * (1.0f / 60.0f);
        switch (pev->kind) {
        case 0: {
            AREQ req;
            EV0 ev;
            ev.n = S16Read(pbis); ev.a = S32Read(pbis); ev.b = S32Read(pbis); ev.c = S32Read(pbis);
            ev.z = F32Read(pbis); ev.x = F32Read(pbis); ev.y = F32Read(pbis);
            req.cb = 0x1C; req.cbAlign = 0x10;
            pev->u8.pv = PvAllocSwCopyImpl(&req, &ev);
            break;
        }
        case 3:
            pev->uC.g = S16Read(pbis) * (1.0f / 60.0f);
            pev->u8.n = S16Read(pbis);
            break;
        case 5:
            pev->u8.g = S16Read(pbis) * (1.0f / 60.0f);
            pev->uC.g = F32Read(pbis);
            break;
        case 7: case 8:
            pev->u8.n = S32Read(pbis);
            pev->uC.g = F32Read(pbis);
            break;
        case 13: case 14: case 15: case 16:
            pev->u8.n = S32Read(pbis);
            pev->uC.n = S32Read(pbis);
            break;
        case 17: {
            pev->u8.pv = PvAlloc(0x10);
            pev->u8.pn[0] = S32Read(pbis); pev->u8.pn[1] = S32Read(pbis); pev->u8.pn[2] = S32Read(pbis);
            ((float *)pev->u8.pn)[3] = F32Read(pbis);
            break;
        }
        case 20: {
            EV20 ev;
            AREQ req;
            AREQ *preq;
            ev.a = S32Read(pbis); ev.b = S32Read(pbis); ev.g = F32Read(pbis);
            preq = &req; req.cb = 0xC; preq->cbAlign = 0x10;
            pev->u8.pv = PvAllocSwCopyImpl(preq, &ev);
            break;
        }
        case 1: case 2: case 21:
            pev->u8.n = S16Read(pbis);
            break;
        case 4: case 11: case 12: case 22:
            pev->u8.n = S32Read(pbis);
            break;
        case 24: {   // three 8-byte blobs
            AREQ req;
            char *pb;
            req.cb = 0x18; req.cbAlign = 0x10;
            pb = (char *)PvAllocSwImpl(&req);
            ReadCb8(pbis, pb); ReadCb8(pbis, pb + 8); ReadCb8(pbis, pb + 0x10);
            pev->u8.pv = pb;
            break;
        }
        }
    }
}
