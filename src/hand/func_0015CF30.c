// (Claude agent) UpdateEpMenu__FP6EPMENU: UI menu state machine. FSpriteAnimPlaying__FP2LOi takes (pepmenu, idPart) with idPart = IdPartCur__FP6EPMENU(pepmenu); the hint == 0 case uses a shared "setf: f = 1" block (reorg fills both beql/bnel slots from it).
struct CRef { int m_tagk; int m_n; };
struct CRefG { int m_tagk; float m_g; };
#include "clock.h"
#include "h2_epmenu.h"
struct SW { char pad[0x3B58]; SWEPPROGRESS epprogress; };
extern struct SW g_sw;
extern char D_003D4A60[];
extern char D_003D9ED0[], D_002E6550[], D_003DA4F0[];   /* the menu, the card status, the message (SafeHouse) */
extern char g_joy[];
extern char D_002F66B0[];   /* the movie queue */
extern int D_002BE248[];    /* per episode: its movie */
extern int D_002BE26C;      /* everything unlocked */
extern int D_002BE270;      /* the movie the menu returns to */
extern int D_002BE200[];    /* per movie: the movie */
extern int D_002BE278[];    /* per mode: the mode that follows its animation */
extern int D_002BE2A8[];    /* per episode: the oid of its exit */
void func_00212C50(EPMENU *pepmenu);
int func_001D9880(void *p);
int IdPartCur__FP6EPMENU(EPMENU *pepmenu);
int func_001880D8(void *pjoy);   /* the up / down step */
int GrfbtnTakePressedJoy(void *pjoy, int grfbtn) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
int func_00187E88(void *pjoy);   /* the left / right step */
void SetEpMode__FP6EPMENUii(EPMENU *pepmenu, int mode, int sub);
void NProgress(void *pref, void *pvKey, void *pv);
void Decref(void *pref) asm("Decref__4CRef");
void SetHint__FP6EPMENUi(EPMENU *pepmenu, int hint);
void QueueMovie__FPUcPv(void *pmq, int pbMovie);
void RequestTransition__FP2SWPUc3OIDT2iT2(struct SW *psw, int pchzWorld, int oid, int a, int b, int c);
void *PsndNewPlain__Fi(int sfxid);
void SetSource__4CSndPv(void *psnd, int pso);
int CmovieOpen__FP6EPMENU(EPMENU *pepmenu);
int FSpriteAnimPlaying__FP2LOi(EPMENU *pepmenu, int idPart);
void *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int cid, int oid, int n);
void SetExitState__FP2LOi(void *pexit, int state);
void TriggerExit__FP4EXIT(void *pexit);
int func_00210B98(int iep);   /* the episode's world */

/* a menu sound: 0x34 accept, 0x36 refused */
static __inline__ void PlaySound(int sfxid)
{
    SetSource__4CSndPv(PsndNewPlain__Fi(sfxid), 0);
}

// name: SafeHouse port (UpdateEpMenu)
/* UpdateEpMenu: the episode menu's update, per mode: choosing the episode (up / down, confirm, back, the movie
 * hint), the movie list (left / right, play), entering the episode (its exit, else a transition), and after an
 * animation part the mode that follows it (D_002BE278). */
