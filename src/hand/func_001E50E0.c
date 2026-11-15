/* func_001E50E0: the script's hands-off state (HandsOff command): turning it on pauses the game and the talk with
 * the given pause flags (replacing an earlier hands-off with other flags), turning it off resumes them. */
#include "relay.h"
struct G { int a; };
extern struct G g_sw;
void ResumeGame__FP9GAMEPAUSEi(struct G *pg, int grfHandsOff);
void ResumeTalk__FP2SW(struct G *pg);
void PauseGame__FP9GAMEPAUSEi(struct G *pg, int grfHandsOff);
void PauseTalk__FP2SW(struct G *pg);
void func_001E50E0(JSG *pjsg, int fHandsOff, int grfHandsOff)
{
    if (!fHandsOff) {
        if (!pjsg->fHandsOff) return;
    } else {
        if (pjsg->fHandsOff) {
            if (grfHandsOff == pjsg->grfHandsOff) return;
            ResumeGame__FP9GAMEPAUSEi(&g_sw, pjsg->grfHandsOff);
            ResumeTalk__FP2SW(&g_sw);
        }
        PauseGame__FP9GAMEPAUSEi(&g_sw, grfHandsOff);
        PauseTalk__FP2SW(&g_sw);
        pjsg->fHandsOff = fHandsOff;
        pjsg->grfHandsOff = grfHandsOff;
        return;
    }
    ResumeGame__FP9GAMEPAUSEi(&g_sw, pjsg->grfHandsOff);
    ResumeTalk__FP2SW(&g_sw);
    pjsg->fHandsOff = fHandsOff;
    pjsg->grfHandsOff = grfHandsOff;
}
