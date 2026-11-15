/* GCmdDuration: how long a (synchronous) script command takes, for the commands with a known length: an animation's
 * length over its speed (PlayAseg, the speed a quadratic in the suck value, clamped), the state machine's time to
 * the target state (ApplySm), the camera jolt (Unk32), a wait / rumble / fade / hint time, or a voice line's length;
 * 0 otherwise and for asynchronous commands. */
#include "relay.h"
struct G { int a; };
extern struct G g_sw;
extern struct G D_003DD040;        /* the voice lines */
extern struct G D_002DE578;        /* the suck state */
extern float DT_CmJoltMax;
typedef struct ASEG {              /* fields by use */
    /* 0x00 */ char unk_lo[0x74];
    /* 0x74 */ float tLength;
    /* 0x78 */ float svtBase;
    /* 0x7c */ int unk_0x7c;
    /* 0x80 */ float asvtSuck[3];  /* speed = [0] + suck [1] + suck^2 [2] */
    /* 0x8c */ int unk_0x8c;
    /* 0x90 */ float svtMin;
    /* 0x94 */ float svtMax;
} ASEG;
ASEG *PloFind__FP3RUNi(JSG *pjsg, OID oid);
float GSuck__FPv(struct G *pg);
void *PloFindSwNearest__FP2LO3OIDii(struct G *pg, int grffso, OID oid, LO *ploContext);
void *PsmaFindAloSm__Fi3OID(void *palo, OID oidSm);
float func_001F11A8(void *psma, OID oidState);   /* time to reach the state */
float func_001FCFD0(struct G *pg, int idLine);   /* a voice line's length */
static __inline__ float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
// name: SafeHouse port (GCmdDuration)
float GCmdDuration__FP3RUNP7SCPTCMD(JSG *pjsg, RELAYCMD *prelaycmd)
{
    float dt = 0.0f;
    if (prelaycmd->fAsync) return dt;
    switch (prelaycmd->relayck) {
    case RELAYCK_PlayAseg: {
        ASEG *paseg = PloFind__FP3RUNi(pjsg, prelaycmd->u.playAseg.oidAseg);
        if (paseg) {
            float uSuck = GSuck__FPv(&D_002DE578);
            float *asvt = paseg->asvtSuck; float svt = asvt[0] + uSuck * (asvt[1] + uSuck * asvt[2]); svt = GClamp(svt, paseg->svtMin, paseg->svtMax);
            dt = paseg->tLength / (paseg->svtBase * svt);
        }
        break;
    }
    case RELAYCK_ApplySm:
        if (prelaycmd->u.applySm.oidState != -1) {
            void *palo = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, prelaycmd->u.applySm.oidSm, pjsg->ploContext);
            if (palo) {
                void *psma = PsmaFindAloSm__Fi3OID(palo, prelaycmd->u.applySm.oidUnk5);
                if (psma) dt = func_001F11A8(psma, prelaycmd->u.applySm.oidState);
            }
        }
        break;
    case RELAYCK_Unk32:
        dt = DT_CmJoltMax;
        break;
    case RELAYCK_Face:
    case RELAYCK_Rumble:
        dt = prelaycmd->u.face.dtWait;   /* = rumble.dtRumble */
        break;
    case RELAYCK_Line:
        dt = func_001FCFD0(&D_003DD040, prelaycmd->u.line.idLine);
        break;
    case RELAYCK_AddObject:
    case RELAYCK_RemoveObject:
    case RELAYCK_HintBox:
        dt = prelaycmd->u.addObject.dtFade;   /* = removeObject.dtFade, hintBox.dtHint */
        break;
    }
    return dt;
}