void UpdateEpMenu__FP6EPMENU(EPMENU *pepmenu)
{
    int idPart;
    func_00212C50(pepmenu);
    if (func_001D9880(D_003D9ED0))
        return;
    if (func_001D9880(D_002E6550))
        return;
    if (func_001D9880(D_003DA4F0))
        return;
    idPart = IdPartCur__FP6EPMENU(pepmenu);
    switch (pepmenu->mode) {
    case EPMODE_None:
        return;
    case EPMODE_Select: {
        float g = func_001880D8(g_joy);
        if (g < 0.0f && pepmenu->cur <= 0) {
            PlaySound(0x36);
            return;
        }
        if (0.0f < g && pepmenu->cur >= pepmenu->max) {
            PlaySound(0x36);
            return;
        }
        if (g != 0.0f) {
            if (g < 0.0f)
                pepmenu->next = pepmenu->cur - 1;
            else
                pepmenu->next = pepmenu->cur + 1;
            SetEpMode__FP6EPMENUii(pepmenu, 0.0f < g ? EPMODE_Next : EPMODE_Prev, -1);
            return;
        }
        if (GrfbtnTakePressedJoy(g_joy, 0x40)) {
            SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Confirm, -1);
            return;
        }
        if (pepmenu->cur && GrfbtnTakePressedJoy(g_joy, 0x10)) {
            pepmenu->next = 0;
            SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Prev, -1);
            return;
        }
        switch (pepmenu->hint) {
        case 0: {
            int c;
            int f = 0;
            int n = D_002BE248[pepmenu->cur];
            void *pv = g_sw.epprogress.apvPercent[pepmenu->cur];
            if (pv) {
                struct CRef ref;
                NProgress(&ref, pv, D_003D4A60);
                c = ref.m_n;
                Decref(&ref);
                if (c >= 100)
                    goto setf;
            }
            if (D_002BE26C) {
            setf:
                f = 1;
            }
            if (n && f && 10.0f < g_clock.tReal - pepmenu->tHint)
                SetHint__FP6EPMENUi(pepmenu, 1);
            return;
        }
        case 1:
            if (GrfbtnTakePressedJoy(g_joy, 0x80)) {
                QueueMovie__FPUcPv(D_002F66B0, D_002BE248[pepmenu->cur]);
                RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, 0, 0x189, -1, 0, -1);
                PlaySound(0x34);
                return;
            }
            if (2.0f < g_clock.tReal - pepmenu->tHint)
                SetHint__FP6EPMENUi(pepmenu, 0);
            return;
        }
        return;
    }
    case EPMODE_Movies:
        switch (pepmenu->sub) {
        case -1:
            if (GrfbtnTakePressedJoy(g_joy, 0x40))
                SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Enter, -1);
            else if (GrfbtnTakePressedJoy(g_joy, 0x10))
                SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Back, -1);
            return;
        case 0: {
            float g;
            if (GrfbtnTakePressedJoy(g_joy, 0x40)) {
                D_002BE270 = pepmenu->imovie;
                QueueMovie__FPUcPv(D_002F66B0, D_002BE200[pepmenu->imovie]);
                RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, 0, 0x189, -1, 0, -1);
                PlaySound(0x34);
                return;
            }
            if (GrfbtnTakePressedJoy(g_joy, 0x10)) {
                SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Back, -1);
                return;
            }
            g = func_00187E88(g_joy);
            if (g < 0.0f && pepmenu->imovie <= 0) {
                PlaySound(0x36);
                return;
            }
            if (0.0f < g && pepmenu->imovie >= CmovieOpen__FP6EPMENU(pepmenu)) {
                PlaySound(0x36);
                return;
            }
            if (g != 0.0f) {
                if (g < 0.0f)
                    pepmenu->imovie = pepmenu->imovie - 1;
                else
                    pepmenu->imovie = pepmenu->imovie + 1;
                SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Movies, 0.0f < g ? 2 : 1);
            }
            return;
        }
        case 1:
        case 2:
            if (!FSpriteAnimPlaying__FP2LOi(pepmenu, idPart))
                SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Movies, 0);
            return;
        }
        return;
    case EPMODE_Enter:
        if (!FSpriteAnimPlaying__FP2LOi(pepmenu, idPart)) {
            int f = 0;
            void *pv = g_sw.epprogress.apvDt[pepmenu->cur];
            if (pv) {
                struct CRefG ref;
                float g;
                f = 1;
                NProgress(&ref, pv, D_003D4A60);
                g = ref.m_g;
                Decref(&ref);
                if (g != 0.0f)
                    f = 0;
            }
            if (f) {
                void *po = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, D_002BE2A8[pepmenu->cur], 0);
                if (po) {
                    SetExitState__FP2LOi(po, 3);
                    TriggerExit__FP4EXIT(po);
                } else
                    f = 0;
            }
            if (!f) {
                int s = func_00210B98(pepmenu->cur);
                RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, s, 0x189, -1, 0, 0x30A);
            }
            SetEpMode__FP6EPMENUii(pepmenu, EPMODE_None, -1);
        }
        return;
    default:
        if (!FSpriteAnimPlaying__FP2LOi(pepmenu, idPart)) {
            int k = D_002BE278[pepmenu->mode];
            int n = -1;
            if (k == EPMODE_Movies && pepmenu->cur == 0) {
                pepmenu->imovie = 0;
                n = 0;
            }
            SetEpMode__FP6EPMENUii(pepmenu, k, n);
        }
        return;
    }
}
